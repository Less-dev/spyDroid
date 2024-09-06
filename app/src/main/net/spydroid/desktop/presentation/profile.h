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

#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "../components/goBack.h"
#include "../models/VncData.h"

static VncData vncData;

class Profile : public QWidget
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);

signals:
    void goToHome();  // Señal para navegar a la vista Home

private slots:
    void onConnectToVnc();  // Slot que se conecta al VNC

private:
    QPushButton* backPage;
    QPushButton* vncConnect;  // Botón para iniciar la conexión VNC
    QVBoxLayout* layout;
    QLabel* label;
};

#endif // PROFILE_H
