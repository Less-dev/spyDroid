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
#include "res/vnc_viewer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>  
#include "presentation/HomeScreen.h"
#include "presentation/SmsScreen.h"
#include "presentation/MultimediaScreen.h"

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
    HomeScreen* home = new HomeScreen;
    SmsScreen* sms = new SmsScreen;
    MultimediaScreen* multimedia = new MultimediaScreen;

    stackedWidget.addWidget(home);         // Index 0
    stackedWidget.addWidget(multimedia);   // Índex 1
    stackedWidget.addWidget(sms);          //Index 2

    // Show view home primary
    stackedWidget.setCurrentIndex(0);
    stackedWidget.showMaximized();
    stackedWidget.setWindowTitle("Información general");

    QObject::connect(home, &HomeScreen::goToMultimedia, [&stackedWidget, multimedia](const QString& alias) {
        multimedia->setDeviceAlias(alias);
        stackedWidget.setCurrentIndex(1);  // Change to view main
        stackedWidget.setWindowTitle("Archivos multimedia de " + alias);
    });

    QObject::connect(home, &HomeScreen::goToSms, [&stackedWidget, &sms](const QString& alias) {
        SmsScreen* newSmsScreen = new SmsScreen(alias);
    
        QObject::connect(newSmsScreen, &SmsScreen::goToHome, [&stackedWidget]() {
            stackedWidget.setCurrentIndex(0);  // Change to home view
            stackedWidget.setWindowTitle("Información general");
        });
    
        stackedWidget.removeWidget(sms);  // Remover la vista antigua
        delete sms;  // Eliminar la instancia antigua
        sms = newSmsScreen;  // Asignar la nueva instancia
        stackedWidget.addWidget(sms);  // Añadir la nueva vista
        stackedWidget.setCurrentIndex(2);  // Cambiar a la vista SmsScreen
        stackedWidget.setWindowTitle("Mensajes de texto de " + alias);
    });



    QObject::connect(multimedia, &MultimediaScreen::goToHome, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(0);  // Change to view main
        stackedWidget.setWindowTitle("Información general");
    });
    return app.exec();
}
