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

#include "FileExplorer.h"
#include <QDir>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QApplication>
#include <QHeaderView>
#include "../../../../../core-data/src/spydroid/data/local/SettingsManager.h"

FileExplorer::FileExplorer(const QString &directoryPath, QWidget *parent) : QWidget(parent)
{
    // Crear el modelo de sistema de archivos
    fileModel = new QFileSystemModel(this);

    // Verificar que la ruta proporcionada sea válida
    QString validPath = directoryPath;
    if (!QDir(validPath).exists()) {
        validPath = QDir::homePath();  // Si la ruta no es válida, usar el home por defecto
    }

    // Establecer el directorio como la raíz del modelo de sistema de archivos
    fileModel->setRootPath(validPath);

    // Crear el QTreeView y asignar el modelo
    treeView = new QTreeView(this);
    treeView->setModel(fileModel);
    treeView->setMouseTracking(true);
    treeView->installEventFilter(this);

    // Establecer el índice raíz en el QTreeView, mostrando el directorio especificado
    QModelIndex rootIndex = fileModel->index(validPath);
    treeView->setRootIndex(rootIndex);

    // Ocultar todas las columnas excepto la de nombre de archivo
    treeView->header()->hide();
    for (int i = 1; i < fileModel->columnCount(); ++i) {
        treeView->hideColumn(i);
    }

    // Configuración de estilo para el QTreeView
    treeView->setStyleSheet(
        "QTreeView { "
        "    background-color: black; "
        "    color: white; "
        "    border: 4px solid red; "
        "    border-radius: 10px; "
        "} "
        "QTreeView::item { "
        "    background-color: black; "
        "    color: white; "
        "} "
        "QTreeView::item:selected { "
        "    background-color: #641414; "
        "    color: white; "
        "} "
        "QTreeView::item:hover { "
        "    background-color: #641414; "
        "    color: white; "
        "} "
    );

    // Crear el label del título
    titleLabel = new QLabel("Explorador de archivos", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "QLabel { "
        "    color: white; "
        "    font-weight: bold; "
        "    background-color: black; "
        "} "
    );
    titleLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    // Crear el contenedor principal
    QWidget *containerWidget = new QWidget(this);
    QVBoxLayout *containerLayout = new QVBoxLayout(containerWidget);
    containerLayout->addWidget(titleLabel);
    containerLayout->addWidget(treeView);

    // Configurar el QHBoxLayout para alinear a la izquierda
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(containerWidget);
    hLayout->setContentsMargins(0, 0, 0, 0);  
    hLayout->setSpacing(0);  
    hLayout->setAlignment(Qt::AlignLeft);  

    setLayout(hLayout);

    // Inicializar el portapapeles
    clipboard = QApplication::clipboard();

    // Configurar el menú contextual y las acciones
    setupActions();
    setupContextMenu();

    // Conectar el menú contextual al QTreeView
    treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(treeView, &QTreeView::customContextMenuRequested, this, [this](const QPoint &pos) {
        contextMenu->exec(treeView->viewport()->mapToGlobal(pos));
    });

    // Conectar el evento de doble clic en un archivo
    connect(treeView, &QTreeView::doubleClicked, this, &FileExplorer::onFileDoubleClicked);
}


bool FileExplorer::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == treeView && event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QPoint cursorPosition = mouseEvent->pos();

        // Obtener el índice del elemento en la posición del cursor
        QModelIndex index = treeView->indexAt(cursorPosition);

        // Obtener el ancho del QTreeView y un margen derecho de 10 píxeles
        int componentWidth = treeView->width();
        int marginRight = 10;

        // Verificar si el cursor está dentro de los últimos 10 píxeles del borde derecho
        bool isNearRightEdge = cursorPosition.x() >= componentWidth - marginRight;

        // Si el cursor está sobre un elemento válido (archivo/carpeta), cambiar a cursor de mano
        if (index.isValid()) {
            treeView->setCursor(Qt::PointingHandCursor);
        }
        // Si el cursor está en el borde derecho, cambiar a cursor de redimensionar
        else if (isNearRightEdge) {
            treeView->setCursor(Qt::SizeHorCursor);

            // Permitir redimensionar si el botón del mouse está presionado
            if (mouseEvent->buttons() & Qt::LeftButton) {
                int newWidth = mapToParent(mouseEvent->pos()).x();
                // Aplicar los límites de tamaño
                if (newWidth >= 220 && newWidth <= 650) {
                    setFixedWidth(newWidth);
                }
            }
        }
        // Si el cursor no está en el borde derecho ni sobre un elemento válido, usar el cursor predeterminado
        else {
            treeView->unsetCursor();  // Quitar el SizeHorCursor y usar el cursor predeterminado
        }
        return true;  // Interceptar el evento
    }
    return QWidget::eventFilter(watched, event);  // Continuar con el procesamiento predeterminado
}



void FileExplorer::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
    setCursor(Qt::ArrowCursor);  // Restablece el cursor cuando se entra al componente
}

void FileExplorer::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    unsetCursor();  // Restablece el cursor cuando se sale del componente
}

