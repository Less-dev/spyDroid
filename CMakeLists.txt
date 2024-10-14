#Copyright (C) 2024 Daniel Gómez (Less)
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program. If not, see <https://www.gnu.org/licenses/>.


cmake_minimum_required(VERSION 3.22)

project(spydroid VERSION 0.0.1 LANGUAGES CXX)

find_package(jsoncpp REQUIRED)
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
find_package(CURL REQUIRED)
find_library(QTERM_LIBRARY qtermwidget5 /usr/lib)
find_library(LIBZIPPP_LIBRARY NAMES zippp HINTS /usr/local/lib /usr/lib)

include_directories(/usr/include/qtermwidget5)

add_subdirectory(core-network)
add_subdirectory(core-ui)
add_subdirectory(core-data)
add_subdirectory(resources)

set(SOURCE_DIR app/src/spydroid/main)
set(SOURCES
    ${SOURCE_DIR}/main.cpp
)

# Add the executable for spydroid
add_executable(spydroid ${SOURCES})

# If there are MOC sources, include them
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
target_sources(spydroid PRIVATE ${MOC_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/resources/qrc_resources.cpp)
target_sources(spydroid PRIVATE ${MOC_SOURCES} ${RESOURCES})

# Link libraries with the executable
target_link_libraries(spydroid
    core-ui         # Link with core-ui module
    core-network    # Link with core-network module
    core-data       # Link with core-data module
    resources       # Link with the static resources library
    CURL::libcurl
    ${QTERM_LIBRARY}
    jsoncpp_lib
    Qt5::Widgets
    Qt5::Core
    zip
    archive 
)

# Installation target
install(TARGETS spydroid DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})

# Install icon
install(FILES resources/spydroid.desktop DESTINATION /usr/share/applications)
install(FILES resources/drawable/spydroid.png DESTINATION /usr/share/icons/hicolor/256x256/apps)

# CPack configuration for DEB packaging
set(CPACK_PACKAGE_NAME "spydroid")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "Less less.github.gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Spydroid - Monitoring devices android")
set(CPACK_PACKAGE_VENDOR "Less")
set(CPACK_PACKAGE_MAINTAINER "Less<less.github@gmail.com")

# Set the package type to DEB
set(CPACK_GENERATOR "DEB")

# Set the architecture for the DEB package
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")

# Define dependencies for the DEB package
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5core5a, libqt5widgets5, libcurl4, libjsoncpp1, qtermwidget5")

# Set additional metadata
#set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
#set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

# Set the app icon location from the resources.qrc file
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-alpha-linux-x64")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/Less-dev/spyDroid")

# Include CPack for package generation
include(CPack)
