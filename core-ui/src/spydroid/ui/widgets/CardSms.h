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

#ifndef CARD_SMS_H
#define CARD_SMS_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "../../../../../core-data/src/spydroid/data/models/SmsHandler.h"  // Incluimos la definición de SmsHandler

class CardSms : public QWidget
{
    Q_OBJECT

public:
    explicit CardSms(const SmsHandler& smsHandler, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel* date;
    QLabel* sms;
    QVBoxLayout* layout;
};

#endif // CARD_SMS_H
