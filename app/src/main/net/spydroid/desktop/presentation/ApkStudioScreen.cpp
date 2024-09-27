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

#include "ApkStudioScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QStackedLayout>
#include "../local/SettingsManager.h"

// Constructor de ClickableLabel como antes
ClickableLabel::ClickableLabel(QWidget *parent) : QLabel(parent) {
    setStyleSheet("ClickableLabel { background-color: transparent; }"
                  "ClickableLabel:hover { background-color: #5f2729; }"
                  "ClickableLabel:pressed { background-color: #5f2729; }");
}

void ClickableLabel::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}

// ToolWindowBar como antes, sin cambios
ToolWindowBar::ToolWindowBar(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);


    ClickableLabel *goToHomeIcon = new ClickableLabel(this);
    QPixmap pixmapBack(":images/2_go_back.png");
    goToHomeIcon->setPixmap(pixmapBack);
    goToHomeIcon->setScaledContents(true);
    goToHomeIcon->setFixedSize(30, 30);
    layout->addWidget(goToHomeIcon);

    // Ícono de archivo (file.png)
    ClickableLabel *fileIcon = new ClickableLabel(this);
    QPixmap pixmapFile(":images/file.png");
    fileIcon->setPixmap(pixmapFile);
    fileIcon->setScaledContents(true);
    fileIcon->setFixedSize(30, 30);
    layout->addWidget(fileIcon);

    // Ícono de Git (git.png)
    ClickableLabel *gitIcon = new ClickableLabel(this);
    QPixmap pixmapGit(":images/git.png");
    gitIcon->setPixmap(pixmapGit);
    gitIcon->setScaledContents(true);
    gitIcon->setFixedSize(30, 30);
    layout->addWidget(gitIcon);

    layout->addStretch();  // Estiramiento para los siguientes íconos

    // Ícono de terminal (terminal.png)
    ClickableLabel *terminalIcon = new ClickableLabel(this);
    QPixmap pixmap1(":images/terminal.png");
    terminalIcon->setPixmap(pixmap1);
    terminalIcon->setScaledContents(true);
    terminalIcon->setFixedSize(30, 30);
    layout->addWidget(terminalIcon);

    // Ícono de play (play.png)
    ClickableLabel *playIcon = new ClickableLabel(this);
    QPixmap pixmap2(":images/run.png");
    playIcon->setPixmap(pixmap2);
    playIcon->setScaledContents(true);
    playIcon->setFixedSize(30, 30);
    layout->addWidget(playIcon);

    // Conectar las señales de clic
    connect(goToHomeIcon, &ClickableLabel::clicked, this, &ToolWindowBar::handleGoToHomeIconClick);
    connect(terminalIcon, &ClickableLabel::clicked, this, &ToolWindowBar::handleTerminalIconClick);
    connect(playIcon, &ClickableLabel::clicked, this, &ToolWindowBar::handlePlayIconClick);
    connect(fileIcon, &ClickableLabel::clicked, this, &ToolWindowBar::handleFileIconClick);
    connect(gitIcon, &ClickableLabel::clicked, this, &ToolWindowBar::handleGitIconClick);

    setFixedWidth(65);
}

// Manejo del clic del ícono de archivo (fileIcon)
void ToolWindowBar::handleGoToHomeIconClick() {
    emit goToHomeIconClicked();
}

void ToolWindowBar::handleFileIconClick() {
    emit fileIconClicked();
}

void ToolWindowBar::handleGitIconClick() {
    emit gitIconClicked();
}

void ToolWindowBar::handleTerminalIconClick() {
    emit terminalIconClicked();
}

void ToolWindowBar::handlePlayIconClick() {
    emit playIconClicked();
}


