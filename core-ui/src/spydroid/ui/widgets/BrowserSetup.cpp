#include "BrowserSetup.h"
#include <QFileDialog>
#include <QDir>

BrowserSetup::BrowserSetup(QWidget *parent) : QWidget(parent) {
    // Crear layout horizontal
    QHBoxLayout *layout = new QHBoxLayout(this);

    // Obtener el directorio del usuario actual
    QString homeDir = QDir::homePath();
    QString initialPath = homeDir + "/SPYDROID";

    // Crear un QLineEdit con la ruta inicial
    pathLineEdit = new QLineEdit(initialPath, this);
    layout->addWidget(pathLineEdit);

    // Crear el botón para abrir el explorador
    QPushButton *browseButton = new QPushButton("Explorador", this);
    layout->addWidget(browseButton);

    // Conectar la señal del botón a la función openFileDialog()
    connect(browseButton, &QPushButton::clicked, this, &BrowserSetup::openFileDialog);
}

void BrowserSetup::openFileDialog() {
    // Abrir un diálogo de selección de directorio
    QString selectedDirectory = QFileDialog::getExistingDirectory(this, "Selecciona un directorio", pathLineEdit->text());

    // Si el usuario selecciona un directorio, actualizar el QLineEdit con la nueva ruta
    if (!selectedDirectory.isEmpty()) {
        pathLineEdit->setText(selectedDirectory);
    }
}
