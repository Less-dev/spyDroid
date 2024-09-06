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
#include "components/goBack.h"
#include "presentation/home.h"
#include "presentation/profile.h"
#include <QStackedWidget>
#include "string"
#include "res/vnc_viewer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>  

int main(int argc, char *argv[])
{

    std::string filePath = "/tmp/vnc_viewer";

    // Verificar si el archivo ya existe
    if (access(filePath.c_str(), F_OK) == -1) {  // F_OK verifica la existencia del archivo
        // Solo escribir si el archivo no existe
        std::ofstream outfile(filePath, std::ios::binary);
        outfile.write(reinterpret_cast<const char*>(vncviewer), vncviewer_len);
        outfile.close();

        // Dar permisos de ejecución
        system(("chmod +x " + filePath).c_str());
    }

    QApplication app(argc, argv);

    QStackedWidget stackedWidget; 

    // Crear las vistas Home y Profile
    Home* home = new Home;
    Profile* profile = new Profile;

    // Añadir las vistas al QStackedWidget
    stackedWidget.addWidget(home);      // Índice 0
    stackedWidget.addWidget(profile);   // Índice 1

    // Mostrar inicialmente la vista Home
    stackedWidget.setCurrentIndex(0);
    stackedWidget.showMaximized();
    stackedWidget.setWindowTitle("Inicio");

    // Conectar la señal para navegar de Home a Profile
    QObject::connect(home, &Home::goToProfile, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(1);  // Cambiar a la vista Profile
        stackedWidget.setWindowTitle("Perfil");
    });

    // Conectar la señal para navegar de Profile a Home
    QObject::connect(profile, &Profile::goToHome, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(0);  // Cambiar a la vista Home
        stackedWidget.setWindowTitle("Inicio");
    });

    return app.exec();
}

