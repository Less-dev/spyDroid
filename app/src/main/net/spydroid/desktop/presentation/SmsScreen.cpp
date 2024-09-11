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

SmsScreen::SmsScreen(const QString& alias, QWidget *parent) : QWidget(parent), deviceAlias(alias)
{
    this->setMinimumSize(600, 500);
    
    // Configurar la paleta de colores del fondo
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, QColor("#260006"));  // El mismo color que la ventana principal
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    // Configurar el botón de volver atrás
    backPage = goBack(this, [this]() {
        emit goToHome();
    });


    // Crear un layout principal vertical

    smsRepository = new SmsRepositoryImp();
    std::vector<SmsHandler> smsList = smsRepository->getSms(alias.toStdString());
    layout = new QVBoxLayout(this);

    if (!smsList.empty())
    {

    layout->setContentsMargins(0, 30, 0, 30);  // Márgenes (izquierda, arriba, derecha, abajo)
    
    // Alinear los elementos hacia la parte superior del layout
    layout->setAlignment(Qt::AlignTop);

    // Añadir el botón de volver atrás al layout principal
    layout->addWidget(backPage);

    // Crear un contenedor para las tarjetas con un QVBoxLayout
    QWidget* cardContainer = new QWidget;
    QVBoxLayout* cardLayout = new QVBoxLayout(cardContainer);
    cardLayout->setAlignment(Qt::AlignTop);  // Alinea las tarjetas hacia arriba
    cardLayout->setSpacing(10);              // Espacio entre las tarjetas

    for (const auto& smsHandler : smsList) {
        // Crear una tarjeta de SMS (CardSms)
        CardSms* card = new CardSms(smsHandler, this);
        card->setStyleSheet("background-color: white;");  // Fondo blanco para las tarjetas

        // Crear un layout horizontal (QHBoxLayout) para centrar la tarjeta
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->setAlignment(Qt::AlignCenter);  // Centrar horizontalmente

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

    // Añadir el área de scroll al layout principal
    
    layout->addWidget(scrollArea);

    // Asignar el layout principal al widget
    } else {
        label = new QLabel("No se encontró información", this);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet(
            "QLabel { "
            "    color : white; "            
            "    font-weight: bold; "            
            "    font-size: 30px; "             
            "    background-image: url(:/drawable/background.png); "
            "    background-position: center; " 
            "    background-repeat: no-repeat; "
            "    width: 100px; "               
            "    height: 100px; "   
            "   padding-bottom: 150px; "            
            "}"
        );

        layout->addWidget(backPage);
        layout->addWidget(label);
    }
    


    this->setLayout(layout);
}
