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
#include <QGuiApplication>
#include <QFileDialog>
#include <QShortcut>
#include "../widgets/FileWidget.h"
#include <QDebug>
#include <QTabBar>
#include <QFileInfo>

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
    QPixmap pixmapBack(":icons/2_go_back.png");
    goToHomeIcon->setPixmap(pixmapBack);
    goToHomeIcon->setScaledContents(true);
    goToHomeIcon->setFixedSize(30, 30);
    layout->addWidget(goToHomeIcon);

    // Ícono de archivo (file.png)
    ClickableLabel *fileIcon = new ClickableLabel(this);
    QPixmap pixmapFile(":icons/file.png");
    fileIcon->setPixmap(pixmapFile);
    fileIcon->setScaledContents(true);
    fileIcon->setFixedSize(30, 30);
    layout->addWidget(fileIcon);

    // Ícono de Git (git.png)
    ClickableLabel *gitIcon = new ClickableLabel(this);
    QPixmap pixmapGit(":icons/git.png");
    gitIcon->setPixmap(pixmapGit);
    gitIcon->setScaledContents(true);
    gitIcon->setFixedSize(30, 30);
    layout->addWidget(gitIcon);

    layout->addStretch();  // Estiramiento para los siguientes íconos

    // Ícono de terminal (terminal.png)
    ClickableLabel *terminalIcon = new ClickableLabel(this);
    QPixmap pixmap1(":icons/terminal.png");
    terminalIcon->setPixmap(pixmap1);
    terminalIcon->setScaledContents(true);
    terminalIcon->setFixedSize(30, 30);
    layout->addWidget(terminalIcon);

    // Ícono de play (play.png)
    ClickableLabel *playIcon = new ClickableLabel(this);
    QPixmap pixmap2(":icons/run.png");
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


