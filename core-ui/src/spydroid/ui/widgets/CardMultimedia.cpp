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
#include <QPainter>
#include <QBrush>


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
    imageLabel->setPixmap(pixmap.scaled(55, 55, Qt::KeepAspectRatio));  // Reducir tamaño a 40x40
    imageLabel->setFixedSize(75, 75);  // Fijar el tamaño del QLabel
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


void CardMultimedia::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Color de relleno con transparencia (negro con alfa 115)
    QBrush brush(QColor(0, 0, 0, 115));  // Color de fondo negro con transparencia
    painter.setBrush(brush);
    
    QPen pen(QColor("#800000"));  // Color del borde
    pen.setWidth(4);  // Grosor del borde
    painter.setPen(pen);
    
    // Dibujamos el rectángulo redondeado
    painter.drawRoundedRect(0, 0, width(), height(), 15, 15);
}
