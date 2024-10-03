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

#include <iostream>
#include <QPainter>
#include "InstallerScreen.h"
#include "../widgets/ItemBoard.h"
#include "../widgets/GoBack.h"
#include <QSpacerItem>


InstallerScreen::InstallerScreen(QWidget *parent) : QWidget(parent) {
    
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);
    setup = new Setup();
    setupSettings = new SetupSettings();
    setupSettings->setVisible(false);
    setupVerify = new SetupVerify();
    setupVerify->setVisible(false);
    setupFinished = new SetupFinished();
    setupFinished->setVisible(false);
    connect(setup, &Setup::nextPage, this, &InstallerScreen::goToSetupSettings);
    connect(setupSettings, &SetupSettings::backPage, this, &InstallerScreen::goToSetup);
    connect(setupSettings, &SetupSettings::nextPage, this, &InstallerScreen::goToSetupVerify);
    connect(setupVerify, &SetupVerify::backPage, this, &InstallerScreen::goBackToSetupSettings);
    connect(setupVerify, &SetupVerify::nextPage, this, &InstallerScreen::goToFinished);
    layout->addWidget(setup);
    layout->addWidget(setupSettings);
    layout->addWidget(setupVerify);
    layout->addWidget(setupFinished);
    setLayout(layout);
}

void InstallerScreen::goToSetup() {
    setupSettings->setVisible(false);
    setup->setVisible(true);
}

void InstallerScreen::goToSetupSettings() {
    setup->setVisible(false);
    setupSettings->setVisible(true);
}

void InstallerScreen::goBackToSetupSettings() {
    setupVerify->setVisible(false);
    setupSettings->setVisible(true);
}

void InstallerScreen::goToSetupVerify() {
    setupSettings->setVisible(false);
    setupVerify->setVisible(true);
}

void InstallerScreen::goToFinished() {
    setupVerify->setVisible(false);
    setupFinished->setVisible(true);
}