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

#ifndef TEMPLATE_SCREEN_H
#define TEMPLATE_SCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPaintEvent>
#include "../widgets/SelectTemplate.h"


class TemplateScreen : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateScreen(QWidget *parent = nullptr);
    
signals:
    void goToSpydroidStudio();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVBoxLayout* layout;
    SelectTemplate* selectTemplate;
    void goToSelectTemplate(const QString& templateScreen);
    void goToSettingsTemplate(const QString& templateScreen);
};

#endif // TEMPLATE_SCREEN_H
