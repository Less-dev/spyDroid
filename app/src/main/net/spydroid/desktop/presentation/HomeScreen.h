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

#ifndef HomeScreen_H
#define HomeScreen_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include "../remote/domain/DevicesRepository.h"
#include "../remote/domain/InfoRepository.h"
#include "../remote/models/DevicesHandler.h"
#include "../remote/models/InfoHandler.h"
#include "../models/InformationMain.h"

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = nullptr);

private slots:
    void searchDevice();  // Slot para manejar la búsqueda
    void handleVncButtonClick();

signals:
    void goToMultimedia();

private:
    QVBoxLayout* layout;
    QLabel* label;
    QPushButton* button;
    QLineEdit* textField;
    QTableWidget* table;
    DevicesRepository* devicesRepository;
    std::vector<DevicesHandler> devices;
};

#endif // HomeScreen_H
