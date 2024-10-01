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

#ifndef SETUP_H
#define SETUP_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPaintEvent>  // Incluir para manejar el paintEvent

class Setup : public QWidget
{
    Q_OBJECT

public:
    // Constructor
    explicit Setup(QWidget *parent = nullptr);

protected:
    // Método protegido para manejar el evento de pintura
    void paintEvent(QPaintEvent *event) override;

private:
    // Layout principal del contenedor
    QHBoxLayout* layout;
};

#endif // CONTAINER_SETUP_H
