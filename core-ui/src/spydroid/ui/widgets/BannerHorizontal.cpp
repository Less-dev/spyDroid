#include "BannerHorizontal.h"
#include <QHBoxLayout>
#include <QFont>
#include <QPalette>

BannerHorizontal::BannerHorizontal(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void BannerHorizontal::setupUI()
{
    int heightSize = 100;
    setMaximumHeight(heightSize);

    // Establecer fondo blanco pastel para el componente
    setStyleSheet("background-color: #FDF5E6;"); // Blanco pastel

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(5, 10, 5, 0);
    mainLayout->setSpacing(0);

    // 1. Imagen a la izquierda
    imageLabel = new QLabel(this);
    QPixmap pixmap(":installer");
    imageLabel->setPixmap(pixmap.scaled(300, heightSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    imageLabel->setFixedSize(300, heightSize);

    // Aplicar estilo para el borde redondeado en la esquina superior izquierda
    imageLabel->setStyleSheet("border-top-left-radius: 15px;"); // Ajusta el radio como desees

    mainLayout->addWidget(imageLabel);

    // Layout para el texto
    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(0);

    // Título
    titleLabel = new QLabel(this);
    QFont titleFont = titleLabel->font();
    titleFont.setBold(true);
    titleFont.setPointSize(20);
    titleLabel->setFont(titleFont);

    // Cambiar el color del texto del título a negro
    titleLabel->setStyleSheet("color: black;");
    textLayout->addWidget(titleLabel);

    // Descripción
    descriptionLabel = new QLabel(this);
    QFont descFont = descriptionLabel->font();
    descFont.setPointSize(12);
    descriptionLabel->setFont(descFont);

    // Cambiar el color del texto de la descripción a negro
    descriptionLabel->setStyleSheet("color: black;");
    textLayout->addWidget(descriptionLabel);

    mainLayout->addLayout(textLayout);

    setLayout(mainLayout);
}


void BannerHorizontal::setTitle(const QString &title)
{
    titleLabel->setText(title);
}

void BannerHorizontal::setDescription(const QString &description)
{
    descriptionLabel->setText(description);
}