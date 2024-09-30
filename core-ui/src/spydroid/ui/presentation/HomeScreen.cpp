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
#include "../widgets/ItemBoard.h"
#include <QDebug>

HomeScreen::HomeScreen(QWidget *parent) : QWidget(parent) {
    
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    
    layout = new QVBoxLayout(this);

    layout->setContentsMargins(20, 20, 20, 20);

    QWidget *itemBoardContainer = new QWidget(this);
    QHBoxLayout *itemBoardLayout = new QHBoxLayout(itemBoardContainer);

    itemBoardLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    itemBoardLayout->setSpacing(10);

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


    itemBoardLayout->addWidget(dashBoard);
    itemBoardLayout->addWidget(apkStudio);

    itemBoardContainer->setLayout(itemBoardLayout);

    layout->addWidget(itemBoardContainer, 0, Qt::AlignLeft | Qt::AlignTop);

    setLayout(layout);
}


void HomeScreen::paintEvent(QPaintEvent *event) {
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
