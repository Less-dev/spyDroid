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

#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileInfo>
#include <QTimer>

class FileWidget : public QWidget
{
    Q_OBJECT

public:
    // Constructor que recibe la ruta del archivo
    explicit FileWidget(const QString& filePath, QWidget* parent = nullptr);

signals:
    // Señal que se emite cuando el widget se cierra
    void closed();

private slots:
    // Maneja el clic del botón de cerrar
    void onCloseClicked();

    // Se restaura la opacidad después de un tiempo
    void restoreIconOpacity();

protected:
    // Función virtual que puede ser sobrescrita
    virtual void onClick();

private:
    QPushButton* closeButton;  // Botón de cerrar
    QTimer* timer;             // Temporizador para restaurar la opacidad
    void paintEvent(QPaintEvent *event);
};

#endif // FILEWIDGET_H
