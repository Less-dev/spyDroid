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

#ifndef CARD_MULTIMEDIA_H
#define CARD_MULTIMEDIA_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CardMultimedia : public QWidget {
    Q_OBJECT

public:
    // Constructor, recibe imagen, título, descripción y onClick (lambda)
    explicit CardMultimedia(const QString& imagePath, const QString& titleText, const QString& descriptionText, std::function<void()> onClick, QWidget* parent = nullptr);

    // Método para setear la imagen
    void setImage(const QString& imagePath);

    // Método para setear el título
    void setTitle(const QString& titleText);

    // Método para setear la descripción
    void setDescription(const QString& descriptionText);

private:
    QLabel* imageLabel;
    QLabel* titleLabel;
    QLabel* descriptionLabel;
    QPushButton* button;
    QVBoxLayout* mainLayout;
    QHBoxLayout* topLayout;
    QVBoxLayout* textLayout;

    void setupUI();
    std::function<void()> onClickAction;


protected:
    // Override para manejar el evento de click
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // CARD_MULTIMEDIA_H