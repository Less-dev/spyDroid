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

#include "SetupVerify.h"
#include <QPainter>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QCheckBox>
#include <QResizeEvent>


SetupVerify::SetupVerify(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    topBarInstaller = new BannerHorizontal();
    topBarInstaller->setTitle("Verificar Configuraciones");
    topBarInstaller->setDescription("Si desea verificar o cambiar alguna de las configuraciones de instalación, haga clic en Volver.");
    layout->addWidget(topBarInstaller, 0, Qt::AlignTop);

    layout->addStretch();
    content = new CardWidgetVerify();
    layout->addWidget(content, 0, Qt::AlignCenter);
    layout->addStretch();

    bottomBarInstaller = new BottomBarInstaller();
    bottomBarInstaller->setCustomButtonText("Finalizar");
    bottomBarInstaller->setBackButtonEnabled(true);
    bottomBarInstaller->setCustomButtonEnabled(true);
    bottomBarInstaller->setCancelButtonEnabled(true);
    layout->addWidget(bottomBarInstaller, 0, Qt::AlignBottom);

    connect(bottomBarInstaller, &BottomBarInstaller::customButtonClicked, this, &SetupVerify::goToNextPage);
    connect(bottomBarInstaller, &BottomBarInstaller::backButtonClicked, this, &SetupVerify::goToBackPage);
}

void SetupVerify::setPath(const QString& path) {
    installationPath = path;
    content->setPath(installationPath);
}

void SetupVerify::onStartCheckBoxStateChanged(int state) {
    bool isChecked = (state == Qt::Checked);
    bottomBarInstaller->setCustomButtonEnabled(isChecked);
}

void SetupVerify::goToBackPage() {
    emit backPage();
}

void SetupVerify::goToNextPage() {
    emit nextPage(installationPath);  // Emitir la señal con el valor de installationPath
}

void SetupVerify::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush(QColor(0, 0, 0, 205));
    painter.setBrush(brush);

    QPen pen(QColor("#800000"));
    pen.setWidth(4);  // Width border
    painter.setPen(pen);

    int margin = 12.5;
    painter.drawRoundedRect(margin, margin, width() - 2 * margin, height() - 2 * margin, 15, 15);
}

void SetupVerify::resizeEvent(QResizeEvent *event)
{
    // Llamar a la implementación base primero
    QWidget::resizeEvent(event);

    // Obtener el tamaño total disponible del widget SetupVerify
    QSize availableSize = event->size();

    // Obtener el tamaño ocupado por topBarInstaller y bottomBarInstaller
    int topBarHeight = topBarInstaller->sizeHint().height();
    int bottomBarHeight = bottomBarInstaller->sizeHint().height();

    // Calcular el espacio vertical disponible entre topBarInstaller y bottomBarInstaller
    int availableHeightForContent = availableSize.height() - topBarHeight - bottomBarHeight;

    // Calcular el 80% del ancho disponible
    int newWidth = static_cast<int>(availableSize.width() * 0.85);

    // Calcular el 55% del alto del espacio disponible para el contenido (entre las barras)
    int newHeight = static_cast<int>(availableHeightForContent * 0.85);

    // Establecer el nuevo tamaño de CardWidgetVerify
    content->setFixedSize(newWidth, newHeight);

    // Esto asegura que CardWidgetVerify no se superpondrá a las barras superior e inferior
}
