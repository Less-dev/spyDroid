#include "BrowserSetup.h"
#include <QFileDialog>
#include <QDir>

BrowserSetup::BrowserSetup(QWidget *parent)
    : QWidget(parent), settingsManager(new SettingsManager("init", this)) {
    // Crear layout horizontal
    QHBoxLayout *layout = new QHBoxLayout(this);

    // Obtener el directorio del usuario actual
    QString homeDir = QDir::homePath();
    QString initialPath = homeDir + "/SPYDROID";

    // Crear un QLineEdit con la ruta inicial
    pathLineEdit = new QLineEdit(initialPath, this);

    // Configurar QLineEdit para que ocupe todo el espacio disponible
    layout->addWidget(pathLineEdit, /* stretch */ 1);

    // Crear el botón para abrir el explorador
    QPushButton *browseButton = new QPushButton("Explorador", this);

    // Añadir el botón al layout sin stretch para que ocupe su tamaño mínimo
    layout->addWidget(browseButton);

    // Conectar la señal del botón a la función openFileDialog()
    connect(browseButton, &QPushButton::clicked, this, &BrowserSetup::openFileDialog);

    // Conectar la señal editingFinished() para detectar cuando el usuario termina de escribir
    connect(pathLineEdit, &QLineEdit::editingFinished, this, &BrowserSetup::onPathEditingFinished);
}

void BrowserSetup::onPathEditingFinished() {
    // Guardar el valor del QLineEdit en path_resources cuando el usuario deja de escribir
    QString currentPath = pathLineEdit->text();
    settingsManager->setValue("path_resources", currentPath);
}

void BrowserSetup::openFileDialog() {
    // Abrir un diálogo de selección de directorio
    QString selectedDirectory = QFileDialog::getExistingDirectory(this, "Selecciona un directorio", pathLineEdit->text());

    // Si el usuario selecciona un directorio, actualizar el QLineEdit con la nueva ruta
    if (!selectedDirectory.isEmpty()) {
        pathLineEdit->setText(selectedDirectory);

        // Guardar el valor en path_resources
        settingsManager->setValue("path_resources", selectedDirectory);
    }
}

void BrowserSetup::hideEvent(QHideEvent *event) {
    // Guardar el valor actual de pathLineEdit en path_resources
    settingsManager->setValue("path_resources", pathLineEdit->text());

    // Llamar al evento base para que continúe el procesamiento normal
    QWidget::hideEvent(event);
}
