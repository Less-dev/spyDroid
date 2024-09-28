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

#ifndef APK_STUDIO_SCREEN_H
#define APK_STUDIO_SCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QPalette>
#include <QPainter>
#include "../components/GoBack.h"
#include "../components/Terminal.h"
#include "../components/CodeEditor.h"
#include "../components/FileExplorer.h"
#include "../local/SettingsManager.h"
#include <QMenuBar>
#include <QTabBar>


class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

class ToolWindowBar : public QWidget {
    Q_OBJECT

public:
    explicit ToolWindowBar(QWidget *parent = nullptr);

signals:
    void goToHomeIconClicked();
    void fileIconClicked();
    void gitIconClicked();
    void terminalIconClicked();  // Señal para la interacción con el icono de terminal
    void playIconClicked();      // Señal para la interacción con el icono de play

private slots:
    void handleGoToHomeIconClick();
    void handleFileIconClick();
    void handleGitIconClick();
    void handleTerminalIconClick();
    void handlePlayIconClick();
};


class ApkStudioScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ApkStudioScreen(QWidget *parent = nullptr);

signals:
    void goToHome();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:

    // Options Lateral Left from the view
    void toggleGoToHome();
    void toggleFileExplorer();
    void toggleGit();
    void toggleTerminal();
    void togglePlay();

    // Option menu bar (File)
    void newFile();
    void openFile();
    void saveFile();
    void onFileOpened(const QString &filePath);

private:
    QVBoxLayout* layout;
    CodeEditor* codeEditor;
    Terminal* terminal;
    FileExplorer* fileExplorer;
    bool altPressed = false;
    
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *newFileAction;
    QAction *openFileAction;
    QAction *saveFileAction;
    QString pathProject;
    SettingsManager* settingsManager;
    QList<QVariant> recentFiles;
    QTabBar* tabBar;
};

#endif // APK_STUDIO_SCREEN_H
