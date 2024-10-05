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

// Archivo SetupVerify.h

#ifndef SETUP_VERIFY_H
#define SETUP_VERIFY_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>
#include "BannerHorizontal.h"
#include "CardWidgetVerify.h"
#include "BottomBarInstaller.h"
#include <QString>

class SetupVerify : public QWidget
{
    Q_OBJECT

public:
    explicit SetupVerify(QWidget *parent = nullptr);

    // Método setter para actualizar la ruta de instalación
    void setPath(const QString& path);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:
    void nextPage(const QString& path);  // Modificación de la señal para aceptar un QString
    void backPage();

private:
    QVBoxLayout* layout;
    BannerHorizontal* topBarInstaller;
    CardWidgetVerify* content;
    BottomBarInstaller* bottomBarInstaller;

    QString installationPath;  // Variable para almacenar la ruta de instalación

    void onStartCheckBoxStateChanged(int state);
    void goToNextPage();
    void goToBackPage();
};

#endif // SETUP_VERIFY_H

