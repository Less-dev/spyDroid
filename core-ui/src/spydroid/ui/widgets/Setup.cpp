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

#include "Setup.h"
#include <QPainter>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QCheckBox>




Setup::Setup(QWidget *parent)
    : QWidget(parent)
{
    // Crear el layout principal y establecer márgenes de 70px
    layout = new QHBoxLayout(this);
    layout->setContentsMargins(70, 70, 70, 70);
    layout->setSpacing(0); // Elimina el espacio extra entre widgets
    this->setLayout(layout);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    QHBoxLayout *imageLayout = new QHBoxLayout();

    // Crear QLabel para la imagen
    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap(":setup");  // Ruta al recurso de imagen
    imageLabel->setPixmap(pixmap);
    imageLabel->setMaximumWidth(300);
    imageLabel->setScaledContents(true);
    imageLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Agregar la imagen al layout horizontal
    imageLayout->addWidget(imageLabel, 0, Qt::AlignLeft | Qt::AlignTop);

    // Agregar el layout de la imagen al layout principal
    layout->addLayout(imageLayout);

    // Añadir expansor flexible para equilibrar el espacio entre la imagen y el contenido
    layout->addStretch();

    // Crear un layout vertical para el título, descripción y casilla
    QVBoxLayout *titleLayout = new QVBoxLayout();

    // Crear QLabel para el título "INSTALADOR"
    QLabel *titleLabel = new QLabel("BIENVENIDO A LA CONFIGURACIÓN DE SPYDROID", this);

    // Estilo del texto: color blanco, tamaño 20px y negrita
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: white;");

    // Alinear el título a la parte superior y centrado horizontalmente
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    // Agregar el título al layout vertical
    titleLayout->addWidget(titleLabel, 0, Qt::AlignTop | Qt::AlignHCenter);

    // Añadir espacio de 30px entre el título y la descripción
    titleLayout->addSpacing(100);

    // Crear QLabel para la descripción "Lorem ipsum"
    QLabel *descriptionLabel = new QLabel(
        "La configuración lo guiará a través de la instalación de spydroid. \n Se recomienda cerrar todas las demás aplicaciones antes de iniciar la instalación. Esto permitirá actualizar los archivos del sistema relevantes sin tener que reiniciar el equipo."
        ,
        this);

    // Estilo del texto: color blanco pastel y tamaño 12px
    QFont descriptionFont;
    descriptionFont.setPointSize(12);
    descriptionLabel->setFont(descriptionFont);
    descriptionLabel->setStyleSheet("color: #D3D3D3;");  // Color blanco pastel
    descriptionLabel->setWordWrap(true);  // Permitir que el texto sea multilínea
    descriptionLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    // Establecer un tamaño fijo de altura de 200px para la descripción
    titleLayout->addWidget(descriptionLabel, 0, Qt::AlignLeft | Qt::AlignTop);
    

    QCheckBox *startCheckBox = new QCheckBox("Empezar spydroid", this);
    startCheckBox->setFixedHeight(100);
    // Estilo del texto: color blanco pastel
    startCheckBox->setStyleSheet("color: #D3D3D3;");

    // Alinear la casilla de verificación a la izquierda
    titleLayout->addWidget(startCheckBox, 0, Qt::AlignLeft | Qt::AlignTop);

    // Añadir expansor para empujar el contenido hacia arriba
    titleLayout->addStretch();

    // Agregar el layout del título al layout principal
    layout->addLayout(titleLayout);

    // Añadir otro expansor para empujar el título y el contenido hacia el centro
    layout->addStretch();
}



void Setup::paintEvent(QPaintEvent *event)
{
    // Llamar al método de la clase base
    QWidget::paintEvent(event);

    // Crear un objeto QPainter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Configuración del pincel (brush) con transparencia
    QBrush brush(QColor(0, 0, 0, 205));  // Color negro con transparencia
    painter.setBrush(brush);

    // Configuración del bolígrafo (pen) para el borde
    QPen pen(QColor("#800000"));  // Color del borde (rojo oscuro)
    pen.setWidth(4);  // Ancho del borde
    painter.setPen(pen);

    // Dibujar un rectángulo redondeado con márgenes
    int margin = 70;
    painter.drawRoundedRect(margin, margin, width() - 2 * margin, height() - 2 * margin, 15, 15);
}
