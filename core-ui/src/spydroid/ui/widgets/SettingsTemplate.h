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

#ifndef SETTINGS_TEMPLATE_H
#define SETTINGS_TEMPLATE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPaintEvent>
#include "BottomBarInstaller.h"

class SettingsTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsTemplate(QWidget *parent = nullptr);
    void setTemplate(const QString& templateScreen);

signals:
    void nextPage(const QString& templateScreen);
    void backPage(const QString& templateScreen);
    void cancel();

private:
    QVBoxLayout* layout;
    //CardTemplate* content;
    BottomBarInstaller* bottomBar;
    QString templateCard;
    void goToNextPage();
    void goToBackPage();
    void goToCancel();
};

#endif // SETTINGS_TEMPLATE_H