void FileExplorer::mouseMoveEvent(QMouseEvent *event)
{
    // Llamar al eventFilter para gestionar los eventos de movimiento de ratón
    eventFilter(treeView, event);
    QWidget::mouseMoveEvent(event);  // Procesar eventos de movimiento adicionales
}

void FileExplorer::onFileDoubleClicked(const QModelIndex &index) {
    QString filePath = fileModel->filePath(index);
    QFileInfo fileInfo(filePath);

    if (fileInfo.isFile()) {
        //addToRecentFiles(filePath);
        emit fileOpened(filePath);
    }
}

void FileExplorer::addToRecentFiles(const QString &filePath) {
    SettingsManager settingsManager("ApkStudio");
    QStringList recentFiles = settingsManager.getValue("recentFiles", QStringList()).toStringList();

    if (!recentFiles.contains(filePath)) {
        recentFiles.append(filePath);
        settingsManager.setValue("recentFiles", recentFiles);
    }
}

void FileExplorer::setRootPath(const QString &newPath) {
    // Verificar si la nueva ruta existe
    if (!QDir(newPath).exists()) {
        qWarning() << "El directorio no existe:" << newPath;
        return;  // Si la ruta no existe, salir del método
    }

    // Establecer el nuevo directorio raíz en el modelo de sistema de archivos
    fileModel->setRootPath(newPath);

    // Obtener el índice del nuevo directorio raíz
    QModelIndex rootIndex = fileModel->index(newPath);

    // Establecer el nuevo índice raíz en el QTreeView para que muestre el nuevo directorio
    treeView->setRootIndex(rootIndex);
}

FileExplorer::~FileExplorer() {}

void FileExplorer::setupActions() {
    // Crear acciones para el menú contextual
    createAction = new QAction("Crear archivo", this);
    renameAction = new QAction("Renombrar", this);
    deleteAction = new QAction("Eliminar", this);
    copyAction = new QAction("Copiar", this);
    pasteAction = new QAction("Pegar", this);

    // Conectar las acciones con los slots correspondientes
    connect(createAction, &QAction::triggered, this, &FileExplorer::createFile);
    connect(renameAction, &QAction::triggered, this, &FileExplorer::renameFile);
    connect(deleteAction, &QAction::triggered, this, &FileExplorer::deleteFile);
    connect(copyAction, &QAction::triggered, this, &FileExplorer::copyFile);
    connect(pasteAction, &QAction::triggered, this, &FileExplorer::pasteFile);
}

void FileExplorer::setupContextMenu() {
    // Crear el menú contextual
    contextMenu = new QMenu(this);

    // Agregar acciones al menú
    contextMenu->addAction(createAction);
    contextMenu->addAction(renameAction);
    contextMenu->addAction(deleteAction);
    contextMenu->addAction(copyAction);
    contextMenu->addAction(pasteAction);
}

void FileExplorer::createFile() {
    QString dirPath = fileModel->filePath(treeView->currentIndex());
    if (!QFileInfo(dirPath).isDir()) {
        dirPath = QFileInfo(dirPath).path();
    }

    QString fileName = QInputDialog::getText(this, "Crear archivo", "Nombre del archivo:");
    if (!fileName.isEmpty()) {
        QFile file(dirPath + "/" + fileName);
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "No se pudo crear el archivo");
        }
    }
}

void FileExplorer::renameFile() {
    QString filePath = fileModel->filePath(treeView->currentIndex());
    QString newFileName = QInputDialog::getText(this, "Renombrar archivo", "Nuevo nombre:");
    if (!newFileName.isEmpty()) {
        QFile file(filePath);
        QString newFilePath = QFileInfo(filePath).absolutePath() + "/" + newFileName;
        if (!file.rename(newFilePath)) {
            QMessageBox::warning(this, "Error", "No se pudo renombrar el archivo");
        }
    }
}

void FileExplorer::deleteFile() {
    QString filePath = fileModel->filePath(treeView->currentIndex());
    if (QMessageBox::question(this, "Eliminar archivo", "¿Estás seguro de que quieres eliminar este archivo?") == QMessageBox::Yes) {
        QFile file(filePath);
        if (!file.remove()) {
            QMessageBox::warning(this, "Error", "No se pudo eliminar el archivo");
        }
    }
}

void FileExplorer::copyFile() {
    copiedFilePath = fileModel->filePath(treeView->currentIndex());
    clipboard->setText(copiedFilePath);
}

void FileExplorer::pasteFile() {
    if (!copiedFilePath.isEmpty()) {
        QString dirPath = fileModel->filePath(treeView->currentIndex());
        if (!QFileInfo(dirPath).isDir()) {
            dirPath = QFileInfo(dirPath).path();
        }

        QString fileName = QFileInfo(copiedFilePath).fileName();
        QString newFilePath = dirPath + "/" + fileName;

        if (QFile::exists(newFilePath)) {
            QMessageBox::warning(this, "Error", "El archivo ya existe en el destino");
            return;
        }

        QFile::copy(copiedFilePath, newFilePath);
    }
}
