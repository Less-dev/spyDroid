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


#include "ApkStudioScreen.h"
#include <iostream>
#include <QPainter>
#include <QHBoxLayout>
#include "../widgets/CardOptions.h"
#include "../widgets/ItemBoard.h"
#include "../widgets/GoBack.h"
#include <QResizeEvent>


ApkStudioScreen::ApkStudioScreen(QWidget *parent) : QWidget(parent) {
    
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    
    layout = new QVBoxLayout(this);

    layout->setContentsMargins(20, 20, 20, 20);
    
    GoBackButton* goBackButton = new GoBackButton(this, QColor(255, 255, 255, 200));
    goBackButton->setOnClick([this]() {
        emit goToHome();
    });
    
    layout->addWidget(goBackButton, 0, Qt::AlignTop | Qt::AlignLeft);

    options = new QHBoxLayout(this);
    options->setContentsMargins(100, 40, 100, 40);
    options->setSpacing(20);  // Agregar un poco de espacio entre las tarjetas

    // Creamos los dos CardOptions
    CardOptions *card1 = new CardOptions(this);
    CardOptions *card2 = new CardOptions(this);

    // Asignamos la imagen y descripción al primer CardOptions
    QPixmap bannerTemplates(":banner_templates");
    card1->setImage(bannerTemplates);
    card1->setDescription("Selecciona una plantilla entre las opciones, "
                          "ten en cuenta que no podrás modificar nada respecto a la interfaz de usuario.");

    // Asignamos la imagen y descripción al segundo CardOptions
    QPixmap bannerProgramming(":banner_programming");
    card2->setImage(bannerProgramming);
    card2->setDescription("Programa la interfaz de usuario, y personalízala libremente y sin restricciones.");

    // Establecemos las políticas de tamaño para que ambos tengan el mismo tamaño
    card1->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    card2->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    // Fijar un tamaño mínimo igual para ambos cards
    card1->setMinimumWidth(200);  // Ajusta este valor según el tamaño deseado
    card2->setMinimumWidth(200);

    connect(card1, &CardOptions::clicked, this, &ApkStudioScreen::goToggleTemplates);
    connect(card2, &CardOptions::clicked, this, &ApkStudioScreen::goToggleIDE);

    // Añadimos los dos CardOptions al layout horizontal
    options->addWidget(card1);
    options->addWidget(card2);

    // Aseguramos que el layout ocupe todo el espacio disponible
    options->setStretch(0, 1);
    options->setStretch(1, 1);

    // Añadimos el layout horizontal al layout principal
    layout->addLayout(options);

    setLayout(layout);
}


void ApkStudioScreen::goToggleIDE() {
    emit goToIDE();
}

void ApkStudioScreen::goToggleTemplates() {
    emit goToTemplates();
}

void ApkStudioScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPixmap background(":background");

    const int maxWidth = 800;
    const int maxHeight = 800;
    const qreal scaleFactor = 0.9;

    QSize maxSize(maxWidth, maxHeight);
    QSize scaledSize = background.size().scaled(this->size().boundedTo(maxSize), Qt::KeepAspectRatio);

    scaledSize.setWidth(scaledSize.width() * scaleFactor);
    scaledSize.setHeight(scaledSize.height() * scaleFactor);

    QRect targetRect((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2, 
                     scaledSize.width(), scaledSize.height());

    QPixmap scaledPixmap = background.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(targetRect, scaledPixmap);

    QPen pen(QColor("#FF0000"));
    pen.setWidth(4);
    painter.setPen(pen);

    QBrush brush(Qt::NoBrush);
    painter.setBrush(brush);

    int padding = 15;
    painter.drawRoundedRect(padding, padding, width() - 2 * padding, height() - 2 * padding, 20, 20);  // Bordes redondeados de 20px
    
    QWidget::paintEvent(event);
}

void ApkStudioScreen::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);

    // Obtenemos el tamaño actual de la ventana
    int currentWidth = this->width();
    int currentHeight = this->height();
    
    // Calculamos los márgenes en proporción al tamaño de la ventana
    int leftRightMargin = currentWidth * 0.05;  // 10% del ancho
    int topBottomMargin = currentHeight * 0.08;  // 8% de la altura

    // Establecemos los márgenes dinámicamente
    options->setContentsMargins(leftRightMargin, topBottomMargin, leftRightMargin, topBottomMargin);
}
