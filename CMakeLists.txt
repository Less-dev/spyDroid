# Minimum required version of CMake
cmake_minimum_required(VERSION 3.22)

# Define the project name
project(spydroid VERSION 1.0 LANGUAGES CXX)

# Check for required packages
find_package(jsoncpp REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CURL_LIBRARY /usr/lib/x86_64-linux-gnu/libcurl.so)
find_package(CURL REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core)
find_library(QTERM_LIBRARY qtermwidget5 /usr/lib)

# Global include directories
include_directories(/usr/include/qtermwidget5)

# Add subdirectories for each core module
add_subdirectory(core-network)
add_subdirectory(core-ui)
add_subdirectory(core-data)
add_subdirectory(resources)

# Define source files for the main executable
set(SOURCE_DIR app/src/spydroid/main)
set(SOURCES
    ${SOURCE_DIR}/main.cpp
)

# Create the executable
add_executable(spydroid ${SOURCES})

# If there are MOC sources, include them
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
target_sources(spydroid PRIVATE ${MOC_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/resources/qrc_resources.cpp)

# Link the libraries
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

# Define installation rules
install(TARGETS spydroid DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})
