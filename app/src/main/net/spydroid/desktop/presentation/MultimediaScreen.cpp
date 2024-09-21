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
#include "../components/GoBack.h"
#include "../components/CardMultimedia.h"
#include "QString"
#include "iostream"
#include <QPainter>

MultimediaScreen::MultimediaScreen(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(640, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));  // El mismo color que la ventana principal
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    

    backPage = goBack(this, [this]() {
        emit goToHome();
    });

    layout = new QVBoxLayout(this);  // Layout principal (para centrar todo)
    gridLayout = new QGridLayout();  // Layout en cuadrícula para las tarjetas

    CardMultimedia* cardImages = new CardMultimedia(
        ":/drawable/images.png",
        "Imagenes",
        "Visualice imagenes de el dispositivo",
        []() {
            std::cout << "CLICK IMAGES!!" << std::endl;
        }
    );


    CardMultimedia* cardVideos = new CardMultimedia(
        ":/drawable/videos.png",
        "Videos",
        "Visualice Videos de el dispositivo",
        []() {
            std::cout << "CLICK VIDEOS!!" << std::endl;
        }
    );

    CardMultimedia* cardAudios = new CardMultimedia(
        ":/drawable/audios.png",
        "Audios",
        "Visualice AUDIOS de el dispositivo",
        []() {
            std::cout << "CLICK AUDIOS!!" << std::endl;
        }
    );

    CardMultimedia* cardDocuments = new CardMultimedia(
        ":/drawable/documents.png",
        "Documentos",
        "Visualice Documentos de el dispositivo",
        []() {
            std::cout << "CLICK DOCUMENTS!!" << std::endl;
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

void MultimediaScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap background(":/drawable/background.png");

    // Escalar la imagen al tamaño máximo permitido
    QSize scaledSize = background.size().scaled(800, 800, Qt::KeepAspectRatio);
    QRect targetRect((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2, scaledSize.width(), scaledSize.height());

    // Escalar el pixmap a la nueva tamaño
    QPixmap scaledPixmap = background.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Dibujar la imagen centrada
    painter.drawPixmap(targetRect, scaledPixmap);

    // Llamar al método base para asegurar que el evento de pintura continúe normalmente
    QWidget::paintEvent(event);
}