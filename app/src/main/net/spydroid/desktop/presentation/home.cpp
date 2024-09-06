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
#include <iostream>
#include <QTableWidget>
#include <QHeaderView>
#include <QScroller>
#include <QMessageBox>

// Función para mostrar la tabla de dispositivos en el layout dado
void showDevicesTable(const std::vector<DevicesHandler>& devices, QVBoxLayout* layout, QTableWidget* &table) {
    // Limpiar la tabla existente si ya existe
    if (table) {
        layout->removeWidget(table);
        table->deleteLater();  // Eliminar el widget de la tabla
    }

    // Crear una nueva tabla con el número de filas igual al número de dispositivos y 2 columnas
    table = new QTableWidget(static_cast<int>(devices.size()), 2);
    table->setHorizontalHeaderLabels(QStringList() << "Alias" << "Dispositivo");

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

        aliasItem->setForeground(QBrush(QColor("#FFFFFF")));  // Color del alias
        nameItem->setForeground(QBrush(QColor("#0000FF")));   // Color del nombre del dispositivo

        ++row;
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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

    // Obtener todos los dispositivos
    devices = devicesRepository->getDevices();

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
        textField->setPlaceholderText("Buscar dispositivo (por alias)...");
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
        QMessageBox::warning(this, "Campo vacío", "Por favor, ingrese un alias para buscar.");
    } else {
        // Obtener dispositivo específico basado en el alias
        std::string alias = searchText.toStdString();
        std::cout << alias << std::endl;
        std::vector<DevicesHandler> result = devicesRepository->getDevice(searchText.toStdString());

        if (result.empty()) {
            // Mostrar mensaje si no se encuentra el dispositivo
            QMessageBox::information(this, "No encontrado",
             "No se encontró un dispositivo con ese alias. Escriba 'ALL' para visualizar todos los dispositivos");
        } else {
            // Actualizar la tabla con el resultado de la búsqueda
            showDevicesTable(result, layout, table);
        }
    }
}
