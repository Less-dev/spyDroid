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

#ifndef DASHBOARD_SCREEN_H
#define DASHBOARD_SCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPaintEvent>
#include "../widgets/GoBack.h"
#include "../../../../../core-data/src/spydroid/data/domain/DevicesRepository.h"
#include "../../../../../core-data/src/spydroid/data/domain/InfoRepository.h"
#include "../../../../../core-data/src/spydroid/data/domain/MultimediaRepository.h"
#include "../../../../../core-data/src/spydroid/data/models/DevicesHandler.h"
#include "../../../../../core-data/src/spydroid/data/models/InfoHandler.h"

class DashBoardScreen : public QWidget
{
    Q_OBJECT

public:
    explicit DashBoardScreen(QWidget *parent = nullptr);

private slots:
    void searchDevice();
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
    QPushButton* search;
    GoBackButton* goBackButton;
    QLineEdit* textField;
    QTableWidget* table;
    DevicesRepository* devicesRepository;
    InfoRepository* infoRepository;
    MultimediaRepository* multimediaRepository;
    std::vector<InfoHandler> infoHandler;
    std::vector<DevicesHandler> devices;
    void showEvent(QShowEvent* event);
    void updateDeviceTable();
    void showDevicesTable(const std::vector<DevicesHandler>& devices, QVBoxLayout* layout, QTableWidget* &table);
};

#endif // DASHBOARD_SCREEN_H