ApkStudioScreen::ApkStudioScreen(QWidget *parent) : QWidget(parent), settingsManager(new SettingsManager("ApkStudio", this)) {
    // Crear el layout principal con márgenes exteriores para el borde de la vista
    pathProject = settingsManager->getValue("projectPath").toString();
    recentFiles = settingsManager->getValue("recentFiles").toList();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    
    mainLayout->setContentsMargins(20, 20, 20, 20);  // Márgenes exteriores
    mainLayout->setSpacing(0);  // Sin espaciado entre widgets del layout principal
    menuBar = new QMenuBar(this);
    fileMenu = menuBar->addMenu("&Archivo");

    // Añadir acciones al menú Archivo
    newFileAction = new QAction("Nuevo Archivo", this);
    newFileAction->setShortcut(QKeySequence("Ctrl+N"));
    connect(newFileAction, &QAction::triggered, this, &ApkStudioScreen::newFile);

    openFileAction = new QAction("Abrir Archivo...", this);
    openFileAction->setShortcut(QKeySequence("Ctrl+O"));
    connect(openFileAction, &QAction::triggered, this, &ApkStudioScreen::openFile);

    saveFileAction = new QAction("Guardar", this);
    saveFileAction->setShortcut(QKeySequence("Ctrl+S"));
    connect(saveFileAction, &QAction::triggered, this, &ApkStudioScreen::saveFile);

    // Añadir las acciones al menú Archivo
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);

    // Añadir separador y más acciones según sea necesario
    fileMenu->addSeparator();

    QMenu *editMenu = menuBar->addMenu("&Editar");
    QMenu *viewMenu = menuBar->addMenu("&Vista");
   menuBar->setStyleSheet("QMenuBar { background-color: black; }"
                           "QMenuBar::item { color: white; }"
                           "QMenuBar::item:selected { background: #800000; }"
                           "QMenu { background-color: #333333; color: white; }"
                           "QMenu::item:selected { background: #555555; }");
    mainLayout->setMenuBar(menuBar);  // Asignar la barra de menú al layout principal

    // Barra lateral de herramientas (ToolWindowBar)
    ToolWindowBar *toolBar = new ToolWindowBar(this);
    toolBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);  // Fijo en tamaño
    mainLayout->addWidget(toolBar);  // Añadir la barra de herramientas al layout principal

    // Crear un layout contenedor para la barra lateral y el FileExplorer
    QVBoxLayout *sidebarLayout = new QVBoxLayout();
    sidebarLayout->setContentsMargins(0, 0, 0, 0);  // Sin márgenes
    sidebarLayout->setSpacing(0);  // Sin espaciado entre widgets

    // Contenedor para el FileExplorer (sin márgenes ni espaciado)
    fileExplorer = new FileExplorer();
    fileExplorer->setRootPath(pathProject);
    fileExplorer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);  // Fijo en tamaño vertical
    fileExplorer->setMinimumWidth(220);
    fileExplorer->setMaximumWidth(650);  // Ancho máximo de 600 px
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

    tabBar = new QTabBar();
    tabBar->setShape(QTabBar::RoundedNorth);  // Estilo de tabs redondeados
    tabBar->setDocumentMode(true);            // El modo de documento ajusta las pestañas a su contenido
    tabBar->setExpanding(false);
    tabBar->setTabsClosable(true);  
    
    tabBar->setStyleSheet(
        "QTabBar {"
        "   padding-bottom: 10px;"            // Espacio entre el QTabBar y el componente de abajo
        "}"
        "QTabBar::tab {"
        "   background: black;"               // Fondo negro para cada pestaña
        "   color: white;"                    // Color del texto en blanco
        "   border: 2px solid red;"           // Borde rojo de 2px
        "   border-radius: 7px;"             // Bordes redondeados
        "   padding: 7px;"                    // Espaciado dentro de cada pestaña
        "   margin-right: 10px;" 
        "}"
        "QTabBar::tab:selected {"
        "   background: #333333;"             // Fondo más oscuro para la pestaña seleccionada
        "}"
        "QTabBar::tab:hover {"
        "   background: #444444;"             // Fondo diferente al pasar el mouse
        "}"
        "QTabBar::close-button {"
        "   image: url(:/icons/close.png);"         // Imagen personalizada para el botón de cierre
        "   subcontrol-position: right;"      // Alineación del botón de cierre a la derecha
        "   subcontrol-origin: padding;"      // Asegura que el botón esté dentro del área de la pestaña
        "   margin-right: 10px;"               // Espacio final dentro de la pestaña
        "}"
    );

    for (const QVariant& file : recentFiles) {
        QFileInfo fileInfo(file.toString());
        int tabIndex = tabBar->addTab(fileInfo.fileName());  // Agregar la pestaña con el nombre recortado
        tabBar->setTabData(tabIndex, file.toString());       // Almacenar la ruta completa como datos de la pestaña
    }

    // Configurar el layout principal
    codeEditor = new CodeEditor();
    codeEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Inicialmente ocultar el codeEditor
    codeEditor->hide();

    // Configurar la lógica para manejar cuando se seleccionan pestañas
    connect(tabBar, &QTabBar::currentChanged, [=](int index) {
        if (index != -1) {  // Una pestaña válida está seleccionada
            QString filePath = tabBar->tabData(index).toString();  // Recuperar la ruta completa del archivo
            codeEditor->loadFile(filePath);  // Cargar el archivo en el CodeEditor
            codeEditor->show();  // Mostrar el CodeEditor si está oculto
        } else {
            codeEditor->hide();  // Si no hay pestaña seleccionada, ocultar el CodeEditor
        }
    });

connect(tabBar, &QTabBar::tabCloseRequested, [=](int index) {
    QString filePath = tabBar->tabData(index).toString();
    
    tabBar->removeTab(index);

    if (tabBar->count() == 0) {
        codeEditor->hide();
    }

    // Eliminar el archivo cerrado de recentFiles
    QVariantList recentFiles = settingsManager->getValue("recentFiles").toList();
    for (int i = recentFiles.size() - 1; i >= 0; --i) {
        if (recentFiles[i].toString() == filePath) {
            recentFiles.removeAt(i);  // Eliminar el archivo de la lista
        }
    }

    // Guardar el recentFiles actualizado en settings
    settingsManager->setValue("recentFiles", recentFiles);
});



    tabBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);  // Asegura que solo expanda en horizontal
    contentLayout->addWidget(tabBar, 0, Qt::AlignTop);
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
    QShortcut *openFileShortcut = new QShortcut(QKeySequence("Ctrl+O"), this);
    connect(openFileShortcut, &QShortcut::activated, this, &ApkStudioScreen::openFile);
    connect(fileExplorer, &FileExplorer::fileOpened, this, &ApkStudioScreen::onFileOpened);
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


