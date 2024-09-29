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

#include "ItemBoard.h"
#include <QFont>
#include <QPainter>
#include <QTimer>

ItemBoard::ItemBoard(QWidget *parent) 
    : QWidget(parent), imageLabel(new QLabel(this)), textLabel(new QLabel(this)), clickTimer(new QTimer(this))
{
    // Crear el layout
    layout = new QVBoxLayout(this);

    // Ajustar espacio entre imagen y texto
    layout->setSpacing(5);

    // Aquí se asegura que los componentes internos se centren horizontalmente dentro del `ItemBoard`
    layout->setAlignment(Qt::AlignHCenter);  // Solo alineación horizontal centrada

    // Añadir las etiquetas (imagen arriba, texto abajo)
    layout->addWidget(imageLabel, 0, Qt::AlignHCenter);  // Centrado horizontalmente
    layout->addWidget(textLabel, 0, Qt::AlignHCenter);   // Centrado horizontalmente

    // Fuente del texto en negrita
    QFont font = textLabel->font();
    font.setBold(true);
    font.setPointSize(10);
    textLabel->setFont(font);

    textLabel->setMaximumWidth(67);  // Establecer un ancho máximo de 50 píxeles

    textLabel->setWordWrap(true);

    textLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    // Alinear el contenido dentro de cada QLabel
    imageLabel->setAlignment(Qt::AlignCenter);  // Centrar contenido de la imagen
    textLabel->setAlignment(Qt::AlignCenter);   // Centrar contenido del texto

    clickTimer->setInterval(80);
    clickTimer->setSingleShot(true);

    // Conectar el evento del temporizador para restaurar el color rojo claro
    connect(clickTimer, &QTimer::timeout, [this]() {
        changeColor(redColor);  // Restaurar color rojo original
    });

    // Conectar la señal de clic a la función de clic
    connect(this, &ItemBoard::clicked, [this]() {
        changeColor(darkRedColor);  // Cambiar a rojo oscuro temporalmente
        clickTimer->start();  // Iniciar el temporizador para volver a rojo claro
    });
}


void ItemBoard::setImage(const QPixmap &image) 
{
    // Crear un QPixmap redimensionado de 50x50
    QPixmap resizedImage = QPixmap(imageSize);
    resizedImage.fill(Qt::transparent);  // Fondo transparente

    // Usar QPainter para pintar la imagen en rojo
    QPainter painter(&resizedImage);
    painter.drawPixmap(0, 0, image.scaled(imageSize));
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(resizedImage.rect(), redColor);  // Rellenar la imagen con color rojo
    painter.end();

    imageLabel->setPixmap(resizedImage);
    imageLabel->setFixedSize(imageSize);  // Asegurar que el QLabel sea de 50x50
}

void ItemBoard::setText(const QString &text) 
{
    textLabel->setText(text);

    // Cambiar el color del texto a rojo
    QPalette palette = textLabel->palette();
    palette.setColor(QPalette::WindowText, redColor);
    textLabel->setPalette(palette);
}

void ItemBoard::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    // En este caso no necesitamos hacer un dibujo adicional, ya que el color del texto y la imagen
    // son manejados por los propios widgets (QLabel).
}

void ItemBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        changeColor(darkRedColor);
        clickTimer->start();

        QTimer::singleShot(100, this, [this]() {
            emit clicked();  // Emite la señal de clic
        });
    }
}

void ItemBoard::changeColor(const QColor &color)
{
    // Cambiar el color de la imagen
    QPixmap resizedImage = QPixmap(imageLabel->pixmap()->size());
    resizedImage.fill(Qt::transparent);

    QPainter painter(&resizedImage);
    painter.drawPixmap(0, 0, imageLabel->pixmap()->scaled(imageSize));

    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(resizedImage.rect(), color);
    painter.end();

    imageLabel->setPixmap(resizedImage);

    // Cambiar el color del texto
    QPalette palette = textLabel->palette();
    palette.setColor(QPalette::WindowText, color);
    textLabel->setPalette(palette);
}
