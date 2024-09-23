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



#include "SmsScreen.h"
#include "../components/GoBack.h"
#include "../components/CardSms.h"
#include "QString"
#include "iostream"
#include "QScrollArea"
#include <QPainter>
#include <QDebug>


SmsScreen::SmsScreen(const QString& alias, QWidget *parent) : QWidget(parent), deviceAlias(alias)
{
    this->setMinimumSize(600, 500);

    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, QColor("#000000"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    // Crear un layout principal vertical

    smsRepository = new SmsRepositoryImp();
    std::vector<SmsHandler> smsList = smsRepository->getSms(alias.toStdString());
    layout = new QVBoxLayout(this);

    GoBackButton* goBackButton = new GoBackButton(this, QColor(255, 255, 255, 200));  // Color blanco pastel
    goBackButton->setOnClick([this]() {
        emit goToDashBoard();
        // Aquí puedes manejar el evento, por ejemplo, navegar hacia atrás
    });
    layout->addWidget(goBackButton, 0, Qt::AlignTop | Qt::AlignLeft);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(30, 30, 30, 30);  // Establecer márgenes del layout principal

    if (!smsList.empty())
    {

    // Crear un contenedor para las tarjetas con un QVBoxLayout
    QWidget* cardContainer = new QWidget;
    cardContainer->setStyleSheet("background: transparent;"); 
    QVBoxLayout* cardLayout = new QVBoxLayout(cardContainer);
    cardLayout->setAlignment(Qt::AlignTop);  // Alinea las tarjetas hacia arriba
    cardLayout->setSpacing(10);              // Espacio entre las tarjetas

    for (const auto& smsHandler : smsList) {
        // Crear una tarjeta de SMS (CardSms)
        CardSms* card = new CardSms(smsHandler, this);
        // Crear un layout horizontal (QHBoxLayout) para centrar la tarjeta
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->setAlignment(Qt::AlignCenter);  // Centrar horizontalmente
        //hLayout->addSpacing(20);  // Ajusta el valor de 20 a la cantidad deseada de padding

        // Añadir la tarjeta al layout horizontal
        hLayout->addWidget(card);

        // Añadir el layout horizontal (con la tarjeta centrada) al layout de tarjetas
        cardLayout->addLayout(hLayout);
    }

    // Añadir padding de 30px en los márgenes del contenedor de tarjetas
    cardLayout->setContentsMargins(0, 30, 0, 30);

    // Crear un QScrollArea para hacer las tarjetas desplazables
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);  // Permitir que el contenido del área de scroll se redimensione
    scrollArea->setWidget(cardContainer);  // Asignar el contenedor de las tarjetas al área de scroll
    scrollArea->setStyleSheet("background: transparent;");
    // Añadir el área de scroll al layout principal
    
    layout->addWidget(scrollArea);

    // Asignar el layout principal al widget
    } else {
        label = new QLabel("No se encontraron mensajes", this);
        label->setAlignment(Qt::AlignCenter);  // Centrar horizontal y verticalmente
        label->setStyleSheet(
            "QLabel { "
            "    color : white; "
            "    font-weight: bold; "
            "    font-size: 30px; "
            "}"
        );

        // Crear un layout vertical para centrar el QLabel
        QVBoxLayout* centerLayout = new QVBoxLayout();  // Layout independiente para centrar el label

        // Añadir expansores arriba y abajo del QLabel para centrarlo verticalmente
        QSpacerItem* topSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QSpacerItem* bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        centerLayout->addItem(topSpacer);  // Añadir el espaciador superior
        centerLayout->addWidget(label);    // Añadir el QLabel
        centerLayout->addItem(bottomSpacer); // Añadir el espaciador inferior

        layout->addLayout(centerLayout);  // Añadir el layout centrado al layout principal
    }
    


    this->setLayout(layout);
}


void SmsScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // Activar suavizado de bordes

    // Dibujar la imagen de fondo centrada (sin cambios)
    QPixmap background(":/images/background.png");
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
    int padding = 20;
    painter.drawRoundedRect(padding, padding, width() - 2 * padding, height() - 2 * padding, 20, 20);  // Bordes redondeados de 20px

    // Llamar al método base para asegurar que el evento de pintura continúe normalmente
    QWidget::paintEvent(event);
}
