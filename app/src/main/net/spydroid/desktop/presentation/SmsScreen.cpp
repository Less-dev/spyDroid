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
#include <QTimer>


SmsScreen::SmsScreen(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(600, 500);

    // Configuración de la paleta de colores de fondo
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(30, 30, 30, 30);

    // Botón de regresar al Dashboard
    GoBackButton* goBackButton = new GoBackButton(this, QColor(255, 255, 255, 200));  // Color blanco pastel
    goBackButton->setOnClick([this]() {
        emit goToDashBoard();  // Emitir la señal cuando se hace clic
    });
    layout->addWidget(goBackButton, 0, Qt::AlignTop | Qt::AlignLeft);

    // Inicializar repositorio de SMS

    // Mostrar el mensaje de "Cargando..." al principio
    /*
        label = new QLabel("Cargando...", this);
        label->setAlignment(Qt::AlignCenter);  // Centrar horizontal y verticalmente
        label->setStyleSheet(
            "QLabel { "
            "    color : #ff0000; "
            "    font-weight: bold; "
            "    font-size: 30px; "
            "}"
        );

    QVBoxLayout* centerLayout = new QVBoxLayout();  // Layout independiente para centrar el label

    QSpacerItem* topSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem* bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    centerLayout->addItem(topSpacer);
    centerLayout->addWidget(label);    
    centerLayout->addItem(bottomSpacer);

    layout->addLayout(centerLayout);*/
    setLayout(layout);

}

void SmsScreen::setAlias(const QString& alias)
{
    deviceAlias = alias;
    smsRepository = new SmsRepositoryImp();
    loadSms();
}


void SmsScreen::loadSms()
{
               
    std::vector<SmsHandler> smsList = smsRepository->getSms(deviceAlias.toStdString());

    QWidget* cardContainer = new QWidget;
    cardContainer->setStyleSheet("background: transparent;");
    QVBoxLayout* cardLayout = new QVBoxLayout(cardContainer);
    cardLayout->setAlignment(Qt::AlignTop);
    cardLayout->setSpacing(10);

    for (const auto& smsHandler : smsList) {
        CardSms* card = new CardSms(smsHandler, this);
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->setAlignment(Qt::AlignCenter);
        hLayout->addWidget(card);
        cardLayout->addLayout(hLayout);
    }

    // Añadir padding de 30px en los márgenes del contenedor de tarjetas
    cardLayout->setContentsMargins(0, 30, 0, 30);

    // Crear un área de scroll para hacer las tarjetas desplazables
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(cardContainer);
    scrollArea->setStyleSheet("background: transparent;");

    // Añadir el área de scroll al layout principal
    layout->addWidget(scrollArea, Qt::AlignTop | Qt::AlignCenter);
}





void SmsScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPixmap background(":/images/background.png");
    QSize scaledSize = background.size().scaled(800, 800, Qt::KeepAspectRatio);
    QRect targetRect((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2, scaledSize.width(), scaledSize.height());
    QPixmap scaledPixmap = background.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(targetRect, scaledPixmap);

    QPen pen(QColor("#FF0000"));
    pen.setWidth(4);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    int padding = 20;
    painter.drawRoundedRect(padding, padding, width() - 2 * padding, height() - 2 * padding, 20, 20);

    QWidget::paintEvent(event);
}