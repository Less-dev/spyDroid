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

#include "SettingsTemplate.h"
#include <iostream>
#include <QPainter>
#include <QDebug>
#include <QScrollArea>
#include <QPainter>


SettingsTemplate::SettingsTemplate(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    bottomBar = new BottomBarInstaller();
    bottomBar->setCustomButtonText("Siguiente");
    bottomBar->setBackButtonEnabled(true);
    bottomBar->setCustomButtonEnabled(true);
    bottomBar->setCancelButtonEnabled(true);

    content = new ConfigurationTemplate();
    content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    layout->addWidget(content);
    layout->addWidget(bottomBar, 0, Qt::AlignBottom);

    connect(bottomBar, &BottomBarInstaller::customButtonClicked, this, &SettingsTemplate::goToNextPage);
    connect(bottomBar, &BottomBarInstaller::backButtonClicked, this, &SettingsTemplate::goToBackPage);
    connect(bottomBar, &BottomBarInstaller::cancelButtonClicked, this, &SettingsTemplate::goToCancel);

    setLayout(layout);
}


void SettingsTemplate::setTemplate(const QString& templateScreen) {
    templateCard = templateScreen;
    qDebug() << "Plantilla desde otra vista 2: "<< templateScreen;

}

void SettingsTemplate::goToNextPage() {
    emit nextPage(templateCard);
}

void SettingsTemplate::goToBackPage() {
    emit backPage(templateCard);
}

void SettingsTemplate::goToCancel() {
    emit cancel();
}