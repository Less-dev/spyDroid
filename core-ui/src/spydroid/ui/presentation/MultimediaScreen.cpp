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

#include "MultimediaScreen.h"
#include "../widgets/GoBack.h"
#include "../widgets/CardMultimedia.h"
#include "QString"
#include "iostream"
#include <QPainter>
#include <QDebug>

MultimediaScreen::MultimediaScreen(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(640, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));  // El mismo color que la ventana principal
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    
    layout = new QVBoxLayout(this);  // Layout principal (para centrar todo)
    layout->setContentsMargins(20, 20, 20, 20);  // Establecer márgenes del layout principal
    
    GoBackButton* goBackButton = new GoBackButton(this, QColor(255, 255, 255, 200));  // Color blanco pastel
    goBackButton->setOnClick([this]() {
        emit goToDashBoard();
        // Aquí puedes manejar el evento, por ejemplo, navegar hacia atrás
    });
    layout->addWidget(goBackButton, 0, Qt::AlignTop | Qt::AlignLeft);

    gridLayout = new QGridLayout();  // Layout en cuadrícula para las tarjetas

    CardMultimedia* cardImages = new CardMultimedia(
        ":/icons/images.png",
        "Imagenes",
        "Visualice imagenes de el dispositivo",
        [this]() {
            emit goToImages(deviceAlias);
        }
    );


    CardMultimedia* cardVideos = new CardMultimedia(
        ":/icons/videos.png",
        "Videos",
        "Visualice Videos de el dispositivo",
        [this]() {
            emit goToVideos(deviceAlias);
        }
    );

    CardMultimedia* cardAudios = new CardMultimedia(
        ":/icons/audios.png",
        "Audios",
        "Escuche audios de el dispositivo",
        [this]() {
            emit goToAudios(deviceAlias);
        }
    );

    CardMultimedia* cardDocuments = new CardMultimedia(
        ":/icons/documents.png",
        "Documentos",
        "Visualice Documentos de el dispositivo",
        [this]() {
            emit goToDocuments(deviceAlias);
        }
    );

    // Añadir widgets al QGridLayout en la posición que deseas
    gridLayout->addWidget(cardImages, 0, 0);  // Fila 0, Columna 0
    gridLayout->addWidget(cardVideos, 0, 1);  // Fila 0, Columna 1
    gridLayout->addWidget(cardAudios, 1, 0);  // Fila 1, Columna 0
    gridLayout->addWidget(cardDocuments, 1, 1);  // Fila 1, Columna 1

    // Centrar el gridLayout dentro del layout principal
    layout->addStretch();  // Añadir un estiramiento arriba para centrar verticalmente
    layout->addLayout(gridLayout);  // Añadir el layout en cuadrícula
    layout->addStretch();  // Añadir un estiramiento abajo para centrar verticalmente

    // Alineación horizontal del contenido en el gridLayout
    gridLayout->setAlignment(Qt::AlignCenter);  // Alinea todo el grid en el centro horizontal
    gridLayout->setHorizontalSpacing(20);  // Ajusta el espacio horizontal entre las tarjetas (opcional)
    gridLayout->setVerticalSpacing(20);    // Ajusta el espacio vertical entre las tarjetas (opcional)
    this->setLayout(layout);  // Establecer el layout principal para la ventana
}


void MultimediaScreen::setAlias(const QString& alias) {
    deviceAlias = alias;
    loadAlias();
}

void MultimediaScreen::loadAlias() {
    
}


void MultimediaScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // Activar suavizado de bordes

    // Dibujar la imagen de fondo centrada (sin cambios)
    QPixmap background(":background");
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