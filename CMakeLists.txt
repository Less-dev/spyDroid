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

project(spydroid VERSION 1.0 LANGUAGES CXX)

find_package(jsoncpp REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CURL_LIBRARY /usr/lib/x86_64-linux-gnu/libcurl.so)
find_package(CURL REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core)
find_library(QTERM_LIBRARY qtermwidget5 /usr/lib)

include_directories(/usr/include/qtermwidget5)

add_subdirectory(core-network)
add_subdirectory(core-ui)
add_subdirectory(core-data)
add_subdirectory(resources)

set(SOURCE_DIR app/src/spydroid/main)
set(SOURCES
    ${SOURCE_DIR}/main.cpp
)

add_executable(spydroid ${SOURCES})

# If there are MOC sources, include them
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
target_sources(spydroid PRIVATE ${MOC_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/resources/qrc_resources.cpp)

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
)

install(TARGETS spydroid DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})
