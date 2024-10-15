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

execute_process(COMMAND pkg-config --modversion libarchive
                OUTPUT_VARIABLE LIBARCHIVE_VERSION
                OUTPUT_STRIP_TRAILING_WHITESPACE)

include_directories(/usr/include/qtermwidget5 ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(core-network)
add_subdirectory(core-ui)
add_subdirectory(core-data)
add_subdirectory(resources)

set(SOURCE_DIR app/src/spydroid/main)
set(SOURCES ${SOURCE_DIR}/main.cpp)

add_executable(spydroid ${SOURCES})

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
target_sources(spydroid PRIVATE ${MOC_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/resources/qrc_resources.cpp)
target_sources(spydroid PRIVATE ${MOC_SOURCES} ${RESOURCES})

target_link_libraries(spydroid
    core-ui
    core-network
    core-data
    resources
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

# Install DEB
install(TARGETS spydroid DESTINATION /usr/bin)
install(FILES ${CMAKE_SOURCE_DIR}/resources/spydroid.desktop DESTINATION /usr/share/applications)
install(FILES ${CMAKE_SOURCE_DIR}/resources/drawable/spydroid.png DESTINATION /usr/share/icons/hicolor/256x256/apps)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION /usr/include)

# CPack configuration for DEB packaging
set(CPACK_PACKAGE_NAME "spydroid")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "Less less.github.gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Spydroid - Monitoring devices android")
set(CPACK_PACKAGE_VENDOR "Less")
set(CPACK_PACKAGE_MAINTAINER "Less less.github@gmail.com")

# Set the package type to DEB
set(CPACK_GENERATOR "DEB")

# Set the architecture for the DEB package
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")

# Set the app icon location from the resources.qrc file
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${CMAKE_PROJECT_VERSION}_alpha_linux-x64")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/Less-dev/spyDroid")

# Include CPack for package generation
include(CPack)