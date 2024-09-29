# Definir el directorio de los archivos fuente
set(SOURCE_DIR src/spydroid/network)

# Archivos de encabezado y fuente
set(HEADERS
    ${SOURCE_DIR}/api/ApiService.h
    ${SOURCE_DIR}/daos/DevicesDao.h
    ${SOURCE_DIR}/daos/InfoDao.h
    ${SOURCE_DIR}/daos/MultimediaDao.h
    ${SOURCE_DIR}/daos/SmsDao.h
    ${SOURCE_DIR}/models/Devices.h
    ${SOURCE_DIR}/models/Info.h
    ${SOURCE_DIR}/models/Multimedia.h
    ${SOURCE_DIR}/models/Sms.h
)

set(SOURCES
    ${SOURCE_DIR}/api/ApiService.cpp
    ${SOURCE_DIR}/data/DevicesDaoImp.cpp
    ${SOURCE_DIR}/data/InfoDaoImp.cpp
    ${SOURCE_DIR}/data/MultimediaDaoImp.cpp
    ${SOURCE_DIR}/data/SmsDaoImp.cpp
)

# Definir el target como una biblioteca
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library(core-network STATIC ${SOURCES} ${HEADERS} ${MOC_SOURCES})

# Incluir los directorios necesarios
target_include_directories(core-network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Vincular las bibliotecas jsoncpp y CURL
target_link_libraries(core-network JsonCpp::JsonCpp CURL::libcurl)
