#!/bin/bash

 #
 # Copyright (C) 2024 Daniel Gómez(Less)
 #
 # This program is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 #  any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with this program. If not, see <https://www.gnu.org/licenses/>.
 #


changeIconApp() {
  local nuevo_icono="$1"
  local file="app/src/main/AndroidManifest.xml"

  sed -i "s/android:icon=\"@mipmap\/ic_launcher_[^\"]*\"/android:icon=\"@mipmap\/ic_launcher_$nuevo_icono\"/" "$file"
  sed -i "s/android:roundIcon=\"@mipmap\/ic_launcher_round_[^\"]*\"/android:roundIcon=\"@mipmap\/ic_launcher_round_$nuevo_icono\"/" "$file"
}

changeAppName() {
  local new_name="$1"
  local file="app/src/main/res/values/strings.xml"

  # Exceptions
  if [ "$new_name" == "calculator" ]; then
    new_name="calculadora"
  elif [ "$new_name" == "default" ]; then
    new_name="Lista de tareas"
  elif [ "$new_name" == "sample" ]; then
    new_name="ejemplo"
  fi

  sed -i "s/<string name=\"app_name\">[^<]*<\/string>/<string name=\"app_name\">$new_name<\/string>/" "$file"
}

valid_options=("default" "facebook" "calculator" "sample")

closest_match() {
    local input=$1
    local min_dist=9999
    local best_match="default"
    local max_dist=5 # Maximum acceptable distance for a match
    
    for option in "${valid_options[@]}"; do
        # Compute the Levenshtein distance
        local dist=$(awk -v str1="$input" -v str2="$option" '
        BEGIN {
            len1 = length(str1)
            len2 = length(str2)
            for (i = 0; i <= len1; i++) d[i,0] = i
            for (j = 0; j <= len2; j++) d[0,j] = j
            for (i = 1; i <= len1; i++) {
                for (j = 1; j <= len2; j++) {
                    cost = (substr(str1,i,1) == substr(str2,j,1) ? 0 : 1)
                    d[i,j] = min(d[i-1,j] + 1, d[i,j-1] + 1, d[i-1,j-1] + cost)
                }
            }
            print d[len1,len2]
        }
        function min(a, b, c) {
            return a < b ? (a < c ? a : c) : (b < c ? b : c)
        }')
        
        if [ "$dist" -lt "$min_dist" ]; then
            min_dist=$dist
            best_match=$option
        fi
    done
    
    # Check if the best match is within the acceptable distance
    if [ "$min_dist" -le "$max_dist" ]; then
        echo "$best_match"
    else
        echo "default"
    fi
}

# Define the function to update the template app
update_template_app() {
    local file="$1"
    local corrected_value="$2"

    # Check if the file exists
    if [ ! -f "$file" ]; then
        echo "The file $file does not exist."
        exit 1
    fi

    # Escape the value for use in sed
    local escaped_value=$(printf '%s\n' "$corrected_value" | sed -e 's/[\/&]/\\&/g')

    # Replace the value of template_app in the file
    sed -i "s/^internal val template_app = \".*\"/internal val template_app = \"$escaped_value\"/" "$file"

    # Print the final message in yellow with "(successfully)!" in green
    changeAppName "$corrected_value"
    changeIconApp "$corrected_value"
    echo -e "\033[33mTemplate selected \"$corrected_value\"\033[0m"
}


install_programs() {
    local programs_to_install=("$@")
    local missing_programs=()

    # Detected SO
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        if [[ -f /etc/debian_version ]]; then
            OS="Debian"
            PACKAGE_MANAGER="apt"
            UPDATE_CMD="sudo apt update"
            INSTALL_CMD="sudo apt install -y"
            SEARCH_CMD="apt-cache search"
        elif [[ -f /etc/fedora-release ]]; then
            OS="Fedora"
            PACKAGE_MANAGER="dnf"
            UPDATE_CMD="sudo dnf check-update"
            INSTALL_CMD="sudo dnf install -y"
            SEARCH_CMD="dnf search"
        elif [[ -f /etc/arch-release ]]; then
            OS="Arch"
            PACKAGE_MANAGER="pacman"
            UPDATE_CMD="sudo pacman -Sy"
            INSTALL_CMD="sudo pacman -S --noconfirm"
            SEARCH_CMD="pacman -Ss"
        else
            echo -e "\e[31mUnsupported Linux distribution.\e[0m"
            exit 1
        fi
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        OS="macOS"
        PACKAGE_MANAGER="brew"
        UPDATE_CMD="brew update"
        INSTALL_CMD="brew install"
        SEARCH_CMD="brew search"
    else
        echo -e "\e[31mUnsupported operating system.\e[0m"
        exit 1
    fi


    # update repos
    $UPDATE_CMD

    # check if the program exists in the repositories
    for program in "${programs_to_install[@]}"; do
        if $SEARCH_CMD "$program" >/dev/null 2>&1; then
            echo -e "\e[96m$program is available in the repositories.\e[0m"
            missing_programs+=("$program")
        else
            echo -e "\e[91m$program is not available in the repositories.\e[0m"
        fi
    done

    # install missing programs
    if [ ${#missing_programs[@]} -gt 0 ]; then
        $INSTALL_CMD "${missing_programs[@]}"
    else
        echo -e "\e[93mAll programs are either already installed or not available in the repositories.\e[0m"
    fi
}


install_dependencies() {
    programs=("openjdk-17-jdk")
    if install_programs "${programs[@]}"; then
        clear
        echo -e "\033[1;32mDependencies installed successfully\033[0m"
    else
        clear
        echo -e "\033[1;31mError attempting to install dependencies\033[0m"
    fi
}

compile_project() {
    ./gradlew assembleRelease
    if [ $? -eq 0 ]; then
        echo -e "\033[1;32mAPK generated successfully\033[0m"
    else
        echo -e "\033[1;31mError generating the APK\033[0m"
    fi
}

# Parse command-line arguments
while getopts ":t:ic" opt; do
    case ${opt} in
        t )
            file="app/src/main/java/net/spydroid/app/config.kt" # Specify the path to your file
            input_value="$OPTARG"

            # Find the closest match from valid options
            corrected_value=$(closest_match "$input_value" "${valid_options[@]}")
            update_template_app "$file" "$corrected_value"
            ;;
        i )
            install_dependencies
            ;;
        c )
            compile_project
            ;;
        \? )
            echo "Invalid option: -$OPTARG" >&2
            ;;
        : )
            echo "Invalid option: -$OPTARG requires an argument" >&2
            echo 'Usage: ./script.sh "template_of_preference"'
            echo -e "\033[34mtemplates for usage: \n* default\n* facebook\n* calculator\n* sample\033[0m"
            ;;
    esac
done
shift $((OPTIND -1))