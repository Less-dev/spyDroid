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
#include <QDebug>
#include <QTabBar>
#include <QFileInfo>
#include "ApkStudioScreen.h"
#include "../widgets/FileWidget.h"

ClickableLabel::ClickableLabel(QWidget *parent) : QLabel(parent) {
    setStyleSheet("ClickableLabel { background-color: transparent; }"
                  "ClickableLabel:hover { background-color: #5f2729; }"
                  "ClickableLabel:pressed { background-color: #5f2729; }");
}

void ClickableLabel::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}

ToolWindowBar::ToolWindowBar(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    ClickableLabel *goToHomeIcon = new ClickableLabel(this);
    QPixmap pixmapBack(":icons/2_go_back.png");
    goToHomeIcon->setPixmap(pixmapBack);
    goToHomeIcon->setScaledContents(true);
    goToHomeIcon->setFixedSize(30, 30);
    layout->addWidget(goToHomeIcon);

    ClickableLabel *fileIcon = new ClickableLabel(this);
    QPixmap pixmapFile(":icons/file.png");
    fileIcon->setPixmap(pixmapFile);
    fileIcon->setScaledContents(true);
    fileIcon->setFixedSize(30, 30);
    layout->addWidget(fileIcon);

    ClickableLabel *gitIcon = new ClickableLabel(this);
    QPixmap pixmapGit(":icons/git.png");
    gitIcon->setPixmap(pixmapGit);
    gitIcon->setScaledContents(true);
    gitIcon->setFixedSize(30, 30);
    layout->addWidget(gitIcon);

    layout->addStretch();

    ClickableLabel *terminalIcon = new ClickableLabel(this);
    QPixmap pixmap1(":icons/terminal.png");
    terminalIcon->setPixmap(pixmap1);
    terminalIcon->setScaledContents(true);
    terminalIcon->setFixedSize(30, 30);
    layout->addWidget(terminalIcon);

    ClickableLabel *playIcon = new ClickableLabel(this);
    QPixmap pixmap2(":icons/run.png");
    playIcon->setPixmap(pixmap2);
    playIcon->setScaledContents(true);
    playIcon->setFixedSize(30, 30);
    layout->addWidget(playIcon);

    connect(goToHomeIcon, &ClickableLabel::clicked, this, &ToolWindowBar::handleGoToHomeIconClick);
    connect(terminalIcon, &ClickableLabel::clicked, this, &ToolWindowBar::handleTerminalIconClick);
    connect(playIcon, &ClickableLabel::clicked, this, &ToolWindowBar::handlePlayIconClick);
    connect(fileIcon, &ClickableLabel::clicked, this, &ToolWindowBar::handleFileIconClick);
    connect(gitIcon, &ClickableLabel::clicked, this, &ToolWindowBar::handleGitIconClick);

    setFixedWidth(65);
}

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
    
    pathProject = settingsManager->getValue("projectPath").toString();
    ultFileOpen = settingsManager->getValue("ultFileOpen").toString();
    recentFiles = settingsManager->getValue("recentFiles").toList();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("#000000"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(0);
    menuBar = new QMenuBar(this);
    fileMenu = menuBar->addMenu("&Archivo");

    // Actions menu file
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

    fileMenu->addSeparator();

    QMenu *editMenu = menuBar->addMenu("&Editar");
    QMenu *viewMenu = menuBar->addMenu("&Vista");
   menuBar->setStyleSheet("QMenuBar { background-color: black; }"
                           "QMenuBar::item { color: white; }"
                           "QMenuBar::item:selected { background: #800000; }"
                           "QMenu { background-color: #333333; color: white; }"
                           "QMenu::item:selected { background: #555555; }");
    mainLayout->setMenuBar(menuBar);

    // Tool lateral options
    ToolWindowBar *toolBar = new ToolWindowBar(this);
    toolBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    mainLayout->addWidget(toolBar);

    QVBoxLayout *sidebarLayout = new QVBoxLayout();
    sidebarLayout->setContentsMargins(0, 0, 0, 0);
    sidebarLayout->setSpacing(0);

    fileExplorer = new FileExplorer();
    fileExplorer->setRootPath(pathProject);
    fileExplorer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    fileExplorer->setMinimumWidth(220);
    fileExplorer->setMaximumWidth(650);
    fileExplorer->setVisible(false);   
    sidebarLayout->addWidget(fileExplorer);

    QWidget *sidebarWidget = new QWidget(this);
    sidebarWidget->setLayout(sidebarLayout);
    mainLayout->addWidget(sidebarWidget);

    QVBoxLayout *contentLayout = new QVBoxLayout();
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(0);

    tabBar = new QTabBar();
    tabBar->setShape(QTabBar::RoundedNorth); 
    tabBar->setDocumentMode(true);
    tabBar->setExpanding(false);
    tabBar->setTabsClosable(true);  
    
    tabBar->setStyleSheet(
        "QTabBar {"
        "   padding-bottom: 10px;"           
        "}"
        "QTabBar::tab {"
        "   background: black;"                
        "   color: white;"                    
        "   border: 2px solid red;"           
        "   border-radius: 7px;"              
        "   padding: 7px;"                     
        "   margin-right: 10px;" 
        "}"
        "QTabBar::tab:selected {"
        "   background: #333333;"           
        "}"
        "QTabBar::tab:hover {"
        "   background: #444444;"            
        "}"
        "QTabBar::close-button {"
        "   image: url(:/icons/close.png);"        
        "   subcontrol-position: right;"     
        "   subcontrol-origin: padding;"     
        "   margin-right: 10px;"
        "}"
    );

    for (const QVariant& file : recentFiles) {
        QFileInfo fileInfo(file.toString());
        int tabIndex = tabBar->addTab(fileInfo.fileName());
        tabBar->setTabData(tabIndex, file.toString());
    }

    codeEditor = new CodeEditor();
    codeEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    codeEditor->hide();

    if (!ultFileOpen.isEmpty()) {
        codeEditor->loadFile(ultFileOpen);
        codeEditor->show();
            for (int i = 0; i < tabBar->count(); ++i) {
        if (tabBar->tabData(i).toString() == ultFileOpen) {
            tabBar->setCurrentIndex(i);
            break;
        }
    }
    } else {
        codeEditor->hide();
    }

    connect(tabBar, &QTabBar::currentChanged, [=](int index) {
        if (index != -1) {
            QString filePath = tabBar->tabData(index).toString();
            codeEditor->loadFile(filePath);
            codeEditor->show();
            settingsManager->setValue("ultFileOpen", filePath);  
        } else {
            codeEditor->hide();
        }
    });

    connect(tabBar, &QTabBar::tabCloseRequested, [=](int index) {
        QString filePath = tabBar->tabData(index).toString();

        tabBar->removeTab(index);

        if (tabBar->count() == 0) {
            codeEditor->hide();
            settingsManager->setValue("ultFileOpen", "");
        } else {
            int currentIndex = tabBar->currentIndex();
            if (currentIndex != -1) {
                QString newFilePath = tabBar->tabData(currentIndex).toString();
                settingsManager->setValue("ultFileOpen", newFilePath);
            }
        }

        QVariantList recentFiles = settingsManager->getValue("recentFiles").toList();
        for (int i = recentFiles.size() - 1; i >= 0; --i) {
            if (recentFiles[i].toString() == filePath) {
                recentFiles.removeAt(i);
            }
        }
        settingsManager->setValue("recentFiles", recentFiles);
    });

    tabBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    contentLayout->addWidget(tabBar, 0, Qt::AlignTop);
    codeEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contentLayout->addWidget(codeEditor);

    terminal = new Terminal(this);
    terminal->setMaximumHeight(500);
    terminal->setMinimumHeight(350);
    terminal->setVisible(false);
    terminal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    contentLayout->addWidget(terminal);

    QWidget *contentWidget = new QWidget(this);
    contentWidget->setLayout(contentLayout);
    mainLayout->addWidget(contentWidget);

    QShortcut *openFileShortcut = new QShortcut(QKeySequence("Ctrl+O"), this);
    connect(openFileShortcut, &QShortcut::activated, this, &ApkStudioScreen::openFile);
    connect(fileExplorer, &FileExplorer::fileOpened, this, &ApkStudioScreen::onFileOpened);
    connect(toolBar, &ToolWindowBar::goToHomeIconClicked, this, &ApkStudioScreen::toggleGoToHome);
    connect(toolBar, &ToolWindowBar::fileIconClicked, this, &ApkStudioScreen::toggleFileExplorer);
    connect(toolBar, &ToolWindowBar::gitIconClicked, this, &ApkStudioScreen::toggleGit);
    connect(toolBar, &ToolWindowBar::terminalIconClicked, this, &ApkStudioScreen::toggleTerminal);

    setMinimumSize(600, 500);
}


