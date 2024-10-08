#include "BottomBarInstaller.h"

BottomBarInstaller::BottomBarInstaller(QWidget *parent) :
    QWidget(parent)
{
    // Crear y configurar el separador superior
    m_separator = new QFrame(this);
    m_separator->setFrameShape(QFrame::HLine);
    m_separator->setFrameShadow(QFrame::Sunken);
    m_separator->setStyleSheet("color: white;");  // Estilo de línea blanca

    // Crear los botones y configurar sus textos
    m_backButton = new QPushButton("Volver", this);
    m_customButton = new QPushButton(this); // Se configura con texto externo
    m_cancelButton = new QPushButton("Cancelar", this);

    // Conectar las señales de clic a las señales propias del widget
    connect(m_backButton, &QPushButton::clicked, this, &BottomBarInstaller::backButtonClicked);
    connect(m_customButton, &QPushButton::clicked, this, &BottomBarInstaller::customButtonClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &BottomBarInstaller::cancelButtonClicked);

    // Crear el layout horizontal para los botones
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();  // Añadir un espacio flexible antes de los botones
    buttonLayout->addWidget(m_backButton);
    buttonLayout->addWidget(m_customButton);
    buttonLayout->addWidget(m_cancelButton);

    // Crear el layout principal y añadir el separador y el layout de botones
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_separator);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    // Configurar las propiedades del componente
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void BottomBarInstaller::setBackButtonEnabled(bool enabled)
{
    m_backButton->setEnabled(enabled);
}

void BottomBarInstaller::setCustomButtonEnabled(bool enabled)
{
    m_customButton->setEnabled(enabled);
}

void BottomBarInstaller::setCancelButtonEnabled(bool enabled)
{
    m_cancelButton->setEnabled(enabled);
}

void BottomBarInstaller::setCustomButtonText(const QString &text)
{
    m_customButton->setText(text);
}
