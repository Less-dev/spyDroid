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

#include "FileWidget.h"
#include <QDebug>
#include <QPainter>

// Constructor
FileWidget::FileWidget(const QString& filePath, QWidget* parent)
    : QWidget(parent), closeButton(nullptr), timer(new QTimer(this))
{
    // Obtenemos el nombre del archivo a partir de la ruta
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();

    // Widget contenedor para encapsular el texto y el botón juntos
    QWidget* container = new QWidget(this);

    // Layout horizontal para texto e ícono
    QHBoxLayout* layout = new QHBoxLayout(container);
    layout->setContentsMargins(10, 5, 10, 5);  // Márgenes alrededor del texto e ícono
    layout->setSpacing(5);  // Espacio entre el texto y el ícono

    // Etiqueta para mostrar el nombre del archivo
    QLabel* fileLabel = new QLabel(fileName, this);
    fileLabel->setStyleSheet("color: white; font-weight: 600;"); // 600 es semibold
    layout->addWidget(fileLabel);

    // Botón con el ícono de cerrar
    closeButton = new QPushButton(this);
    closeButton->setFixedSize(25, 25);
    closeButton->setIcon(QIcon(":/icons/close.png"));
    closeButton->setIconSize(QSize(25, 25));
    closeButton->setStyleSheet("background-color: transparent; border: none;");
    layout->addWidget(closeButton);

    // Ajustar el ancho dinámicamente según el contenido
    container->adjustSize();

    // Layout principal del FileWidget
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);  // Sin márgenes exteriores
    mainLayout->addWidget(container);  // Añadir el contenedor al layout principal

    // Ajustar el tamaño mínimo del FileWidget para ajustarse al contenido
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);  // Ajustar ancho dinámico y altura fija
    adjustSize();

    // Conectar la señal de clic del botón a la función onCloseClicked
    connect(closeButton, &QPushButton::clicked, this, &FileWidget::onCloseClicked);

    // Conectar el temporizador para restaurar la opacidad
    connect(timer, &QTimer::timeout, this, &FileWidget::restoreIconOpacity);
}

// Maneja el clic del botón de cerrar
void FileWidget::onCloseClicked()
{
    // Hacer semi-transparente el botón
    closeButton->setStyleSheet("background-color: transparent; border: none; opacity: 0.5;");
    
    // Iniciar un temporizador para restaurar la opacidad después de 80 ms
    timer->start(80);

    // Llamar a la función onClick() para manejar la lógica personalizada
    onClick();
}

// Restaura la opacidad del ícono de cerrar
void FileWidget::restoreIconOpacity()
{
    // Restaurar la opacidad completa
    closeButton->setStyleSheet("background-color: transparent; border: none; opacity: 1.0;");
    
    // Detener el temporizador
    timer->stop();
}

// Función virtual que puede ser sobrescrita por otras clases
void FileWidget::onClick()
{
    // Por defecto, emitimos la señal de cerrado
    emit closed();

    // Destruir el widget después de emitir la señal
    this->deleteLater();
}


void FileWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Color de relleno con transparencia (negro con alfa 115)
    QBrush brush(QColor(0, 0, 0, 115));  // Color de fondo negro con transparencia
    painter.setBrush(brush);
    
    QPen pen(QColor("#800000"));  // Color del borde
    pen.setWidth(4);  // Grosor del borde
    painter.setPen(pen);
    
    // Dibujamos el rectángulo redondeado
    painter.drawRoundedRect(0, 0, width(), height(), 15, 15);
}