ApkStudioScreen::ApkStudioScreen(QWidget *parent) : QWidget(parent) {
    // Crear el layout principal con márgenes exteriores para el borde de la vista
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    
    mainLayout->setContentsMargins(20, 20, 20, 20);  // Márgenes exteriores
    mainLayout->setSpacing(0);  // Sin espaciado entre widgets del layout principal
    
    // Barra lateral de herramientas (ToolWindowBar)
    ToolWindowBar *toolBar = new ToolWindowBar(this);
    toolBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);  // Fijo en tamaño
    mainLayout->addWidget(toolBar);  // Añadir la barra de herramientas al layout principal

    // Crear un layout contenedor para la barra lateral y el FileExplorer
    QVBoxLayout *sidebarLayout = new QVBoxLayout();
    sidebarLayout->setContentsMargins(0, 0, 0, 0);  // Sin márgenes
    sidebarLayout->setSpacing(0);  // Sin espaciado entre widgets

    // Contenedor para el FileExplorer (sin márgenes ni espaciado)
    QString path = "/home/less/Downloads";
    fileExplorer = new FileExplorer(path);
    fileExplorer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);  // Fijo en tamaño vertical
    fileExplorer->setVisible(false);   // Inicialmente oculto
    sidebarLayout->addWidget(fileExplorer);  // Añadir el FileExplorer al layout contenedor

    // Crear un widget contenedor para mantener la barra lateral y el FileExplorer juntos
    QWidget *sidebarWidget = new QWidget(this);
    sidebarWidget->setLayout(sidebarLayout);  // Asignar el layout contenedor al widget
    mainLayout->addWidget(sidebarWidget);  // Añadir el widget contenedor al layout principal

    // Layout vertical para editor de código y terminal (sin márgenes ni espaciado)
    QVBoxLayout *contentLayout = new QVBoxLayout();
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(0);

    // Editor de código
    codeEditor = new CodeEditor();
    codeEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contentLayout->addWidget(codeEditor);

    // Terminal
    terminal = new Terminal(this);
    terminal->setMaximumHeight(500);
    terminal->setMinimumHeight(350);
    terminal->setVisible(false);  // Inicialmente oculto
    terminal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    contentLayout->addWidget(terminal);

    // Widget contenedor para la parte central (editor y terminal)
    QWidget *contentWidget = new QWidget(this);
    contentWidget->setLayout(contentLayout);
    mainLayout->addWidget(contentWidget);  // Añadir el contenedor de contenido al layout principal

    // Conectar las señales de clic de los íconos con los métodos de acción
    connect(toolBar, &ToolWindowBar::goToHomeIconClicked, this, &ApkStudioScreen::toggleGoToHome);
    connect(toolBar, &ToolWindowBar::fileIconClicked, this, &ApkStudioScreen::toggleFileExplorer);
    connect(toolBar, &ToolWindowBar::gitIconClicked, this, &ApkStudioScreen::toggleGit);
    connect(toolBar, &ToolWindowBar::terminalIconClicked, this, &ApkStudioScreen::toggleTerminal);

    setMinimumSize(600, 500);  // Establecer tamaño mínimo del widget principal
}


// Método para manejar la visibilidad del FileExplorer
void ApkStudioScreen::toggleGoToHome() {
    emit goToHome();
}

void ApkStudioScreen::toggleFileExplorer() {
    if (fileExplorer->isVisible()) {
        fileExplorer->setVisible(false);
    } else {
        fileExplorer->setVisible(true);
    }
    // Forzar la actualización del layout para que el editor y la terminal se redimensionen
    this->update();
}

void ApkStudioScreen::toggleGit() {
    // todo
}

void ApkStudioScreen::toggleTerminal() {
    if (terminal->isVisible()) {
        terminal->setVisible(false);
    } else {
        terminal->setVisible(true);
    }
    this->update();
}



void ApkStudioScreen::togglePlay() {
    
}

void ApkStudioScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPixmap background(":/images/background.png");
    QSize scaledSize = background.size().scaled(800, 800, Qt::KeepAspectRatio);
    QRect targetRect((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2, scaledSize.width(), scaledSize.height());
    QPixmap scaledPixmap = background.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(targetRect, scaledPixmap);

    QPen pen(QColor("#FF0000"));
    pen.setWidth(4);  
    painter.setPen(pen);

    QBrush brush(Qt::NoBrush);
    painter.setBrush(brush);

    int padding = 15;
    painter.drawRoundedRect(padding, padding, width() - 2 * padding, height() - 2 * padding, 20, 20);  // Bordes redondeados de 20px
    QWidget::paintEvent(event);
}
