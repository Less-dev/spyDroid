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
    smsRepository = new SmsRepositoryImp();

    // Mostrar el mensaje de "Cargando..." al principio
    label = new QLabel("Cargando...", this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet(
        "QLabel { "
        "    color : white; "
        "    font-weight: bold; "
        "    font-size: 30px; "
        "}"
    );

    layout->addWidget(label);  // Mostrar "Cargando..." hasta que se carguen los datos
}

void SmsScreen::setAlias(const QString& alias)
{
    // Actualizar el alias del dispositivo y recargar los SMS
    deviceAlias = alias;
    loadSms();  // Volver a cargar los SMS con el nuevo alias
}

void SmsScreen::loadSms()
{
    // Mostrar "Cargando..." antes de hacer la operación
    label->setText("Cargando...");
    label->show();

    // Usar un QTimer para simular una operación asíncrona (como acceso a base de datos)
    QTimer::singleShot(500, this, [this]() {
        // Simulamos un retraso en la obtención de los datos
        std::vector<SmsHandler> smsList = smsRepository->getSms(deviceAlias.toStdString());

        // Limpiar el layout actual antes de cargar los nuevos SMS
        QLayoutItem* item;
        while ((item = layout->takeAt(1)) != nullptr) {  // Comenzamos en 1 para dejar el botón de volver intacto
            if (item->widget()) {
                delete item->widget();  // Eliminar los widgets existentes
            }
            delete item;  // Eliminar el layout item
        }

        // Si se encuentran SMS, cargar las tarjetas
        if (!smsList.empty()) {
            QWidget* cardContainer = new QWidget;
            cardContainer->setStyleSheet("background: transparent;");
            QVBoxLayout* cardLayout = new QVBoxLayout(cardContainer);
            cardLayout->setAlignment(Qt::AlignTop);
            cardLayout->setSpacing(10);

            // Crear una tarjeta por cada SMS
            for (const auto& smsHandler : smsList) {
                CardSms* card = new CardSms(smsHandler, this);

                // Centrar la tarjeta horizontalmente
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
            layout->addWidget(scrollArea);
        } else {
            // Si no hay SMS, mostrar un mensaje de "No se encontraron mensajes"
            label->setText("No se encontraron mensajes");
            label->show();  // Asegurar que el label se muestre
            layout->addWidget(label);  // Volver a añadir el label al layout
        }

        // Aplicar el layout actualizado
        this->setLayout(layout);
    });
}


void SmsScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Dibujar el fondo
    QPixmap background(":/images/background.png");
    QSize scaledSize = background.size().scaled(800, 800, Qt::KeepAspectRatio);
    QRect targetRect((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2, scaledSize.width(), scaledSize.height());
    QPixmap scaledPixmap = background.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(targetRect, scaledPixmap);

    // Dibujar un borde rojo alrededor del widget
    QPen pen(QColor("#FF0000"));
    pen.setWidth(4);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    int padding = 20;
    painter.drawRoundedRect(padding, padding, width() - 2 * padding, height() - 2 * padding, 20, 20);

    QWidget::paintEvent(event);
}