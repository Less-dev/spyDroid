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

#include "QString"
#include "iostream"
#include <QPainter>
#include <QDebug>
#include "MultimediaScreen.h"
#include "../widgets/GoBack.h"
#include "../widgets/CardMultimedia.h"

MultimediaScreen::MultimediaScreen(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(640, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    
    layout = new QVBoxLayout(this);  
    layout->setContentsMargins(20, 20, 20, 20);  
    
    GoBackButton* goBackButton = new GoBackButton(this, QColor(255, 255, 255, 200));
    
    goBackButton->setOnClick([this]() {
        emit goToDashBoard();
    });
    
    layout->addWidget(goBackButton, 0, Qt::AlignTop | Qt::AlignLeft);

    gridLayout = new QGridLayout();

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

    gridLayout->addWidget(cardImages, 0, 0);        // Row 0, Column 0
    gridLayout->addWidget(cardVideos, 0, 1);        // Row 0, Column 1
    gridLayout->addWidget(cardAudios, 1, 0);        // Row 1, Column 0
    gridLayout->addWidget(cardDocuments, 1, 1);     // Row 1, Column 1

    layout->addStretch();
    layout->addLayout(gridLayout);
    layout->addStretch();

    gridLayout->setAlignment(Qt::AlignCenter);
    gridLayout->setHorizontalSpacing(20);
    gridLayout->setVerticalSpacing(20);
    this->setLayout(layout);
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
    painter.setRenderHint(QPainter::Antialiasing);

    QPixmap background(":background");
    QSize scaledSize = background.size().scaled(800, 800, Qt::KeepAspectRatio);
    QRect targetRect((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2, scaledSize.width(), scaledSize.height());
    QPixmap scaledPixmap = background.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(targetRect, scaledPixmap);

    QPen pen(QColor("#FF0000"));
    pen.setWidth(4);
    painter.setPen(pen);

    QBrush brush(Qt::NoBrush);
    painter.setBrush(brush);

    int padding = 15;
    painter.drawRoundedRect(padding, padding, width() - 2 * padding, height() - 2 * padding, 20, 20);

    QWidget::paintEvent(event);
}