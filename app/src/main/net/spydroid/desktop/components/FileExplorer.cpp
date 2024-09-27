#include "FileExplorer.h"
#include <QDir>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QApplication>
#include <QHeaderView>

FileExplorer::FileExplorer(QWidget *parent) : QWidget(parent)
{
    // Crear el modelo de sistema de archivos
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath(QDir::rootPath());

    // Crear el QTreeView y asignar el modelo
    treeView = new QTreeView(this);
    treeView->setModel(fileModel);
    treeView->setRootIndex(fileModel->index(QDir::homePath()));
    treeView->setMaximumWidth(400);
    treeView->header()->hide();

    // Solo mostrar la columna de nombre
    for (int i = 1; i < fileModel->columnCount(); ++i) {
        treeView->hideColumn(i);
    }

    treeView->setStyleSheet(
        "QTreeView { "
        "    background-color: black; "            // Fondo negro
        "    color: white; "                       // Letras blancas
        "    border: 4px solid red; " 
        "    border-radius: 10px; "                // Bordes redondeados de 10px
        "} "
        "QTreeView::item { "
        "    background-color: black; "            // Fondo de elementos
        "    color: white; "                       // Texto de elementos
        "} "
        "QTreeView::item:selected { "
        "    background-color: #641414; "          // Fondo de selección
        "    color: white; "                       // Texto seleccionado
        "} "
        "QTreeView::item:hover { "
        "    background-color: #641414; "          // Fondo al pasar el cursor
        "    color: white; "                       // Texto al pasar el cursor
        "} "
    );


titleLabel = new QLabel("Explorador de archivos", this);
titleLabel->setAlignment(Qt::AlignCenter);

// Aplicar estilo a titleLabel para que sea texto en negrita y con fondo negro
titleLabel->setStyleSheet(
    "QLabel { "
    "    color: white; "                      // Color de texto blanco
    "    font-weight: bold; "                 // Texto en negrita
    "    background-color: black; "           // Fondo negro
    "} "
);

// Establecer ancho máximo del título para evitar que ocupe todo el ancho
titleLabel->setMaximumWidth(215);  // Ajustar según tus necesidades
titleLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);  // Evitar expansión

// Crear un contenedor para el QLabel (titleLabel) y el QTreeView
QWidget *containerWidget = new QWidget(this);
QVBoxLayout *containerLayout = new QVBoxLayout(containerWidget);

// Agregar titleLabel y treeView al layout vertical dentro del contenedor
containerLayout->addWidget(titleLabel);
containerLayout->addWidget(treeView);

// Crear el layout horizontal para alinear a la izquierda
QHBoxLayout *hLayout = new QHBoxLayout();
hLayout->addWidget(containerWidget);  // Sin expansores

// Configurar el layout principal de FileExplorer
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
