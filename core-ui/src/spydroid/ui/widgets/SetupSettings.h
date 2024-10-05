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

#ifndef SETUP_SETTINGS_H
#define SETUP_SETTINGS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPaintEvent>
#include "BottomBarInstaller.h"
#include "BannerHorizontal.h"
#include "CardWidgetSettings.h"
#include <QString>
#include "../../../../../core-data/src/spydroid/data/local/SettingsManager.h"

class SetupSettings : public QWidget
{
    Q_OBJECT

public:
    explicit SetupSettings(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event);

signals:
    void nextPage();
    void backPage();
    
private:
    QVBoxLayout* layout;
    BannerHorizontal* topBarInstaller;
    CardWidgetSettings* content;
    BottomBarInstaller* bottomBarInstaller;
    SettingsManager* settingsManager;
    void onStartCheckBoxStateChanged(int state);
    void goToNextPage();
    void goToBackPage();
    void showToastMessage(const QString &message);
    bool isValidPath(const QString &path);
};

#endif // SETUP_SETTINGS_H
