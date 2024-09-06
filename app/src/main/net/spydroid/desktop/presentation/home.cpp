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

#include "home.h"

Home::Home(QWidget *parent) : QWidget(parent)
{
    // Establecer las propiedades de la ventana
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, QColor("#260006"));  // El mismo color que la ventana principal
    this->setAutoFillBackground(true);
    this->setPalette(pal);


    // Crear el layout vertical
    layout = new QVBoxLayout(this);

    // Crear y configurar el QLabel
    label = new QLabel("Home", this);
    label->setAlignment(Qt::AlignCenter);

    // Crear el QPushButton para navegar a la vista Profile
    button = new QPushButton("Ir a Profile", this);
    connect(button, &QPushButton::clicked, this, &Home::goToProfile);  // Conectar el botón a la señal `goToProfile`

    // Crear el QLineEdit
    textField = new QLineEdit(this);
    textField->setPlaceholderText("Introduce algo aquí");

    // Añadir los widgets al layout
    layout->addWidget(label);
    layout->addWidget(button);
    layout->addWidget(textField);

    // Establecer el layout para esta vista
    this->setLayout(layout);
}



    /*
        DevicesRepositoryImp devicesRepository;

    // Get all devices
    std::vector<DevicesHandler> devices = devicesRepository.getDevices();


    for (const auto& device : devices) {
        std::cout <<
         "ID: " <<
          device.id <<
           ", Alias: " <<
            device.alias <<
             ", Name: " <<
              device.name <<
               std::endl;
    }

    // Get specific device from api
    std::string alias = "ALIAS_3";
    std::vector<DevicesHandler> device = devicesRepository.getDevice(alias);
    std::cout << std::string(40, '-') << std::endl;

    for (const auto& device : device) {
        std::cout << 
        "ID: " <<
         device.id <<
          ", Alias: " <<
           device.alias <<
            ", Name: " <<
             device.name <<
              std::endl;
    }
    */