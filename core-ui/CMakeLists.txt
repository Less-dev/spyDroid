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

set(HEADERS
    src/spydroid/ui/presentation/InstallerScreen.h
    src/spydroid/ui/presentation/HomeScreen.h
    src/spydroid/ui/presentation/DashBoardScreen.h
    src/spydroid/ui/presentation/ApkStudioScreen.h
    src/spydroid/ui/presentation/IDEScreen.h
    src/spydroid/ui/presentation/TemplateScreen.h
    src/spydroid/ui/presentation/ServerStudioScreen.h
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
    src/spydroid/ui/widgets/Setup.h
    src/spydroid/ui/widgets/SetupSettings.h
    src/spydroid/ui/widgets/SetupVerify.h
    src/spydroid/ui/widgets/SetupFinished.h
    src/spydroid/ui/widgets/BottomBarInstaller.h
    src/spydroid/ui/widgets/BannerHorizontal.h
    src/spydroid/ui/widgets/BrowserSetup.h
    src/spydroid/ui/widgets/CardWidgetVerify.h
    src/spydroid/ui/widgets/CardWidgetSettings.h
    src/spydroid/ui/widgets/CardWidgetInstaller.h
    src/spydroid/ui/widgets/CardOptions.h
    src/spydroid/ui/widgets/SelectTemplate.h
)

set(SOURCES
    src/spydroid/ui/presentation/InstallerScreen.cpp
    src/spydroid/ui/presentation/HomeScreen.cpp
    src/spydroid/ui/presentation/DashBoardScreen.cpp
    src/spydroid/ui/presentation/ApkStudioScreen.cpp
    src/spydroid/ui/presentation/IDEScreen.cpp
    src/spydroid/ui/presentation/TemplateScreen.cpp
    src/spydroid/ui/presentation/ServerStudioScreen.cpp
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
    src/spydroid/ui/widgets/Setup.cpp
    src/spydroid/ui/widgets/SetupSettings.cpp
    src/spydroid/ui/widgets/SetupVerify.cpp
    src/spydroid/ui/widgets/SetupFinished.cpp
    src/spydroid/ui/widgets/BottomBarInstaller.cpp
    src/spydroid/ui/widgets/BannerHorizontal.cpp
    src/spydroid/ui/widgets/BrowserSetup.cpp
    src/spydroid/ui/widgets/CardWidgetVerify.cpp
    src/spydroid/ui/widgets/CardWidgetSettings.cpp
    src/spydroid/ui/widgets/CardWidgetInstaller.cpp
    src/spydroid/ui/widgets/CardOptions.cpp
    src/spydroid/ui/widgets/SelectTemplate.cpp
)

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library(core-ui STATIC ${SOURCES} ${HEADERS} ${MOC_SOURCES})


target_include_directories(core-ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(core-ui Qt5::Widgets)
