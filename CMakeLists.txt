# Check for required packages
find_package(jsoncpp REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(CURL REQUIRED)

# Define directories
set(SOURCE_DIR app/src/main/net/spydroid/desktop)
set(INCLUDE_DIR ${SOURCE_DIR}/presentation)

# Define header files
set(HEADERS
    ${INCLUDE_DIR}/HomeScreen.h
    ${INCLUDE_DIR}/MultimediaScreen.h
    ${INCLUDE_DIR}/SmsScreen.h
    ${SOURCE_DIR}/components/CardSms.h
    ${SOURCE_DIR}/components/GoBack.h
    ${SOURCE_DIR}/components/CardMultimedia.h
)

# Define source files
set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${INCLUDE_DIR}/HomeScreen.cpp
    ${INCLUDE_DIR}/MultimediaScreen.cpp
    ${INCLUDE_DIR}/SmsScreen.cpp
    ${SOURCE_DIR}/data/colors.cpp
    ${SOURCE_DIR}/components/GoBack.cpp
    ${SOURCE_DIR}/components/CardSms.cpp
    ${SOURCE_DIR}/components/CardMultimedia.cpp
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

# Add MOC sources
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
target_sources(spydroid PRIVATE ${MOC_SOURCES})

# Add resources
qt5_add_resources(RESOURCES app/src/main/net/spydroid/desktop/resources.qrc)
target_sources(spydroid PRIVATE ${RESOURCES})

# Link libraries
target_link_libraries(spydroid
    ${GETTEXT_LIBRARIES}
    ${CURL_LIBRARIES}
    jsoncpp_lib
    Qt5::Widgets
)

# Include directories
target_include_directories(spydroid PRIVATE ${INCLUDE_DIR})

# Install targets
install(TARGETS spydroid DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})
