#include "FileExplorer.h"
#include <QDir>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QApplication>
#include <QHeaderView>

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

        // Establecer el índice raíz en el QTreeView, mostrando el directorio especificado
    // Establecer el índice raíz en el QTreeView, mostrando el directorio especificado
    QModelIndex rootIndex = fileModel->index(validPath);
    treeView->setRootIndex(rootIndex);
    
    // Ocultar todas las columnas excepto la de nombre de archivo
    treeView->header()->hide();  // Ocultar el encabezado de la tabla
    
    for (int i = 1; i < fileModel->columnCount(); ++i) {
        treeView->hideColumn(i);  // Ocultar todas las columnas excepto la de nombre
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
    titleLabel->setMaximumWidth(215);
    titleLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    // Crear el contenedor principal
    QWidget *containerWidget = new QWidget(this);
    QVBoxLayout *containerLayout = new QVBoxLayout(containerWidget);
    containerLayout->addWidget(titleLabel);
    containerLayout->addWidget(treeView);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(containerWidget);

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
