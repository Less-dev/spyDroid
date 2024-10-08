#include "BannerHorizontal.h"
#include <QHBoxLayout>
#include <QFont>
#include <QPalette>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QRectF>
#include <QPainterPath>

BannerHorizontal::BannerHorizontal(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void BannerHorizontal::setupUI()
{
    int heightSize = 100;
    setMaximumHeight(heightSize);

    // Establecer fondo blanco pastel para el componente
    // setStyleSheet("background-color: #FDF5E6;"); // Blanco pastel

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(5.5, 5.2, 5.5, 0);  // Márgenes: izquierda, arriba, derecha, abajo
    mainLayout->setSpacing(0);

    // 1. Layout horizontal para la imagen y el texto
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    // 2. Imagen a la izquierda
    imageLabel = new QLabel(this);
    QPixmap pixmap(":installer");
    imageLabel->setPixmap(pixmap.scaled(300, heightSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    imageLabel->setFixedSize(300, heightSize);

    horizontalLayout->addWidget(imageLabel);

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
    descriptionLabel->setWordWrap(true);

    // Cambiar el color del texto de la descripción a negro
    descriptionLabel->setStyleSheet("color: black;");
    textLayout->addWidget(descriptionLabel);

    horizontalLayout->addLayout(textLayout);
    mainLayout->addLayout(horizontalLayout);

    // 3. Agregar un divisor horizontal (QFrame)
    QFrame *divider = new QFrame(this);
    divider->setFrameShape(QFrame::HLine);
    divider->setFrameShadow(QFrame::Sunken);
    divider->setStyleSheet("color: red; background-color: red;");
    divider->setFixedHeight(2);  // Definir la altura del divisor

    mainLayout->addWidget(divider);  // Agregar el divisor al layout principal

    setLayout(mainLayout);
}

void BannerHorizontal::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Configurar un pincel para el fondo (blanco pastel)
    QBrush brush(QColor(253, 245, 230));  // Color blanco pastel (equivalente a #FDF5E6)
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing);

    // Configurar un borde transparente con grosor
    QPen pen;
    pen.setWidth(2);  // Grosor del borde (ajusta según tus necesidades)
    pen.setColor(QColor(0, 0, 0, 128));  // Color negro con transparencia (alpha = 128)
    painter.setPen(pen);

    // Definir las dimensiones del componente, excluyendo los márgenes
    QRectF rect = this->rect().adjusted(5.5, 5.2, -5.5, 0);  // Excluir los márgenes de 5px de izquierda, derecha y arriba

    // Definir el radio para las esquinas superiores redondeadas
    int radius = 12;

    // Dibujar un rectángulo con esquinas superiores redondeadas y esquinas inferiores rectas
    QPainterPath path;
    path.moveTo(rect.topRight());  // Moverse al borde superior derecho
    path.arcTo(QRectF(rect.right() - 2 * radius, rect.top(), 2 * radius, 2 * radius), 0, 90);  // Esquina superior derecha
    path.arcTo(QRectF(rect.left(), rect.top(), 2 * radius, 2 * radius), 90, 90);  // Esquina superior izquierda
    path.lineTo(rect.bottomLeft());  // Línea hasta la esquina inferior izquierda
    path.lineTo(rect.bottomRight());  // Línea hasta la esquina inferior derecha
    path.closeSubpath();  // Cerrar el camino

    // Dibujar el camino con el borde y fondo
    painter.drawPath(path);

    // Llamar al método base para asegurarse de que se manejen otros eventos de pintura
    QWidget::paintEvent(event);
}


void BannerHorizontal::setTitle(const QString &title)
{
    titleLabel->setText(title);
}

void BannerHorizontal::setDescription(const QString &description)
{
    descriptionLabel->setText(description);
}