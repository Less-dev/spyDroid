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
    connect(setup, &Setup::nextPage, this, &InstallerScreen::depen);
    connect(setupSettings, &SetupSettings::backPage, this, &InstallerScreen::back);
    layout->addWidget(setup);
    layout->addWidget(setupSettings);
    setLayout(layout);
}


void InstallerScreen::depen() {
    setup->setVisible(false);
    setupSettings->setVisible(true);
}

void InstallerScreen::back() {
    setupSettings->setVisible(false);
    setup->setVisible(true);
}