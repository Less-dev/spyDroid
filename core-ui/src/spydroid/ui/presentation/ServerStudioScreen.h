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

#ifndef SERVER_STUDIO_SCREEN_H
#define SERVER_STUDIO_SCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPaintEvent>

class ServerStudioScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ServerStudioScreen(QWidget *parent = nullptr);

signals:
    void goToHome();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVBoxLayout* layout;
};

#endif // SERVER_STUDIO_SCREEN_H
