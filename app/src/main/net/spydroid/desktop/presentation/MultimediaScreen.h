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

#ifndef MULTIMEDIA_SCREEN_H
#define MULTIMEDIA_SCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "../components/GoBack.h"
#include <QPaintEvent>
#include <QString>

class MultimediaScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MultimediaScreen(QWidget *parent = nullptr);
    void setAlias(const QString& alias);

signals:
    void goToDashBoard();
    void goToImages(const QString& alias);
    void goToVideos(const QString& alias);
    void goToAudios(const QString& alias);
    void goToDocuments(const QString& alias);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVBoxLayout* layout;
    QGridLayout* gridLayout;
    QString deviceAlias;
    void loadAlias();
};

#endif // MULTIMEDIA_SCREEN_H