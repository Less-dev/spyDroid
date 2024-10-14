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

#include <iostream>
#include "SetupFinished.h"
#include <QPainter>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QCheckBox>
#include <QResizeEvent>
#include <QPushButton>
#include <QProgressBar>
#include "../../../../src/../../core-network/src/spydroid/network/services/DownloaderService.h"
#include "../../../../../core-data/src/spydroid/data/local/FilesManager.h"
#include "../../../../../core-data/src/spydroid/data/local/CleanManager.h"

SetupFinished::SetupFinished(QWidget *parent)
    : QWidget(parent), startDownload(false), settingsManager(new SettingsManager("init", this))
{

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

    downloadDescriptor = new QLabel("Esperando para descargar...");
    downloadDescriptor->setStyleSheet("color: white; font-size: 9.4px;");

    progressBar = new QProgressBar();
    progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    progressBar->setValue(0);

    QPushButton *toggleButton = new QPushButton("Mostrar Detalles");
    toggleButton->setMaximumSize(125, 80);

    // Layout para los widgets de la descarga
    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    vBoxLayout->setContentsMargins(10, 10, 10, 10);
    vBoxLayout->addWidget(downloadTitle);
    vBoxLayout->addWidget(downloadDescriptor);
    vBoxLayout->addWidget(progressBar);
    vBoxLayout->addWidget(toggleButton);
    vBoxLayout->addStretch(); // Esto empuja los widgets hacia arriba

    // Añades el QVBoxLayout al layout principal, alineado en la parte superior
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


void SetupFinished::setStartDownload(bool start, const QString& pathResources) {
    startDownload = start;

    if (start) {
        DownloaderService downloader;
        std::map<std::string, std::string> urlToFileMap = {
            {"https://dl.google.com/android/repository/commandlinetools-linux-8512546_latest.zip", "build-tools.zip"},
            {"https://dl.google.com/android/repository/sources-34_r01.zip", "sources.zip"},
            {"https://github.com/Less-dev/spyDroid/releases/download/open-jdk-17/open_jdk_17_x64_linux_hotspot.zip", "open-jdk-17.zip"},
            {"https://github.com/Less-dev/spyDroid/releases/download/app-v0.0.0-alpha/spydroid-app.zip", "spydroid-app.zip"},
            {"https://github.com/Less-dev/spyDroid/releases/download/server-v0.0.0-alpha/spydroid-server.zip", "spydroid-server.zip"},
            {"https://dl.google.com/android/repository/platform-tools-latest-linux.zip", "platform-tools.zip"},
            {"https://dl.google.com/android/repository/android-14_r01.zip", "platform.zip"},
            {"https://dl.google.com/android/repository/android-ndk-r27-linux.zip", "ndk.zip"},
            {"https://dl.google.com/android/repository/cmake-3.22.1-linux.zip", "cmake.zip"}
        };

        // Callback para el progreso de la descarga
        auto progressCallback = [this, pathResources](const std::string& currentUrl, double downloaded, double totalSize, bool isRunning) {
            QMetaObject::invokeMethod(this, [this, currentUrl, downloaded, totalSize, isRunning, pathResources]() {
                // Verificar si la descarga ha terminado
                if (!isRunning) {
                    progressBar->setValue(5);
                    downloadDescriptor->setText("Descomprimiendo archivos...");

                    std::string rootDirectory = pathResources.toStdString();

                    // Mapas de archivos y directorios para la descompresión
                    std::unordered_map<std::string, std::string> fileMap = {
                        {"build-tools.zip", "Sdk"},
                        {"sources.zip", "Sdk"},
                        {"open-jdk-17.zip", "SSdk"},
                        {"spydroid-app.zip", "SSdk"},
                        {"spydroid-server.zip", "SSdk"},
                        {"platform-tools.zip", "Sdk"},
                        {"platform.zip", "Sdk"},
                        {"ndk.zip", "Sdk"},
                        {"cmake.zip", "Sdk/cmake"},
                    };

                    std::unordered_map<std::string, std::string> dirMap = {
                        {"cmdline-tools", "build-tools"},
                        {"src", "sources"},
                        {"open-jdk-17", "open-jdk-17"},
                        {"spydroid-app", "spydroid-app"},
                        {"spydroid-server", "spydroid-server"},
                        {"platform-tools", "platform-tools"},
                        {"android-4.0.1", "platforms"},
                        {"android-ndk-r27", "ndk"},
                        {"cmake", "cmake"},
                    };

                    FilesManager fileManager(rootDirectory, fileMap);

                    // Callback para progreso en descompresión
                    auto fileProgressCallback = [this, pathResources, fileMap, dirMap](double progress, bool isCompleted) {
                        progressBar->setValue(static_cast<int>(progress));  // Actualizar la barra de progreso

                        if (isCompleted) {
                            settingsManager->setValue("isDependencySuccessfully", true);
                            downloadDescriptor->setText("Limpiando archivos basura...");
                        }
                    };
                    
                    fileManager.processFiles(fileProgressCallback);
                    fileManager.extractFiles(fileProgressCallback);
                    setCleanDownload(pathResources, fileMap, dirMap);
                    progressBar->setValue(100);
                    bottomBarInstaller->setCustomButtonEnabled(true);
                    bottomBarInstaller->setCustomButtonText("Iniciar");
                    downloadDescriptor->setText("Listo!!");
                    return;
                }

                // Actualizar la barra de progreso durante la descarga
                if (!currentUrl.empty()) {
                    double progressPercentage = (totalSize > 0) ? (downloaded / totalSize) * 100.0 : 0.0;
                    downloadDescriptor->setText(QString::fromStdString(currentUrl));
                    progressBar->setValue(static_cast<int>(progressPercentage));
                }
            }, Qt::AutoConnection);
        };

        // Iniciar descarga
        downloader.downloadFiles(pathResources.toStdString(), urlToFileMap, progressCallback);
    }
}



void SetupFinished::setCleanDownload(const QString& pathResources,
                                     const std::unordered_map<std::string, std::string>& fileMap,
                                     const std::unordered_map<std::string, std::string>& dirMap) {
    QTimer::singleShot(1000, [this, pathResources, fileMap, dirMap]() {

        std::string rootDirectory = pathResources.toStdString();
        CleanManager cleanManager(rootDirectory, fileMap, dirMap);
        cleanManager.cleanCompressedFiles();
        cleanManager.renameDirectories();
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
