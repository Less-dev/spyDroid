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

#ifndef GENERAL_INFORMATION_CREEN_H
#define GENERAL_INFORMATION_SCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPaintEvent>
#include "../remote/domain/DevicesRepository.h"
#include "../remote/domain/InfoRepository.h"
#include "../remote/domain/MultimediaRepository.h"
#include "../remote/models/DevicesHandler.h"
#include "../remote/models/InfoHandler.h"

class GeneralInformationScreen : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralInformationScreen(QWidget *parent = nullptr);

private slots:
    void searchDevice();  // Slot para manejar la búsqueda
    void handleVncButtonClick();

signals:
    void goToMultimedia(const QString& alias);
    void goToSms(const QString& alias);
    void goToHome();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVBoxLayout* layout;
    QLabel* label;
    QPushButton* button;
    QLineEdit* textField;
    QTableWidget* table;
    DevicesRepository* devicesRepository;
    InfoRepository* infoRepository;
    MultimediaRepository* multimediaRepository;
    std::vector<InfoHandler> infoHandler;
    std::vector<DevicesHandler> devices;

    void showDevicesTable(const std::vector<DevicesHandler>& devices, QVBoxLayout* layout, QTableWidget* &table);
};

#endif // GENERAL_INFORMATION_SCREEN_H
