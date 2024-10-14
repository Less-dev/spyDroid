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

#ifndef CONFIGURATION_TEMPLATE_H
#define CONFIGURATION_TEMPLATE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPaintEvent>
#include <QComboBox>
#include <QScrollArea>
#include <QCheckBox>
#include <QList>
#include "HeaderConfigurationTemplate.h"

class ConfigurationTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigurationTemplate(QWidget *parent = nullptr);

signals:
    void goToMultimedia(const QString& alias);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void selectAllFunctionalities(bool checked);

private:
    QVBoxLayout* layout;
    HeaderConfigurationTemplate* headerTemplate;
    QComboBox* serverComboBox;
    QLineEdit* templateLineEdit;
    QList<QCheckBox*> functionalitiesCheckBoxes;
    void editImage();
};

#endif // CONFIGURATION_TEMPLATE_H