void ApkStudioScreen::toggleGoToHome() {
    emit goToHome();
}


void ApkStudioScreen::onFileOpened(const QString &filePath) {
    // Verify if does exists tab with de file
    for (int i = 0; i < tabBar->count(); ++i) {
        if (tabBar->tabData(i).toString() == filePath) {
            tabBar->setCurrentIndex(i);
            return;
        }
    }

    QFileInfo fileInfo(filePath);
    int tabIndex = tabBar->addTab(fileInfo.fileName());
    tabBar->setTabData(tabIndex, filePath);
    tabBar->setCurrentIndex(tabIndex);

    codeEditor->loadFile(filePath);
    codeEditor->show();

    // Update recentFiles unduplicated
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

}

void ApkStudioScreen::openFile() {
    QString selectedPath = QFileDialog::getExistingDirectory(this, tr("Seleccionar Directorio"), pathProject);

    if (!selectedPath.isEmpty()) {
        pathProject = selectedPath;

        settingsManager->setValue("projectPath", pathProject);

        fileExplorer->setRootPath(pathProject);
        fileExplorer->setVisible(true);
    }
    else {
        // User canceled the selection
    }
}


void ApkStudioScreen::saveFile() {
    // Save file
}


void ApkStudioScreen::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Alt) {
        altPressed = true;
    }
}

