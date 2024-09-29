# Definir el directorio de los archivos fuente
set(SOURCE_DIR src/spydroid/data)

# Archivos de encabezado y fuente
set(HEADERS
    ${SOURCE_DIR}/domain/DevicesRepository.h
    ${SOURCE_DIR}/domain/InfoRepository.h
    ${SOURCE_DIR}/domain/MultimediaRepository.h
    ${SOURCE_DIR}/domain/SmsRepository.h
    ${SOURCE_DIR}/models/DevicesHandler.h
    ${SOURCE_DIR}/models/InfoHandler.h
    ${SOURCE_DIR}/models/MultimediaHandler.h
    ${SOURCE_DIR}/models/SmsHandler.h
    ${SOURCE_DIR}/local/SettingsManager.h
)

set(SOURCES
    ${SOURCE_DIR}/data/DevicesRepositoryImp.cpp
    ${SOURCE_DIR}/data/InfoRepositoryImp.cpp
    ${SOURCE_DIR}/data/MultimediaRepositoryImp.cpp
    ${SOURCE_DIR}/data/SmsRepositoryImp.cpp
    ${SOURCE_DIR}/local/SettingsManager.cpp
)

# Definir el target como una biblioteca
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library(core-data STATIC ${SOURCES} ${HEADERS} ${MOC_SOURCES})

# Incluir directorios relevantes para la compilación
target_include_directories(core-data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(core-data Qt5::Core)
