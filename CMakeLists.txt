# Minimum required version of CMake
cmake_minimum_required(VERSION 3.22)

# Define the project name
project(spydroid VERSION 1.0 LANGUAGES CXX)

# Check for required packages
find_package(jsoncpp REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED) # Cambiado de Qt6 a Qt5
find_package(CURL REQUIRED)
find_library(QTERM_LIBRARY qtermwidget5 /usr/lib)

# Define directories
set(SOURCE_DIR app/src/main/net/spydroid/desktop)
set(INCLUDE_DIR ${SOURCE_DIR}/presentation)
include_directories(/usr/include/qtermwidget5)

# Define header files
set(HEADERS
    ${INCLUDE_DIR}/HomeScreen.h
    ${INCLUDE_DIR}/DashBoardScreen.h
    ${INCLUDE_DIR}/ApkStudioScreen.h
    ${INCLUDE_DIR}/MultimediaScreen.h
    ${INCLUDE_DIR}/ImagesScreen.h
    ${INCLUDE_DIR}/VideosScreen.h
    ${INCLUDE_DIR}/AudiosScreen.h
    ${INCLUDE_DIR}/DocumentsScreen.h
    ${INCLUDE_DIR}/SmsScreen.h
    ${SOURCE_DIR}/components/CardSms.h
    ${SOURCE_DIR}/components/GoBack.h
    ${SOURCE_DIR}/components/CardMultimedia.h
    ${SOURCE_DIR}/components/ItemBoard.h
    ${SOURCE_DIR}/components/Terminal.h
    ${SOURCE_DIR}/components/CodeEditor.h
    ${SOURCE_DIR}/components/FileExplorer.h
    ${SOURCE_DIR}/presentation/ApkStudioScreen.h
)

# Define source files
set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${INCLUDE_DIR}/HomeScreen.cpp
    ${INCLUDE_DIR}/DashBoardScreen.cpp
    ${INCLUDE_DIR}/ApkStudioScreen.cpp
    ${INCLUDE_DIR}/MultimediaScreen.cpp
    ${INCLUDE_DIR}/ImagesScreen.cpp
    ${INCLUDE_DIR}/VideosScreen.cpp
    ${INCLUDE_DIR}/AudiosScreen.cpp
    ${INCLUDE_DIR}/DocumentsScreen.cpp
    ${INCLUDE_DIR}/SmsScreen.cpp
    ${SOURCE_DIR}/data/colors.cpp
    ${SOURCE_DIR}/components/GoBack.cpp
    ${SOURCE_DIR}/components/CardSms.cpp
    ${SOURCE_DIR}/components/CardMultimedia.cpp
    ${SOURCE_DIR}/components/ItemBoard.cpp
    ${SOURCE_DIR}/components/Terminal.cpp 
    ${SOURCE_DIR}/components/CodeEditor.cpp 
    ${SOURCE_DIR}/components/FileExplorer.cpp 
    ${SOURCE_DIR}/remote/network/api/ApiService.cpp
    ${SOURCE_DIR}/remote/network/data/DevicesDaoImp.cpp
    ${SOURCE_DIR}/remote/network/data/InfoDaoImp.cpp
    ${SOURCE_DIR}/remote/network/data/MultimediaDaoImp.cpp
    ${SOURCE_DIR}/remote/network/data/SmsDaoImp.cpp
    ${SOURCE_DIR}/remote/data/DevicesRepositoryImp.cpp
    ${SOURCE_DIR}/remote/data/InfoRepositoryImp.cpp
    ${SOURCE_DIR}/remote/data/MultimediaRepositoryImp.cpp
    ${SOURCE_DIR}/remote/data/SmsRepositoryImp.cpp
)

# Create the executable
add_executable(spydroid ${SOURCES})

# Add MOC sources (Qt5 version)
qt5_wrap_cpp(MOC_SOURCES ${HEADERS}) # Cambiado de qt6_wrap_cpp a qt5_wrap_cpp
target_sources(spydroid PRIVATE ${MOC_SOURCES})

# Add resources (Qt5 version)
qt5_add_resources(RESOURCES app/src/main/net/spydroid/desktop/resources.qrc) # Cambiado de qt6_add_resources a qt5_add_resources
target_sources(spydroid PRIVATE ${RESOURCES})

# Link libraries
target_link_libraries(spydroid
    ${GETTEXT_LIBRARIES}
    ${CURL_LIBRARIES}
    ${QTERM_LIBRARY}
    jsoncpp_lib
    Qt5::Widgets # Cambiado de Qt6::Widgets a Qt5::Widgets
)

# Include directories
target_include_directories(spydroid PRIVATE ${INCLUDE_DIR})

# Install targets
install(TARGETS spydroid DESTINATION ${CMAKE_INSTALL_FULL_BINDIR} )
