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

#include "SetupSettings.h"
#include <QPainter>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QCheckBox>

SetupSettings::SetupSettings(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    content = new QHBoxLayout(this);
    content->setContentsMargins(20, 20, 20, 20);  // Márgenes más pequeños
    content->setSpacing(20);
    this->setLayout(layout);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    topBarInstaller = new BannerHorizontal();
    topBarInstaller->setTitle("Ajustes de Configuración");
    topBarInstaller->setDescription("Ubicaciones de instalación");
    layout->addWidget(topBarInstaller, 0, Qt::AlignTop);
    bottomBarInstaller = new BottomBarInstaller();
    bottomBarInstaller->setCustomButtonText("Siguiente");
    bottomBarInstaller->setBackButtonEnabled(true);
    bottomBarInstaller->setCustomButtonEnabled(false);
    bottomBarInstaller->setCancelButtonEnabled(true);
    layout->addWidget(bottomBarInstaller, 0, Qt::AlignBottom);
    content->addStretch();

    // SIGNALS
    connect(bottomBarInstaller, &BottomBarInstaller::customButtonClicked, this, &SetupSettings::goToNextPage);
    connect(bottomBarInstaller, &BottomBarInstaller::backButtonClicked, this, &SetupSettings::goToBackPage);
}

void SetupSettings::onStartCheckBoxStateChanged(int state)
{
    // El botón de "Siguiente" se habilita si el checkbox está seleccionado (estado "Qt::Checked")
    bool isChecked = (state == Qt::Checked);
    bottomBarInstaller->setCustomButtonEnabled(isChecked);
}


void SetupSettings::goToBackPage() {
    emit backPage();
}

void SetupSettings::goToNextPage() {
    emit nextPage();
}

void SetupSettings::paintEvent(QPaintEvent *event)
{
    // Llamar al método de la clase base
    QWidget::paintEvent(event);

    // Crear un objeto QPainter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Configuración del pincel (brush) con transparencia
    QBrush brush(QColor(0, 0, 0, 205));  // Color negro con transparencia
    painter.setBrush(brush);

    // Configuración del bolígrafo (pen) para el borde
    QPen pen(QColor("#800000"));  // Color del borde (rojo oscuro)
    pen.setWidth(4);  // Ancho del borde
    painter.setPen(pen);

    // Dibujar un rectángulo redondeado con márgenes
    int margin = 12.5;
    painter.drawRoundedRect(margin, margin, width() - 2 * margin, height() - 2 * margin, 15, 15);
}
