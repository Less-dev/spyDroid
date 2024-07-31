#!/bin/bash

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
    echo -e "\033[33mTemplate selected \"$corrected_value\"\033[0m"
}


# Parse command-line arguments
while getopts ":t:" opt; do
    case ${opt} in
        t )
            file="app/src/main/java/net/spydroid/app/config.kt" # Specify the path to your file
            input_value="$OPTARG"

            # Find the closest match from valid options
            corrected_value=$(closest_match "$input_value" "${valid_options[@]}")
            update_template_app "$file" "$corrected_value"
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


installTools() {
    sudo apt update
    sudo apt upgrade -y
}

while getopts ":install-tools:" opt; do
    case ${opt} in
        t )

            installTools
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

