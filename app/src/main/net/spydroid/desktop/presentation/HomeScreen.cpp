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
#include "HomeScreen.h"
#include <iostream>
#include <QPainter>
#include "../components/ItemBoard.h"
#include <QDebug>

HomeScreen::HomeScreen(QWidget *parent) : QWidget(parent) {
    
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    
    // Crear el layout para HomeScreen
    layout = new QVBoxLayout(this);

    // Ajustar los márgenes del layout para que los elementos se posicionen
    layout->setContentsMargins(20, 20, 20, 20);  // Márgenes ajustados (izquierda, arriba, derecha, abajo)

    // Crear un widget contenedor para los ItemBoard
    QWidget *itemBoardContainer = new QWidget(this);
    QHBoxLayout *itemBoardLayout = new QHBoxLayout(itemBoardContainer);

    itemBoardLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop); // Alineación en la parte superior izquierda
    itemBoardLayout->setSpacing(10);  // Espaciado entre los widgets

    // Crear el componente ItemBoard y configurarlo
    ItemBoard *dashBoard = new ItemBoard(itemBoardContainer);
    dashBoard->setImage(QPixmap(":/icons/home.png"));
    dashBoard->setText("Panel");
    connect(dashBoard, &ItemBoard::clicked, [this]() {
        emit goToDashBoard();
    });

    ItemBoard *apkStudio = new ItemBoard(itemBoardContainer);
    apkStudio->setImage(QPixmap(":/icons/builder.png"));
    apkStudio->setText("APK Estudio");
    connect(apkStudio, &ItemBoard::clicked, [this]() {
        emit goToBuildApk();
    });


    // Añadir los ItemBoard al layout del contenedor
    itemBoardLayout->addWidget(dashBoard);
    itemBoardLayout->addWidget(apkStudio);

    // Aplicar el layout al contenedor
    itemBoardContainer->setLayout(itemBoardLayout);

    // Añadir el contenedor al layout principal de HomeScreen
    layout->addWidget(itemBoardContainer, 0, Qt::AlignLeft | Qt::AlignTop);

    // Aplicar el layout principal al widget
    setLayout(layout);
}


void HomeScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // Activar suavizado de bordes

    // Dibujar la imagen de fondo centrada (sin cambios)
    QPixmap background(":/icons/background.png");
    QSize scaledSize = background.size().scaled(800, 800, Qt::KeepAspectRatio);
    QRect targetRect((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2, scaledSize.width(), scaledSize.height());
    QPixmap scaledPixmap = background.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(targetRect, scaledPixmap);

    // Establecer el color y grosor del borde rojo
    QPen pen(QColor("#FF0000"));  // Color rojo para el borde
    pen.setWidth(4);  // Grosor del borde
    painter.setPen(pen);

    // Establecer un brush transparente para que solo se vea el borde
    QBrush brush(Qt::NoBrush);
    painter.setBrush(brush);

    // Dibujar un rectángulo redondeado con padding de 20px (para que no toque los bordes)
    int padding = 15;
    painter.drawRoundedRect(padding, padding, width() - 2 * padding, height() - 2 * padding, 20, 20);  // Bordes redondeados de 20px

    // Llamar al método base para asegurar que el evento de pintura continúe normalmente
    QWidget::paintEvent(event);
}
