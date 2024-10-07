#include "CardOptions.h"
#include <QPainter>
#include <QVBoxLayout>
#include <cmath>


CardOptions::CardOptions(QWidget *parent)
    : QWidget(parent), isHovered(false)
{
    // Inicializamos los labels
    imageLabel = new QLabel(this);
    descriptionLabel = new QLabel(this);

    // Configuramos el QLabel de la imagen para que mantenga el tamaño adecuado
    imageLabel->setScaledContents(true);  // La imagen se escalará dentro del label
    imageLabel->setContentsMargins(2, 2, 2, 2);  // Margen opcional alrededor de la imagen

    // Configuramos el QLabel de la descripción
    descriptionLabel->setWordWrap(true);  // Permitir que el texto se envuelva
    descriptionLabel->setAlignment(Qt::AlignHCenter);  // Centramos el texto horizontalmente
    descriptionLabel->setStyleSheet("font-weight: bold; color: white;");
    
    // Establecemos márgenes para la descripción (5px de cada lado)
    descriptionLabel->setContentsMargins(5, 0, 5, 0);  // Márgenes izquierdo, superior, derecho, inferior

    // Layout para colocar la imagen arriba y el texto debajo
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    layout->addSpacing(10);  // Espacio de 10px entre la imagen y la descripción
    layout->addWidget(descriptionLabel);

    // Establecer márgenes para el layout principal (sin padding a los lados, solo superior e inferior)
    layout->setContentsMargins(0, 0, 0, 10);
    setLayout(layout);

    // Permitir redimensionamiento
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}


void CardOptions::setImage(const QPixmap &pixmap)
{
    imageLabel->setPixmap(pixmap);
}

void CardOptions::setDescription(const QString &description)
{
    descriptionLabel->setText(description);
}

void CardOptions::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Color de relleno semitransparente (negro con alfa 115)
    QColor backgroundColor = isHovered ? QColor(0, 0, 0, 150) : QColor(0, 0, 0, 115);
    QBrush brush(backgroundColor);
    painter.setBrush(brush);

    // Bordes y grosor
    QPen pen(QColor("#800000"));  // Color del borde
    pen.setWidth(4);  // Grosor del borde
    painter.setPen(pen);

    // Dibujar rectángulo redondeado con bordes
    painter.drawRoundedRect(0, 0, width(), height(), 15, 15);
}

void CardOptions::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Obtener las dimensiones del widget
    int widgetHeight = height();
    int widgetWidth = width();

    // Ajustar la altura de la imagen proporcionalmente al tamaño del widget
    int maxImageHeight = qMin(static_cast<double>(widgetHeight) * 0.3, 150.0);  // Ajustar la altura de la imagen
    imageLabel->setFixedHeight(maxImageHeight);  // Establecer nueva altura de la imagen
    imageLabel->setFixedWidth(widgetWidth);  // La imagen siempre ocupará todo el ancho

    // Ajustar el tamaño de la fuente proporcionalmente al tamaño del widget (ancho y altura)
    QFont font = descriptionLabel->font();
    int area = widgetHeight * widgetWidth;  // Área total del widget
    int newFontSize = qMax(8, static_cast<int>(sqrt(area) / 20));  // Ajustar el tamaño del texto según el área del widget
    font.setPointSize(newFontSize);
    descriptionLabel->setFont(font);

    // Alinear el texto horizontalmente
    descriptionLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}



void CardOptions::enterEvent(QEvent *event)
{
    isHovered = true;
    update();  // Actualizar el componente para reflejar los cambios visuales
    QWidget::enterEvent(event);
}

void CardOptions::leaveEvent(QEvent *event)
{
    isHovered = false;
    update();
    QWidget::leaveEvent(event);
}

void CardOptions::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clicked();  // Emitimos la señal clicked
    }
    QWidget::mousePressEvent(event);
}
