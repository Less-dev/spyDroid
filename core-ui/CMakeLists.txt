# Definir los archivos de encabezado y fuente para core-ui
set(HEADERS
    src/spydroid/ui/presentation/HomeScreen.h
    src/spydroid/ui/presentation/DashBoardScreen.h
    src/spydroid/ui/presentation/ApkStudioScreen.h
    src/spydroid/ui/presentation/MultimediaScreen.h
    src/spydroid/ui/presentation/ImagesScreen.h
    src/spydroid/ui/presentation/VideosScreen.h
    src/spydroid/ui/presentation/AudiosScreen.h
    src/spydroid/ui/presentation/DocumentsScreen.h
    src/spydroid/ui/presentation/SmsScreen.h
    src/spydroid/ui/widgets/CardMultimedia.h
    src/spydroid/ui/widgets/CardSms.h
    src/spydroid/ui/widgets/GoBack.h
    src/spydroid/ui/widgets/ItemBoard.h
    src/spydroid/ui/widgets/Terminal.h
    src/spydroid/ui/widgets/CodeEditor.h
    src/spydroid/ui/widgets/FileExplorer.h
    src/spydroid/ui/widgets/FileWidget.h
)

set(SOURCES
    src/spydroid/ui/presentation/HomeScreen.cpp
    src/spydroid/ui/presentation/DashBoardScreen.cpp
    src/spydroid/ui/presentation/ApkStudioScreen.cpp
    src/spydroid/ui/presentation/MultimediaScreen.cpp
    src/spydroid/ui/presentation/ImagesScreen.cpp
    src/spydroid/ui/presentation/VideosScreen.cpp
    src/spydroid/ui/presentation/AudiosScreen.cpp
    src/spydroid/ui/presentation/DocumentsScreen.cpp
    src/spydroid/ui/presentation/SmsScreen.cpp
    src/spydroid/ui/widgets/GoBack.cpp
    src/spydroid/ui/widgets/CardSms.cpp
    src/spydroid/ui/widgets/CardMultimedia.cpp
    src/spydroid/ui/widgets/ItemBoard.cpp
    src/spydroid/ui/widgets/Terminal.cpp
    src/spydroid/ui/widgets/CodeEditor.cpp
    src/spydroid/ui/widgets/FileExplorer.cpp
    src/spydroid/ui/widgets/FileWidget.cpp
)

# Definir el objetivo core-ui como una biblioteca
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library(core-ui STATIC ${SOURCES} ${HEADERS} ${MOC_SOURCES})


# Especificar los directorios de inclusión para core-ui
target_include_directories(core-ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Vincular las bibliotecas necesarias
target_link_libraries(core-ui Qt5::Widgets)
