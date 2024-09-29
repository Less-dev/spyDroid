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
#include "../widgets/GoBack.h"
#include "../widgets/CardSms.h"
#include "QString"
#include "iostream"
#include "QScrollArea"
#include <QPainter>
#include <QDebug>
#include <QTimer>


SmsScreen::SmsScreen(QWidget *parent)
    : QWidget(parent),
      scrollArea(nullptr)  // Inicializamos el puntero a nullptr
{
    this->setMinimumSize(600, 500);

    // Configuración de la paleta de colores de fondo
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(20, 20, 20, 20);

    // Botón de regresar al Dashboard
    GoBackButton* goBackButton = new GoBackButton(this, QColor(255, 255, 255, 200));  // Color blanco pastel
    goBackButton->setOnClick([this]() {
        emit goToDashBoard();  // Emitir la señal cuando se hace clic
    });
    layout->addWidget(goBackButton, 0, Qt::AlignTop | Qt::AlignLeft);
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
    // Verificar si ya existe un scrollArea en el layout
    if (scrollArea != nullptr) {
        layout->removeWidget(scrollArea);  // Lo quitamos del layout
        delete scrollArea;  // Eliminamos la instancia anterior de scrollArea
        scrollArea = nullptr;  // Restablecemos el puntero
    }

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

    cardLayout->setContentsMargins(0, 30, 0, 30);

    scrollArea = new QScrollArea;  // Creamos una nueva instancia de scrollArea
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

    QPixmap background(":background");
    QSize scaledSize = background.size().scaled(800, 800, Qt::KeepAspectRatio);
    QRect targetRect((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2, scaledSize.width(), scaledSize.height());
    QPixmap scaledPixmap = background.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(targetRect, scaledPixmap);

    QPen pen(QColor("#FF0000"));
    pen.setWidth(4);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    int padding = 15;
    painter.drawRoundedRect(padding, padding, width() - 2 * padding, height() - 2 * padding, 20, 20);

    QWidget::paintEvent(event);
}