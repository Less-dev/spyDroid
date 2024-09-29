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

#ifndef ITEMBOARD_H
#define ITEMBOARD_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QMouseEvent>

class ItemBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ItemBoard(QWidget *parent = nullptr);

    // Setters for image and text
    void setImage(const QPixmap &image);
    void setText(const QString &text);

signals:
    // Signal for when the widget is clicked
    void clicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *imageLabel;
    QLabel *textLabel;
    QVBoxLayout *layout;
    QTimer *clickTimer;  // Timer to revert the color after click

    // Color constants
    const QColor redColor = QColor(255, 0, 0);
    const QColor darkRedColor = QColor(139, 0, 0);
    const QSize imageSize = QSize(35, 35);  // Size for the image

    void changeColor(const QColor &color);
};

#endif // ITEMBOARD_H
