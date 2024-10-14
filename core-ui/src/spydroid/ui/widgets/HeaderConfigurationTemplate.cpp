#include "HeaderConfigurationTemplate.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QString>

HeaderConfigurationTemplate::HeaderConfigurationTemplate(QWidget *parent)
    : QWidget(parent),
      titleLabel(new QLabel("CONFIGURACIÓN", this)),
      imageLabel(new QLabel(this)),
      editButton(new QPushButton(this))
{
    // Configurar el texto "CONFIGURACIÓN"
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont boldFont = titleLabel->font();
    boldFont.setBold(true);
    boldFont.setPixelSize(19); // Tamaño del texto
    titleLabel->setFont(boldFont);
    titleLabel->setStyleSheet("color: white;");


    // Configurar la imagen
    imageLabel->setFixedSize(100, 100);  // Tamaño máximo inicial
    imageLabel->setStyleSheet("border: 2.5px solid red;");

    // Configurar el botón de editar
    editButton->setIcon(QIcon(":/icons/edit_image"));
    editButton->setFixedSize(25, 25);
    editButton->setStyleSheet("border: none;");
    
    // Conectar el clic del botón con la señal
    connect(editButton, &QPushButton::clicked, this, &HeaderConfigurationTemplate::editImageRequested);

    // Crear el layout principal
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch();
    mainLayout->addWidget(imageLabel);

    // Posicionar el botón de editar dentro de la imagen
    QVBoxLayout *imageLayout = new QVBoxLayout(imageLabel);
    imageLayout->addStretch();
    imageLayout->addWidget(editButton, 0, Qt::AlignBottom | Qt::AlignRight);

    setLayout(mainLayout);
}

void HeaderConfigurationTemplate::setImage(const QString &imagePath)
{
    QPixmap pixmap;
    if (pixmap.load(imagePath)) {
        currentImage = pixmap;
        imageLabel->setPixmap(currentImage.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        // no se pudo cargar
        imageLabel->clear();
    }
}


void HeaderConfigurationTemplate::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Ajustar dinámicamente el tamaño de la imagen en función del ancho disponible
    int newSize = std::max(50, std::min(width() / 6, 100));
    imageLabel->setFixedSize(newSize, newSize);
    imageLabel->setPixmap(currentImage.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
