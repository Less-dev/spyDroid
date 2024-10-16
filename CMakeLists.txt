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

# Instalación solo para Linux
if(NOT WIN32)
    install(TARGETS spydroid DESTINATION /usr/bin)
else()
    # Instalación en un directorio relativo para Windows
    install(TARGETS spydroid DESTINATION bin)
endif()

# Aditional configuration for linux
if(UNIX AND NOT APPLE)
    install(FILES ${CMAKE_SOURCE_DIR}/resources/spydroid.desktop DESTINATION /usr/share/applications)
    install(FILES ${CMAKE_SOURCE_DIR}/resources/drawable/spydroid.png DESTINATION /usr/share/icons/hicolor/256x256/apps)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION /usr/lib)
    set(CMAKE_INSTALL_RPATH "/lib/x86_64-linux-gnu:/usr/lib:/usr/lib/qtermwidget5")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
endif()


# CPack configuration for DEB packaging
set(CPACK_PACKAGE_NAME "spydroid")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "Less less.github.gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Spydroid - Monitoring devices android")
set(CPACK_PACKAGE_VENDOR "Less")
set(CPACK_PACKAGE_MAINTAINER "Less less.github@gmail.com")

# Configuration packagment multiplatform
if(WIN32)
    # Package Windows
    set(CPACK_GENERATOR "NSIS;ZIP")
    set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_NAME} Installer")
    set(CPACK_NSIS_PACKAGE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-win64")
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/resources/drawable/spydroid.ico")
    set(CPACK_NSIS_HELP_LINK "https://github.com/Less-dev/spyDroid/issues")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/Less-dev/spyDroid/wiki/SPYDROID")
    set(CPACK_NSIS_CONTACT "less.github@gmail.com")
    set(CPACK_NSIS_MODIFY_PATH ON)
elseif(APPLE)
    # Package Apple
    # IF no is macbook next
    if(CPACK_GENERATOR MATCHES "DragNDrop")
        set(CPACK_GENERATOR "DragNDrop;ZIP")
        set(CPACK_DMG_BACKGROUND_IMAGE "${CMAKE_SOURCE_DIR}/dmg_background.png")
        set(CPACK_DMG_VOLUME_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-mac64")
    endif()
else()
    # Package Linux
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "less.github@gmail.com")
    set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${CMAKE_PROJECT_VERSION}_alpha_linux-x64")
endif()

# Include CPack for package generation
include(CPack)

# Custom target to package the DEB file and move it to the outputs directory
add_custom_target(linux-deb
    COMMAND ${CMAKE_COMMAND} -E echo "Generating DEB package with CPack..."
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/outputs
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} cpack -G DEB
    COMMAND ${CMAKE_COMMAND} -E echo "Moving DEB package to outputs directory..."
    COMMAND ${CMAKE_COMMAND} -E rename
        ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}_${PROJECT_VERSION}_alpha_linux-x64.deb
        ${CMAKE_BINARY_DIR}/outputs/${CMAKE_PROJECT_NAME}_${PROJECT_VERSION}_alpha_linux-x64.deb
    COMMENT "Packaging with CPack and moving .deb to outputs directory"
)

# Custom target for Windows NSIS
add_custom_target(windows-nsis
    COMMAND ${CMAKE_COMMAND} -E echo "Generating NSIS package with CPack..."
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/outputs
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} cpack -G NSIS
    COMMAND ${CMAKE_COMMAND} -E echo "Moving NSIS package to outputs directory..."
    COMMAND ${CMAKE_COMMAND} -E rename
        ${CMAKE_BINARY_DIR}/${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-win64.exe
        ${CMAKE_BINARY_DIR}/outputs/${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-win64.exe
    COMMENT "Packaging NSIS installer with CPack and moving it to outputs directory"
)

# Custom target for Windows ZIP
add_custom_target(windows-zip
    COMMAND ${CMAKE_COMMAND} -E echo "Generating ZIP package with CPack..."
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/outputs
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} cpack -G ZIP
    COMMAND ${CMAKE_COMMAND} -E echo "Moving ZIP package to outputs directory..."
    COMMAND ${CMAKE_COMMAND} -E rename
        ${CMAKE_BINARY_DIR}/${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-win64.zip
        ${CMAKE_BINARY_DIR}/outputs/${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-win64.zip
    COMMENT "Packaging ZIP archive with CPack and moving it to outputs directory"
)

# Custom target for Apple DMG
add_custom_target(mac-dmg
    COMMAND ${CMAKE_COMMAND} -E echo "Generating DMG package with CPack..."
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/outputs
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} cpack -G DragNDrop
    COMMAND ${CMAKE_COMMAND} -E echo "Moving DMG package to outputs directory..."
    COMMAND ${CMAKE_COMMAND} -E rename
        ${CMAKE_BINARY_DIR}/${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-mac64.dmg
        ${CMAKE_BINARY_DIR}/outputs/${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-mac64.dmg
    COMMENT "Packaging DMG with CPack and moving it to outputs directory"
)

# Custom target for Apple ZIP
add_custom_target(mac-zip
    COMMAND ${CMAKE_COMMAND} -E echo "Generating ZIP package with CPack..."
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/outputs
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} cpack -G ZIP
    COMMAND ${CMAKE_COMMAND} -E echo "Moving ZIP package to outputs directory..."
    COMMAND ${CMAKE_COMMAND} -E rename
        ${CMAKE_BINARY_DIR}/${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-mac64.zip
        ${CMAKE_BINARY_DIR}/outputs/${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-mac64.zip
    COMMENT "Packaging ZIP archive with CPack and moving it to outputs directory"
)