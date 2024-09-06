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
#include "../remote/domain/DevicesRepository.h"
#include "iostream"
#include <QTableWidget>
#include <QHeaderView>
#include <QScroller>


void showDevicesTable(const std::vector<DevicesHandler>& devices, QVBoxLayout* layout) {
    // Crear la tabla con el número de filas igual al número de dispositivos y 2 columnas
    QTableWidget* table = new QTableWidget(static_cast<int>(devices.size()), 2);
    table->setHorizontalHeaderLabels(QStringList() << "Alias" << "Dispositivo");

    // Poblar la tabla con los datos de dispositivos
    int row = 0;
    for (const auto& device : devices) {
        // Column alias
        QTableWidgetItem* aliasItem = new QTableWidgetItem(QString::fromStdString(device.alias));
        aliasItem->setTextAlignment(Qt::AlignLeft | Qt::AlignTop);  // Alinear a la izquierda y arriba
        aliasItem->setToolTip(QString::fromStdString(device.alias)); // Tooltip con el alias completo
        table->setItem(row, 0, aliasItem);

        // Column device
        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(device.name));
        table->setItem(row, 1, nameItem);
        aliasItem->setForeground(QBrush(QColor("#FFFFFF")));  // Color alias
        nameItem->setForeground(QBrush(QColor("#0000FF")));   // Color device

        ++row;
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->resizeRowsToContents();

    // Interactive tables
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    // Permission for edit the content
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QPalette palette = table->palette();
    palette.setColor(QPalette::Base, QColor("#260006"));  // Background
    table->setPalette(palette);
    table->setAutoFillBackground(true);
    table->setBackgroundRole(QPalette::Base);  

    table->setStyleSheet(
        "QScrollBar:vertical {"
        "    background: #390009;"
        "    width: 15px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #A9A9A9;"
        "    min-height: 20px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    background: #2E2E2E;"
        "    height: 0px;"
        "}"
        "QScrollBar:horizontal {"
        "    background: #390009;"
        "    height: 15px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "    background: #A9A9A9;"
        "    min-width: 20px;"
        "}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "    background: #390009;"
        "    width: 0px;"
        "}"

        "QTableWidget::item:selected {"
        "    background-color: #390009;"
        "}"
    );

    
    layout->addWidget(table);
}


Home::Home(QWidget *parent) : QWidget(parent) {
    // Establecer las propiedades de la ventana
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, QColor("#260006"));  // El mismo color que la ventana principal
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    // Crear el layout principal
    layout = new QVBoxLayout(this);

    DevicesRepositoryImp devicesRepository;

    // Obtener todos los dispositivos
    std::vector<DevicesHandler> devices = devicesRepository.getDevices();
    this->setLayout(layout);

    if (!devices.empty())
    {
        showDevicesTable(devices, layout);
    } else {
        label = new QLabel("No se encontró información", this);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("QLabel { color : #ffdae0; }");
        this->setLayout(layout);
        layout->addWidget(label);
    }
}





    /*
   // Crear el QPushButton para navegar a la vista Profile
    button = new QPushButton("Ir a Profile", this);
    connect(button, &QPushButton::clicked, this, &Home::goToProfile);  // Conectar el botón a la señal `goToProfile`


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