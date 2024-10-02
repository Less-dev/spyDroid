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

#include "Setup.h"
#include <QPainter>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QCheckBox>

Setup::Setup(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    content = new QHBoxLayout(this);
    content->setContentsMargins(20, 20, 20, 20);  // Márgenes más pequeños
    content->setSpacing(20);
    this->setLayout(layout);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    QHBoxLayout *imageLayout = new QHBoxLayout();

    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap(":setup");
    imageLabel->setPixmap(pixmap);
    imageLabel->setMaximumWidth(300);
    imageLabel->setScaledContents(true);
    imageLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    imageLayout->addWidget(imageLabel, 0, Qt::AlignLeft | Qt::AlignTop);

    content->addLayout(imageLayout);
    content->addStretch();

    QVBoxLayout *titleLayout = new QVBoxLayout();

    QLabel *titleLabel = new QLabel("BIENVENIDO A LA CONFIGURACIÓN DE SPYDROID", this);
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: white;");
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    titleLabel->setWordWrap(true);  // Ajuste de línea automática

    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    titleLabel->setMinimumHeight(50);

    titleLayout->addWidget(titleLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    titleLayout->addSpacing(40);

    QLabel *descriptionLabelPart1 = new QLabel(
        "La configuración lo guiará a través de la instalación de spydroid.", this);
    QLabel *descriptionLabelPart2 = new QLabel(
        "Se recomienda cerrar todas las demás aplicaciones antes de iniciar la instalación. Esto permitirá actualizar los archivos del sistema relevantes sin tener que reiniciar el equipo.", this);

    QFont descriptionFont;
    descriptionFont.setPointSize(12);
    descriptionLabelPart1->setFont(descriptionFont);
    descriptionLabelPart1->setStyleSheet("color: #D3D3D3;");
    descriptionLabelPart1->setWordWrap(true);
    descriptionLabelPart1->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    descriptionLabelPart2->setFont(descriptionFont);
    descriptionLabelPart2->setStyleSheet("color: #D3D3D3;");
    descriptionLabelPart2->setWordWrap(true);
    descriptionLabelPart2->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Añadir ambos QLabel al content
    titleLayout->addWidget(descriptionLabelPart1, 0, Qt::AlignLeft | Qt::AlignTop);
    titleLayout->addWidget(descriptionLabelPart2, 0, Qt::AlignLeft | Qt::AlignTop);

    QCheckBox *startCheckBox = new QCheckBox("Empezar spydroid", this);
    startCheckBox->setFixedHeight(40);
    startCheckBox->setStyleSheet("color: #D3D3D3;");
    startCheckBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    titleLayout->addWidget(startCheckBox, 0, Qt::AlignLeft | Qt::AlignTop);
    titleLayout->addStretch();
    content->addLayout(titleLayout);

    bottomBarInstaller = new BottomBarInstaller();
    bottomBarInstaller->setCustomButtonText("Siguiente");
    bottomBarInstaller->setBackButtonEnabled(false);
    bottomBarInstaller->setCustomButtonEnabled(false);
    bottomBarInstaller->setCancelButtonEnabled(true);
    layout->addLayout(content);
    layout->addWidget(bottomBarInstaller);
    content->addStretch();
    connect(startCheckBox, &QCheckBox::stateChanged, this, &Setup::onStartCheckBoxStateChanged);
}

void Setup::onStartCheckBoxStateChanged(int state)
{
    // El botón de "Siguiente" se habilita si el checkbox está seleccionado (estado "Qt::Checked")
    bool isChecked = (state == Qt::Checked);
    bottomBarInstaller->setCustomButtonEnabled(isChecked);
}


void Setup::paintEvent(QPaintEvent *event)
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
