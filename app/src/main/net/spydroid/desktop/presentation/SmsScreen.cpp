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

#include "SmsScreen.h"
#include "../components/goBack.h"
#include "QString"

SmsScreen::SmsScreen(QWidget *parent) : QWidget(parent)
{
    
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, QColor("#260006"));  // El mismo color que la ventana principal
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    
    backPage = goBack(this, [this]() {
        emit goToHome();
    });


    layout = new QVBoxLayout(this);

    label = new QLabel("Mensajes de texto", this);
    label->setAlignment(Qt::AlignCenter);

    layout->addWidget(backPage);
    layout->addWidget(label);
    // Establecer el layout para esta vista
    this->setLayout(layout);
}
