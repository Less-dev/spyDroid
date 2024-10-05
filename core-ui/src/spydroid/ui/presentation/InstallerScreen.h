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

#ifndef INSTALLER_SCREEN_H
#define INSTALLER_SCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPaintEvent>
#include "../widgets/Setup.h"
#include "../widgets/SetupSettings.h"
#include "../widgets/SetupVerify.h"
#include "../widgets/SetupFinished.h"
#include "../../../../../core-data/src/spydroid/data/local/SettingsManager.h"

class InstallerScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InstallerScreen(QWidget *parent = nullptr);
    
signals:
    void goToHome();
private:
    QVBoxLayout* layout;
    Setup* setup;
    SetupSettings* setupSettings;
    SetupVerify* setupVerify;
    SetupFinished* setupFinished;
    SettingsManager* settingsManager;
    void goToSetup();
    void goToSetupSettings();
    void goBackToSetupSettings();
    void goToSetupVerify(const QString& path);
    void goToFinished(const QString& path);
    void goToSpydroid();
};

#endif // INSTALLER_SCREEN_H
