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

#include "SetupFinished.h"
#include <QPainter>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QCheckBox>
#include <QResizeEvent>
#include <QPushButton>
#include <QProgressBar>

SetupFinished::SetupFinished(QWidget *parent)
    : QWidget(parent)
{
// Creas el layout principal y lo asignas a la ventana
QVBoxLayout *layout = new QVBoxLayout(this);
this->setLayout(layout);
this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Creas el componente de la barra superior
    topBarInstaller = new BannerHorizontal();
    topBarInstaller->setTitle("Descargando Componentes");
    topBarInstaller->setDescription("Este proceso puede tardar unos minutos");
    layout->addWidget(topBarInstaller, 0, Qt::AlignTop);

    // Creas los componentes que se deben alinear a la derecha
    QLabel *downloadTitle = new QLabel("Iniciando Descarga...");
    downloadTitle->setStyleSheet("color: white; font-weight: bold; font-size: 13.5px;");

    QLabel *downloadDescriptor = new QLabel("https://dl.google.com/android/repository/emulator-linux64X86.zip");
    downloadDescriptor->setStyleSheet("color: white; font-size: 9.4px;");

    QProgressBar *progressBar = new QProgressBar();
    progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    progressBar->setValue(0);

    QPushButton *toggleButton = new QPushButton("Mostrar Detalles");
    toggleButton->setMaximumSize(125,80);
    // Creas un QHBoxLayout para alinear los elementos a la derecha
    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    vBoxLayout->setContentsMargins(10, 10, 10, 10);
    vBoxLayout->addWidget(downloadTitle);
    vBoxLayout->addWidget(downloadDescriptor);
    vBoxLayout->addWidget(progressBar);
    vBoxLayout->addWidget(toggleButton);
    vBoxLayout->addStretch(); // Esto empuja los widgets hacia la derecha

    // Añades el QHBoxLayout al layout principal, alineado en la parte superior
    layout->addLayout(vBoxLayout, 0);

    details = new CardWidgetInstaller();
    details->setVisible(false);
    layout->addWidget(details, 0, Qt::AlignCenter);

    bottomBarInstaller = new BottomBarInstaller();
    bottomBarInstaller->setCustomButtonText("Instalando");
    bottomBarInstaller->setBackButtonEnabled(false);
    bottomBarInstaller->setCustomButtonEnabled(false);
    bottomBarInstaller->setCancelButtonEnabled(true);
    layout->addWidget(bottomBarInstaller, 0, Qt::AlignBottom);

    // SIGNALS
    connect(bottomBarInstaller, &BottomBarInstaller::customButtonClicked, this, &SetupFinished::goToNextPage);
    connect(bottomBarInstaller, &BottomBarInstaller::backButtonClicked, this, &SetupFinished::goToBackPage);

    connect(toggleButton, &QPushButton::clicked, this, [this]() {
        details->setVisible(!details->isVisible());
    });
}


void SetupFinished::onStartCheckBoxStateChanged(int state)
{
    bool isChecked = (state == Qt::Checked);
    bottomBarInstaller->setCustomButtonEnabled(isChecked);
}


void SetupFinished::goToBackPage() {
    emit backPage();
}

void SetupFinished::goToNextPage() {
    emit nextPage();
}

void SetupFinished::paintEvent(QPaintEvent *event)
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


void SetupFinished::resizeEvent(QResizeEvent *event)
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
    int newHeight = static_cast<int>(availableHeightForContent * 0.50);

    // Establecer el nuevo tamaño de CardWidgetVerify
    details->setFixedSize(newWidth, newHeight);

    // Esto asegura que CardWidgetVerify no se superpondrá a las barras superior e inferior
}
