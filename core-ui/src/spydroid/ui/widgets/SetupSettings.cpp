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

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>

// Definición del CardWidget
class CardWidget : public QWidget {
public:
    CardWidget(QWidget *parent = nullptr) : QWidget(parent) {
        // Configurar el marco (la tarjeta) con el borde superior ajustado
        QFrame *card = new QFrame(this);

        // Aplicar un margen negativo en el borde superior para desplazarlo hacia abajo
        card->setStyleSheet(
            "QFrame { border: 2px solid red; border-radius: 15px; background-color: black; "
            "margin-top: 10px; /* Desplazar el borde superior hacia abajo */ }"
        );

        card->setFixedSize(450, 150);

        // Título que sobresale de la parte superior y está alineado a la izquierda
        QLabel *title = new QLabel("Ubicación de instalación de spydroid", this);
        title->setStyleSheet(
            "QLabel { color: white; background-color: black; font-size: 16px; padding: 0 10px; }"
        );
        title->move(25, -2);  // Posicionarlo fuera del borde superior y a la izquierda
        title->raise();  // Asegurar que el título esté por encima de otros widgets

        // Layout vertical para centrar el contenido
        QVBoxLayout *layout = new QVBoxLayout(card);
        layout->setAlignment(Qt::AlignCenter);
        card->setLayout(layout);
    }
};

// Modificación en SetupSettings para centrar el CardWidget
SetupSettings::SetupSettings(QWidget *parent)
    : QWidget(parent)
{
    // Configurar layout principal
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    // Asegurar que el layout expanda para ocupar todo el espacio disponible
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Añadir la barra superior
    topBarInstaller = new BannerHorizontal();
    topBarInstaller->setTitle("Ajustes de Configuración");
    topBarInstaller->setDescription("Ubicaciones de instalación");
    layout->addWidget(topBarInstaller, 0, Qt::AlignTop);

    // Crear CardWidget y añadirlo centrado
    CardWidget* content = new CardWidget();
    content->setMinimumSize(450, 150);
    layout->addWidget(content, 0, Qt::AlignCenter);  // Alinear al centro del layout


    // Añadir la barra inferior
    bottomBarInstaller = new BottomBarInstaller();
    bottomBarInstaller->setCustomButtonText("Siguiente");
    bottomBarInstaller->setBackButtonEnabled(true);
    bottomBarInstaller->setCustomButtonEnabled(false);
    bottomBarInstaller->setCancelButtonEnabled(true);
    layout->addWidget(bottomBarInstaller, 0, Qt::AlignBottom);

    // Conectar señales
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