void ApkStudioScreen::onFileOpened(const QString &filePath) {
    // Verificar si ya existe una pestaña con este archivo
    for (int i = 0; i < tabBar->count(); ++i) {
        if (tabBar->tabData(i).toString() == filePath) {
            tabBar->setCurrentIndex(i);  // Si ya está abierto, selecciona la pestaña
            return;
        }
    }

    // Si el archivo no está abierto, crea una nueva pestaña
    QFileInfo fileInfo(filePath);
    int tabIndex = tabBar->addTab(fileInfo.fileName());
    tabBar->setTabData(tabIndex, filePath);
    tabBar->setCurrentIndex(tabIndex);

    // Cargar el archivo en el editor de código
    codeEditor->loadFile(filePath);
    codeEditor->show();

    // Actualizar recentFiles sin duplicados
    QVariantList recentFiles = settingsManager->getValue("recentFiles").toList();
    if (!recentFiles.contains(filePath)) {
        recentFiles.append(filePath);
        settingsManager->setValue("recentFiles", recentFiles);
    }
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


void ApkStudioScreen::newFile() {
    // Lógica para nuevo archivo
}

void ApkStudioScreen::openFile() {
    QString selectedPath = QFileDialog::getExistingDirectory(this, tr("Seleccionar Directorio"), pathProject);

    // Verificar si el usuario seleccionó un directorio o canceló el diálogo
    if (!selectedPath.isEmpty()) {
        // Actualizar pathProject con el nuevo directorio seleccionado
        pathProject = selectedPath;

        // Guardar el nuevo pathProject en las preferencias utilizando SettingsManager
        settingsManager->setValue("projectPath", pathProject);

        // Actualizar el FileExplorer con la nueva ruta
        fileExplorer->setRootPath(pathProject);
        fileExplorer->setVisible(true);  // Asegurarse de que el FileExplorer esté visible
    }
    else {
        // El usuario canceló la selección, mantener el pathProject actual
    }
}


void ApkStudioScreen::saveFile() {
    // Lógica para guardar archivo
}


void ApkStudioScreen::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Alt) {
        altPressed = true;
    }
}

// Evento de tecla liberada
void ApkStudioScreen::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Alt && altPressed) {
        // Alternar la visibilidad de la barra de menú
        menuBar->setVisible(!menuBar->isVisible());
        altPressed = false;  // Restablecer el estado de altPressed
        update();  // Solicitar una actualización de la interfaz para reflejar los cambios en el paintEvent
    }
}

void ApkStudioScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Definir el relleno superior adicional de 15px cuando la barra de menús esté visible
    int topPadding = menuBar->isVisible() ? 15 : 0;

    // Dibujar el fondo de la ventana
    QPixmap background(":background");
    QSize scaledSize = background.size().scaled(800, 800, Qt::KeepAspectRatio);
    QRect targetRect((width() - scaledSize.width()) / 2,
                     (height() - scaledSize.height()) / 2 + topPadding,  // Ajuste vertical basado en el relleno superior
                     scaledSize.width(), scaledSize.height());
    QPixmap scaledPixmap = background.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(targetRect, scaledPixmap);

    // Configuración del pincel y estilo de rectángulo
    QPen pen(QColor("#FF0000"));
    pen.setWidth(4);
    painter.setPen(pen);

    QBrush brush(Qt::NoBrush);
    painter.setBrush(brush);

    // Definir el relleno de los bordes
    int padding = 15;
    int adjustedHeight = height() - 2 * padding - topPadding;
    adjustedHeight = adjustedHeight > 0 ? adjustedHeight : 1;  // Asegurar que la altura no sea negativa

    painter.drawRoundedRect(padding, padding + topPadding,  // Desplazar el rectángulo según el relleno superior
                            width() - 2 * padding, adjustedHeight, 20, 20);  // Ajustar la altura

    QWidget::paintEvent(event);
}
