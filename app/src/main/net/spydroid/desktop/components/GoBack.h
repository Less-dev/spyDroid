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

#ifndef GOBACKBUTTON_H
#define GOBACKBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QIcon>
#include <QGraphicsOpacityEffect>

class GoBackButton : public QWidget
{
    Q_OBJECT

public:
    explicit GoBackButton(QWidget* parent = nullptr, const QColor& iconColor = QColor(255, 255, 255, 200));

    // Método para configurar el callback de clic
    void setOnClick(const std::function<void()>& onClick);

    // Método para recolorear el ícono
    void recolorIcon(const QColor& newColor);

private:
    QPushButton* button;
    QGraphicsOpacityEffect* opacityEffect;
    QColor currentColor;
    QIcon createRecoloredIcon(const QString& iconPath, const QColor& color);

};

#endif // GOBACKBUTTON_H