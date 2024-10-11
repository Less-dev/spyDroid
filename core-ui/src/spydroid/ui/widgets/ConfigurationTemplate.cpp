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

#include "ConfigurationTemplate.h"
#include <QPainter>

ConfigurationTemplate::ConfigurationTemplate(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    // Ajustar márgenes de acuerdo a los valores especificados
    int paddingVertical = height() * 0.10;  // 15% del alto
    int paddingHorizontal = width() * 0.25; // 25% del ancho
    layout->setContentsMargins(paddingHorizontal, paddingVertical, paddingHorizontal, paddingVertical);

    setLayout(layout);
}

void ConfigurationTemplate::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fondo negro semi-transparente
    QBrush brush(QColor(0, 0, 0, 115));  // Color de fondo negro con transparencia
    painter.setBrush(brush);

    // Pen para el borde
    QPen pen(QColor("#FF0000"));  // Color rojo para el borde
    pen.setWidth(4);
    painter.setPen(pen);

    // Calcular el padding dinámico para el borde del rectángulo
    int paddingHorizontal = width() * 0.20;  // 20% del ancho
    int paddingVertical = height() * 0.05;   // 10% de la altura

    // Dibujar rectángulo con bordes redondeados de 20px y el padding ajustado
    painter.drawRoundedRect(paddingHorizontal, paddingVertical, 
                            width() - 2 * paddingHorizontal, 
                            height() - 2 * paddingVertical, 20, 20);

    QWidget::paintEvent(event);
}
