# Minimum required version of CMake
cmake_minimum_required(VERSION 3.22)

# Añadir el archivo de recursos (resources.qrc) al sistema de construcción de Qt5
qt5_add_resources(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)

# Crear una biblioteca estática de recursos que pueda ser vinculada al ejecutable principal
add_library(resources STATIC ${RESOURCES})

# Incluir el directorio de recursos como parte de las rutas de búsqueda de encabezados
target_include_directories(resources PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
