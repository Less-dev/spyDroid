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
#include <QPainter>


ApkStudioScreen::ApkStudioScreen(QWidget *parent) : QWidget(parent) {
    
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    
    layout = new QVBoxLayout(this);

    layout->setContentsMargins(30, 30, 30, 30);  // Márgenes ajustados (izquierda, arriba, derecha, abajo)
    
    goBackButton = new GoBackButton(this, QColor(255, 255, 255, 200));
    goBackButton->setOnClick([this]() {
        emit goToHome();
    });
    layout->addWidget(goBackButton, 0, Qt::AlignTop | Qt::AlignLeft);

    setLayout(layout);
}


void ApkStudioScreen::paintEvent(QPaintEvent *event) {
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

    QBrush brush(Qt::NoBrush);
    painter.setBrush(brush);

    int padding = 20;
    painter.drawRoundedRect(padding, padding, width() - 2 * padding, height() - 2 * padding, 20, 20);  // Bordes redondeados de 20px
    QWidget::paintEvent(event);
}
