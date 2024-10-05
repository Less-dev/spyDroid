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
#include <QRegularExpressionMatch>
#include <QPainter>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QCheckBox>
#include <QResizeEvent>
#include <QTimer>
#include <QDebug>

// Modificación en SetupSettings para centrar el CardWidgetSettings
SetupSettings::SetupSettings(QWidget *parent)
    : QWidget(parent), settingsManager(new SettingsManager("init", this)) // Instancia SettingsManager
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
    content = new CardWidgetSettings();
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
    // Obtener el directorio almacenado en path_resources
    QString path = settingsManager->getValue("path_resources", "").toString();

    // Si el directorio está vacío, mostrar un mensaje en consola
    if (path.isEmpty()) {
        qDebug() << "La ruta de instalación no está configurada.";
        return;
    }

    // Verificar si la ruta contiene caracteres inválidos
    if (!isValidPath(path)) {
        qDebug() << "La ruta contiene caracteres inválidos.";
        return;
    }

    QDir dir(path);

    // Verificar si ya es el directorio SPYDROID
    if (dir.dirName() == "SPYDROID" && dir.exists()) {
        emit nextPage(path);  // Emitir la señal con el valor actual de path
        return;
    }

    // Emitir la señal para ir a la siguiente página con la ruta actual
    emit nextPage(path);
}


// Función para validar si el path contiene caracteres inválidos
bool SetupSettings::isValidPath(const QString &path) {
    // Definir caracteres no permitidos en los nombres de directorios
    QString invalidChars = R"([\\\'"*?<>|:´¨^¸.!¡])";

    // Usar una expresión regular para detectar caracteres no permitidos
    QRegularExpression regex(invalidChars);

    // Verificar si el path contiene caracteres no permitidos
    QRegularExpressionMatch match = regex.match(path);
    return !match.hasMatch();
}


void SetupSettings::showToastMessage(const QString &message) {
    QLabel *toast = new QLabel(this);
    toast->setText(message);
    toast->setStyleSheet("background-color: black; color: white; padding: 10px; border-radius: 5px;");
    toast->setAlignment(Qt::AlignCenter);

    QVBoxLayout *toastLayout = new QVBoxLayout(toast);
    layout->addWidget(toast, 0, Qt::AlignBottom);  // Agregar el toast al layout en la parte inferior

    // Configurar un temporizador para ocultar el toast después de 3 segundos
    QTimer::singleShot(3000, toast, &QLabel::deleteLater);
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


void SetupSettings::resizeEvent(QResizeEvent *event)
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
