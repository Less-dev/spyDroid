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

#include "GoBack.h"
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QVBoxLayout>

// Constructor del GoBackButton
GoBackButton::GoBackButton(QWidget* parent, const QColor& iconColor)
    : QWidget(parent), currentColor(iconColor)
{
    // Crear el botón
    button = new QPushButton(this);

    // Asignar el ícono al botón desde los recursos
    QIcon icon = createRecoloredIcon(":/icons/goBack.png", iconColor);
    button->setIcon(icon);

    // Ajustar el tamaño del ícono y el botón
    button->setIconSize(QSize(60, 30));
    button->setFixedSize(60, 30);
    button->setStyleSheet("border: none; padding: 0px; QPushButton { outline: none; }");

    // Crear el efecto de opacidad
    opacityEffect = new QGraphicsOpacityEffect(button);
    opacityEffect->setOpacity(1.0);
    button->setGraphicsEffect(opacityEffect);

    // Manejar la opacidad al hacer clic en el botón
    QObject::connect(button, &QPushButton::pressed, [this]() {
        opacityEffect->setOpacity(0.5);  // Reducir opacidad a 50%
        QTimer::singleShot(100, [this]() {
            opacityEffect->setOpacity(1.0);  // Restaurar opacidad a 100%
        });
    });

    // Layout opcional (si es necesario para usar en un layout externo)
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(button);
    layout->setContentsMargins(0, 0, 0, 0);  // Sin márgenes para permitir que el layout padre controle la posición
    setLayout(layout);
}

// Método para asignar la acción de clic
void GoBackButton::setOnClick(const std::function<void()>& onClick)
{
    QObject::connect(button, &QPushButton::clicked, onClick);
}

// Método para recolorear el ícono
void GoBackButton::recolorIcon(const QColor& newColor)
{
    currentColor = newColor;
    QIcon icon = createRecoloredIcon(":/icons/goBack.png", newColor);
    button->setIcon(icon);
}

// Función privada para recolorear el ícono
QIcon GoBackButton::createRecoloredIcon(const QString& iconPath, const QColor& color)
{
    QPixmap pixmap(iconPath);
    QImage image = pixmap.toImage();

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor pixelColor = image.pixelColor(x, y);
            if (pixelColor.alpha() > 0) {
                QColor newPixelColor = color;
                newPixelColor.setAlpha(pixelColor.alpha());
                image.setPixelColor(x, y, newPixelColor);
            }
        }
    }

    QPixmap newPixmap = QPixmap::fromImage(image);
    return QIcon(newPixmap);
}
