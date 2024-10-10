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

#ifndef SELECT_TEMPLATE_H
#define SELECT_TEMPLATE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPaintEvent>
#include "BottomBarInstaller.h"
#include "CardTemplate.h"

class SelectTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit SelectTemplate(QWidget *parent = nullptr);
    
signals:
    void nextPage(const QString& path);
    void backPage();
    void cancel();

private:
    QVBoxLayout* layout;
    CardTemplate* content;
    BottomBarInstaller* bottomBar;
    QString templateCard;
    void goToNextPage();
    void goToBackPage();
    void goToCancel();
};

#endif // SELECT_TEMPLATE_H