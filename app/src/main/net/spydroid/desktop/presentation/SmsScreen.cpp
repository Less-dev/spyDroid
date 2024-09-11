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
#include "../components/CardSms.h"
#include "QString"
#include "iostream"

SmsScreen::SmsScreen(const QString& alias, QWidget *parent) : QWidget(parent), deviceAlias(alias)
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
    layout->addWidget(backPage);

    // Cargar los mensajes basados en el alias pasado
    smsRepository = new SmsRepositoryImp();
    std::vector<SmsHandler> smsList = smsRepository->getSms(alias.toStdString());

    for (const auto& smsHandler: smsList) {
        CardSms* card = new CardSms(smsHandler, this);
        layout->addWidget(card);
    }
    this->setLayout(layout);
}
