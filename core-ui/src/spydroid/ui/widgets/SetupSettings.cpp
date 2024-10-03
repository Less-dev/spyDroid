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
#include "BrowserSetup.h"

class CardWidgetSettings : public QWidget {
public:
    CardWidgetSettings(QWidget *parent = nullptr) : QWidget(parent) {
        // Configurar el marco (la tarjeta) sin aplicar tamaños fijos, ajustándose al contenido
        QFrame *card = new QFrame(this);

        // Título que sobresale de la parte superior y está alineado a la izquierda
        QLabel *title = new QLabel("Ubicación de instalación de spydroid", this);
        title->setStyleSheet(
            "QLabel { color: white; background-color: black; font-size: 16px; padding: 0 10px; }"
        );
        title->move(25, -2);  // Posicionarlo fuera del borde superior y a la izquierda
        title->raise();  // Asegurar que el título esté por encima de otros widgets

        // Layout para el contenido dentro de la tarjeta
        QVBoxLayout *layout = new QVBoxLayout(card);
        layout->setContentsMargins(20, 70, 20, 20);  // Padding de 20px en todos los lados
        layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);  // Alinear los textos en la parte superior izquierda

        // Crear un QLabel para el texto principal (renombrado a textDescription)
        QLabel *textDescription = new QLabel("La ubicación especificada debe tener al menos 500 MB de espacio libre.", card);
        textDescription->setStyleSheet("QLabel { color: white; font-size: 20px; }");

        // Crear un segundo QLabel para el texto secundario
        QLabel *secondaryText = new QLabel("Haga click en Explorador para personalizar", card);
        secondaryText->setStyleSheet("QLabel { color: white; font-size: 13.5px; }");  // Tamaño de fuente más pequeño

        // Añadir los textos al layout
        layout->addWidget(textDescription);
        layout->addWidget(secondaryText);

        layout->addSpacing(20);

        // Añadir el componente BrowserSetup debajo de secondaryText
        BrowserSetup *browserSetup = new BrowserSetup(card);
        layout->addWidget(browserSetup);

        card->setLayout(layout);  // Aplicar el layout a la tarjeta
    }

protected:
    // Sobrescribir el paintEvent para dibujar el borde manualmente
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Establecer el color del borde y su grosor
        QPen pen(Qt::red, 2);  // Color rojo, grosor de 2px
        painter.setPen(pen);
        painter.setBrush(QBrush(Qt::black));  // Fondo negro

        // Dibujar el borde y el fondo con esquinas redondeadas
        QRect rect = this->rect();
        rect.adjust(1, 1, -1, -1);  // Ajustar para evitar que el borde sobresalga del widget
        painter.drawRoundedRect(rect, 15, 15);  // Esquinas redondeadas de 15px de radio

        // Llamar al evento base para continuar con el procesamiento predeterminado
        QWidget::paintEvent(event);
    }
};


// Modificación en SetupSettings para centrar el CardWidgetSettings
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

    // Crear CardWidgetSettings y añadirlo centrado
    layout->addStretch();
    CardWidgetSettings* content = new CardWidgetSettings();
    content->setMinimumSize(750, 300);
    layout->addWidget(content, 0, Qt::AlignCenter);  // Alinear al centro del layout
    layout->addStretch();

    // Añadir la barra inferior
    bottomBarInstaller = new BottomBarInstaller();
    bottomBarInstaller->setCustomButtonText("Siguiente");
    bottomBarInstaller->setBackButtonEnabled(true);
    bottomBarInstaller->setCustomButtonEnabled(true);
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
