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

#include "goBack.h"
#include <QIcon>
#include <QObject>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QColor>

QIcon recolorIcon(const QString& iconPath, const QColor& newColor) {
    // Cargar el QPixmap desde el archivo original del ícono
    QPixmap pixmap(iconPath);

    // Crear una imagen a partir del pixmap
    QImage image = pixmap.toImage();

    // Iterar sobre los píxeles para cambiar el color
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            // Obtener el color del píxel actual
            QColor color = image.pixelColor(x, y);

            // Si el píxel no es completamente transparente, aplicar el nuevo color
            if (color.alpha() > 0) {
                QColor pastelColor = newColor;
                pastelColor.setAlpha(color.alpha());  // Mantener la transparencia original
                image.setPixelColor(x, y, pastelColor);
            }
        }
    }

    // Crear un nuevo pixmap a partir de la imagen modificada
    QPixmap newPixmap = QPixmap::fromImage(image);

    // Retornar el QIcon con el pixmap recoloreado
    return QIcon(newPixmap);
}


// Implementación de la función goBack
QPushButton* goBack(QWidget* parent, const std::function<void()>& onClick)
{
    // Crear el botón y asignarlo al widget padre
    QPushButton* button = new QPushButton(parent);
    // Asignar el ícono al botón desde los recursos

    QColor pastelWhite(255, 255, 255, 200);  // Blanco pastel con un poco de transparencia
    QIcon icon = recolorIcon(":/drawable/goBack.png", pastelWhite);
    button->setIcon(icon);

    // Ajustar el tamaño del ícono para que ocupe todo el botón
    button->setIconSize(QSize(60, 30));

    // Ajustar el tamaño del botón a 80x40 píxeles
    button->setFixedSize(60, 30);

    // Eliminar cualquier margen o padding del botón
    button->setStyleSheet("border: none; padding: 0px; QPushButton { outline: none; }");

    // Conectar la señal de clic con la lambda o función recibida
    QObject::connect(button, &QPushButton::clicked, onClick);

    // Crear un efecto de opacidad
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(button);

    // Asegurarse de que la opacidad inicial sea 100% (1.0)
    opacityEffect->setOpacity(1.0);
    button->setGraphicsEffect(opacityEffect);

    // Oscurecer temporalmente el ícono cuando el botón se presiona
    QObject::connect(button, &QPushButton::pressed, [opacityEffect]() {
        // Reducir la opacidad del ícono (oscurecer)
        opacityEffect->setOpacity(0.5);  // 50% opacidad (oscurecido)

        // Restablecer la opacidad original después de 0.1 segundos
        QTimer::singleShot(100, [opacityEffect]() {
            opacityEffect->setOpacity(1.0);  // 100% opacidad (original)
        });
    });

    // Retornar el botón para agregarlo a la UI
    return button;
}
