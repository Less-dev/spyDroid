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

#include "CardSms.h"
#include <QPainter>
#include <QBrush>
#include <QString>

CardSms::CardSms(const SmsHandler& smsHandler, QWidget *parent)
    : QWidget(parent)
{
    // Establecer máximo ancho
    this->setMaximumWidth(500);

    // Layout para organizar las etiquetas
    layout = new QVBoxLayout(this);

    // Creamos y configuramos las etiquetas
    date = new QLabel(QString("%1 sep 14:%1").arg(smsHandler.id), this);
    QFont dateFont;
    dateFont.setPointSize(18);  // Tamaño de la fuente: 25px
    dateFont.setBold(true);     // Fuente en negrita
    date->setFont(dateFont);

    // Color de la etiqueta de fecha (Blanco pastel)
    QPalette datePalette = date->palette();
    date->setAttribute(Qt::WA_TranslucentBackground); 
    datePalette.setColor(QPalette::WindowText, QColor("#F5F5F5"));
    date->setPalette(datePalette);

    sms = new QLabel(QString("%1").arg(QString::fromStdString(smsHandler.sms)), this);
    sms->setAttribute(Qt::WA_TranslucentBackground); 
    QFont smsFont;
    smsFont.setPointSize(13);   // Tamaño de la fuente: 17px
    smsFont.setItalic(true);    // Fuente en itálica
    sms->setFont(smsFont);

    // Color de la etiqueta sms (Gris claro)
    QPalette smsPalette = sms->palette();
    smsPalette.setColor(QPalette::WindowText, QColor("#D3D3D3"));
    sms->setPalette(smsPalette);

    // Ajuste de alineación justificada (alinear ambos lados del texto)
    sms->setWordWrap(true);  // Para que el texto no se corte
    sms->setAlignment(Qt::AlignJustify);

    // Añadimos las etiquetas al layout
    layout->addWidget(date);
    layout->addWidget(sms);

    // Establecemos el layout al widget
    this->setLayout(layout);

    // Ajuste de tamaño de acuerdo al contenido
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
}

void CardSms::paintEvent(QPaintEvent *event)
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
