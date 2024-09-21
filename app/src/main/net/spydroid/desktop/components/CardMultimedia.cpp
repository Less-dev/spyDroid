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



#include "CardMultimedia.h"
#include <QPixmap>
#include <QMouseEvent>

// Constructor modificado
CardMultimedia::CardMultimedia(
    const QString& imagePath,
    const QString& titleText,
    const QString& descriptionText,
    std::function<void()> onClick,
    QWidget* parent
    ) : QWidget(parent), onClickAction(onClick) {

    // Inicialización de los widgets y layout
    imageLabel = new QLabel(this);
    titleLabel = new QLabel(this);
    descriptionLabel = new QLabel(this);

    setImage(imagePath);
    setTitle(titleText);
    setDescription(descriptionText);

    setupUI();
}

// Método para setear la imagen
void CardMultimedia::setImage(const QString& imagePath) {
    QPixmap pixmap(imagePath);
    imageLabel->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio));  // Reducir tamaño a 40x40
    imageLabel->setFixedSize(55, 55);  // Fijar el tamaño del QLabel
}

// Método para setear el título
void CardMultimedia::setTitle(const QString& titleText) {
    titleLabel->setText(titleText);
}

// Método para setear la descripción
void CardMultimedia::setDescription(const QString& descriptionText) {
    descriptionLabel->setText(descriptionText);
    descriptionLabel->setWordWrap(true);  // Asegura que el texto se ajuste en varias líneas
}

// Configuración del UI
void CardMultimedia::setupUI() {
    // Ajustar tamaño dinámico
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // Layouts
    mainLayout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout();
    textLayout = new QVBoxLayout();

    // Estilo del título
    titleLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    titleLabel->setStyleSheet("padding: 0px; font-size: 30px; font-weight: bold; color: #f8f9fa;");

    // Estilo de la descripción
    descriptionLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);  // Alinear la descripción a la izquierda
    descriptionLabel->setStyleSheet("padding: 0px; font-size: 20px; color: #d3d3d3;");

    // Configuraciones de la imagen
    imageLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    imageLabel->setStyleSheet("padding-left: 10px;");

    // Añadir los widgets al layout
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(descriptionLabel);
    topLayout->addWidget(imageLabel);
    topLayout->addLayout(textLayout);
    mainLayout->addLayout(topLayout);

    setLayout(mainLayout);
}


// Método para manejar el evento de click
void CardMultimedia::mousePressEvent(QMouseEvent* event) {
    if (onClickAction) {
        onClickAction(); // Llamar a la lambda cuando se haga click en el componente
    }
    QWidget::mousePressEvent(event); // Llamar al evento base
}