// Evento de tecla liberada
void ApkStudioScreen::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Alt && altPressed) {
        menuBar->setVisible(!menuBar->isVisible());
        altPressed = false;
        update();
    }
}

void ApkStudioScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int topPadding = menuBar->isVisible() ? 15 : 0;

    QPixmap background(":background");

    const int maxWidth = 800;
    const int maxHeight = 800;
    const qreal scaleFactor = 0.9;

    QSize maxSize(maxWidth, maxHeight);
    QSize scaledSize = background.size().scaled(this->size().boundedTo(maxSize), Qt::KeepAspectRatio);

    scaledSize.setWidth(scaledSize.width() * scaleFactor);
    scaledSize.setHeight(scaledSize.height() * scaleFactor);

    QRect targetRect((width() - scaledSize.width()) / 2,
                     (height() - scaledSize.height()) / 2 + topPadding,
                     scaledSize.width(), scaledSize.height());

    QPixmap scaledPixmap = background.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(targetRect, scaledPixmap);

    QPen pen(QColor("#FF0000"));
    pen.setWidth(4);
    painter.setPen(pen);

    QBrush brush(Qt::NoBrush);
    painter.setBrush(brush);

    int padding = 15;
    int adjustedHeight = height() - 2 * padding - topPadding;
    adjustedHeight = adjustedHeight > 0 ? adjustedHeight : 1;

    painter.drawRoundedRect(padding, padding + topPadding,
                            width() - 2 * padding, adjustedHeight, 20, 20);

    QWidget::paintEvent(event);
}
