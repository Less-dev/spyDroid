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
#include <iostream>
#include <QTableWidget>
#include <QHeaderView>
#include <QScroller>
#include <QMessageBox>
#include "QObject"
#include "QDebug"



void Home::handleVncButtonClick() {
    // Aquí manejas el clic del botón VNC
    qDebug() << "Hola Mundo";  // Imprime "Hola Mundo" cuando se presiona el botón
}

void showDevicesTable(const std::vector<DevicesHandler>& devices, QVBoxLayout* layout, QTableWidget* &table) {
    // Limpiar la tabla existente si ya existe
    if (table) {
        layout->removeWidget(table);
        table->deleteLater();  // Eliminar el widget de la tabla
    }

    // Crear una nueva tabla con el número de filas igual al número de dispositivos y 5 columnas
    table = new QTableWidget(static_cast<int>(devices.size()), 6);
    table->setHorizontalHeaderLabels(
        QStringList() <<
                "Dispositivo" <<
                "Nombre" <<
                 "Dirección IP pública" <<
                  "Dirección IP privada" <<
                   "Localización" <<
                   "Servidor Vnc"
    );

    // Poblar la tabla con los datos de dispositivos
    int row = 0;
    for (const auto& device : devices) {
        // Columna alias
        QTableWidgetItem* aliasItem = new QTableWidgetItem(QString::fromStdString(device.alias));
        aliasItem->setTextAlignment(Qt::AlignLeft | Qt::AlignTop);
        aliasItem->setToolTip(QString::fromStdString(device.alias));
        table->setItem(row, 0, aliasItem);

        // Columna dispositivo
        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(device.name));
        table->setItem(row, 1, nameItem);

        // Columna IP pública
        QTableWidgetItem* ipAddressPublic = new QTableWidgetItem(QString::fromStdString(device.ip_address_public));
        table->setItem(row, 2, ipAddressPublic);

        // Columna IP privada
        QTableWidgetItem* ipAddressPrivate = new QTableWidgetItem(QString::fromStdString(device.ip_address_private));
        table->setItem(row, 3, ipAddressPrivate);

        // Columna coordenadas geográficas
        QTableWidgetItem* location = new QTableWidgetItem(QString::fromStdString(device.location));
        table->setItem(row, 4, location);

        // Nueva columna - Servidor VNC

        if (device.ip_address_private == "192.168.100.212" ||
            device.ip_address_private == "80.74.124.12") {

            QPushButton* vncButton = new QPushButton();
            QIcon vncIcon(":/drawable/play.png");  // Asegúrate de que la ruta al ícono sea correcta
            vncButton->setIcon(vncIcon);
            vncButton->setIconSize(QSize(20, 20));  // Ajustar el tamaño del ícono
            vncButton->setFlat(true);  // Botón sin borde
            table->setCellWidget(row, 5, vncButton);  // Insertar el botón en la celda
            QObject::connect(vncButton, &QPushButton::clicked, []() {
                qDebug() << "Hola Mundo";
            });
        } else {
            std::string message = "Servidor apagado";
            QTableWidgetItem* vncServer = new QTableWidgetItem(
                QString::fromStdString(message)
            );
            vncServer->setForeground(QBrush(QColor("#CB1D11")));
            table->setItem(row, 5, vncServer);
        }



        
        // Estilo y colores
        aliasItem->setForeground(QBrush(QColor("#FFFFFF")));  // Color del alias
        nameItem->setForeground(QBrush(QColor("#0000FF")));   // Color del nombre del dispositivo
        ipAddressPublic->setForeground(QBrush(QColor("#FFFFFF")));  // Color de la IP pública
        ipAddressPrivate->setForeground(QBrush(QColor("#0000FF"))); // Color de la IP privada
        location->setForeground(QBrush(QColor("#FFFFFF")));  // Color de la localización

        ++row;
    }

    // Ajustar tamaño de las columnas al contenido de los encabezados
    for (int col = 0; col < table->columnCount(); ++col) {
        table->resizeColumnToContents(col);
    }

    // Ajustar las filas al contenido
    table->resizeRowsToContents();

    // Ajustes interactivos
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    // Deshabilitar la edición de la tabla
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Configurar paleta de colores
    QPalette palette = table->palette();
    palette.setColor(QPalette::Base, QColor("#260006"));
    table->setPalette(palette);
    table->setAutoFillBackground(true);
    table->setBackgroundRole(QPalette::Base);

    // Aplicar estilo a la tabla y a las barras de desplazamiento
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


Home::Home(QWidget *parent) : QWidget(parent), table(nullptr) {
    
    devicesRepository = new DevicesRepositoryImp();

    std::string ALL = "ALL";
    // Obtener todos los dispositivos
    devices = devicesRepository->getDevice(ALL);

    // Establecer las propiedades de la ventana
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, QColor("#260006"));  // Fondo oscuro
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    layout = new QVBoxLayout(this);

    if (!devices.empty()) {
        // Crear la barra superior con campo de texto de búsqueda y botón
        QHBoxLayout* topLayout = new QHBoxLayout();
        textField = new QLineEdit(this);
        textField->setPlaceholderText("Buscar dispositivo (por Dispositivo)...");
        textField->setStyleSheet("QLineEdit { color: #ffffff; background-color: #390009; }");
        textField->setFixedWidth(400);

        button = new QPushButton("Buscar", this);
        button->setFixedWidth(150);

        // Conectar el botón y el evento de tecla "Enter" a la función de búsqueda
        connect(button, &QPushButton::clicked, this, &Home::searchDevice);
        connect(textField, &QLineEdit::returnPressed, this, &Home::searchDevice);

        // Añadir un espaciador a la izquierda para alinear a la derecha
        QSpacerItem* spacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
        topLayout->addItem(spacer);

        // Añadir el campo de texto y el botón al layout
        topLayout->addWidget(textField);
        topLayout->addWidget(button);
        
        layout->addLayout(topLayout);
        
        // Mostrar la tabla con dispositivos iniciales
        showDevicesTable(devices, layout, table);
    } else {
        // Mostrar mensaje si no hay dispositivos
        label = new QLabel("No se encontró información", this);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("QLabel { color : #ffdae0; }");
        layout->addWidget(label);
    }

    setLayout(layout);
}

// Función que maneja la búsqueda de dispositivos
void Home::searchDevice() {
    QString searchText = textField->text().trimmed();

    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Campo vacío", "Por favor, ingrese un dispositivo para buscar.");
    } else {
        // Obtener dispositivo específico basado en el alias
        std::string alias = searchText.toStdString();
        std::cout << alias << std::endl;
        std::vector<DevicesHandler> result = devicesRepository->getDevice(searchText.toStdString());

        if (result.empty()) {
            // Mostrar mensaje si no se encuentra el dispositivo
            QMessageBox::information(this, "No encontrado",
             "No se encontró un dispositivo llamado así. Escriba 'ALL' para visualizar todos los dispositivos");
        } else {
            // Actualizar la tabla con el resultado de la búsqueda
            showDevicesTable(result, layout, table);
        }
    }
}


