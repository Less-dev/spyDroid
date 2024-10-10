#include "CardTemplate.h"
#include <QPixmap>
#include <QVBoxLayout>
#include <QFrame>
#include <QMouseEvent>
#include <QPainter>

CardTemplate::CardTemplate(QWidget *parent) : QWidget(parent), selectedCard(nullptr)
{
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(5);  // Espaciado entre tarjetas
    gridLayout->setContentsMargins(10, 10, 10, 10);  // Márgenes externos de la cuadrícula

    this->setLayout(gridLayout);
    setFocusPolicy(Qt::StrongFocus);  // Permitir recibir eventos de teclado
}

void CardTemplate::setTemplates(const QMap<QString, QString> &templates)
{
    int row = 0, col = 0;

    for (auto it = templates.begin(); it != templates.end(); ++it) {

        QString imagePath = it.key();
        QString description = it.value();

        // Crear contenedor para imagen y descripción
        QWidget *cardWidget = new QWidget();
        QVBoxLayout *cardLayout = new QVBoxLayout(cardWidget);

        // Ajustar el tamaño del layout al contenido
        cardLayout->setSizeConstraint(QLayout::SetMinimumSize);

        // Imagen
        QLabel *imageLabel = new QLabel();
        QPixmap pixmap(imagePath);

        // La imagen se ajustará a 200px de ancho y el alto se ajustará proporcionalmente
        imageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
        imageLabel->setAlignment(Qt::AlignCenter);

        // Descripción
        QLabel *descLabel = new QLabel(description);
        descLabel->setStyleSheet("color: white;");
        descLabel->setAlignment(Qt::AlignCenter);
        descLabel->setWordWrap(true);  // Permitir que el texto sea de varias líneas

        // Añadir los widgets al layout de la tarjeta
        cardLayout->addWidget(imageLabel);
        cardLayout->addWidget(descLabel);

        // Aplicar padding de 20px en los lados de la tarjeta
        cardWidget->setFixedWidth(220);  // 200px (ancho imagen) + 2x20px (margen)
        cardLayout->setContentsMargins(10, 10, 10, 10);  // Márgenes internos de la tarjeta

        // Colocar la tarjeta en la cuadrícula
        gridLayout->addWidget(cardWidget, row, col);
        templateMap[imageLabel] = description;

        // Avanzar en la cuadrícula
        col++;
        if (col >= 3) {  // 3 columnas por fila
            col = 0;
            row++;
        }

        // Instalar el filtro de eventos para detectar los clics
        imageLabel->installEventFilter(this);
    }
}

void CardTemplate::mousePressEvent(QMouseEvent *event)
{
    QLabel *clickedLabel = qobject_cast<QLabel*>(childAt(event->pos()));
    if (clickedLabel && templateMap.contains(clickedLabel))
    {
        selectCard(clickedLabel);
    }
}

void CardTemplate::selectCard(QLabel *card)
{
    if (selectedCard)
    {
        // Des-seleccionar tarjeta previamente seleccionada
        updateBorders(selectedCard, false);
    }

    // Seleccionar nueva tarjeta
    updateBorders(card, true);
    selectedCard = card;

    // Ejecutar la lambda si está configurada
    if (onTemplateSelected)
    {
        onTemplateSelected(templateMap[card]);
    }

    // Redibujar el widget para reflejar el cambio
    update();
}

void CardTemplate::updateBorders(QLabel *card, bool selected)
{
    if (card)
    {
        card->update();
    }
}

void CardTemplate::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);  // Llamamos al paintEvent por defecto

    if (selectedCard)
    {
        QPainter painter(this);

        // Fondo negro con transparencia
        QBrush brush(QColor(0, 0, 0, 115));  // Negro con 45% de opacidad
        painter.setBrush(brush);

        // Borde blanco con grosor de 2px y esquinas redondeadas
        QPen pen(Qt::white, 2);
        painter.setPen(pen);

        // Dibujamos el borde alrededor de la tarjeta seleccionada con esquinas redondeadas
        QWidget *parentWidget = selectedCard->parentWidget();
        if (parentWidget)
        {
            QRect rect = parentWidget->geometry();
            painter.drawRoundedRect(rect.adjusted(1, 1, -1, -1), 10, 10);  // Esquinas redondeadas con radio de 10px
        }
    }
}

// Manejar eventos de teclado para la navegación
void CardTemplate::keyPressEvent(QKeyEvent *event)
{
    if (!selectedCard)
    {
        QWidget::keyPressEvent(event);  // No hacemos nada si no hay tarjeta seleccionada
        return;
    }

    int row = -1, col = -1;

    // Encontrar la posición actual de la tarjeta seleccionada en el grid
    for (int r = 0; r < gridLayout->rowCount(); ++r)
    {
        for (int c = 0; c < gridLayout->columnCount(); ++c)
        {
            if (gridLayout->itemAtPosition(r, c) && gridLayout->itemAtPosition(r, c)->widget() == selectedCard->parentWidget())
            {
                row = r;
                col = c;
                break;
            }
        }
        if (row != -1)
            break;
    }

    // Navegar en función de la tecla presionada
    switch (event->key())
    {
    case Qt::Key_Up:
        if (row > 0)
            navigateTo(row - 1, col);
        break;
    case Qt::Key_Down:
        if (row < gridLayout->rowCount() - 1)
            navigateTo(row + 1, col);
        break;
    case Qt::Key_Left:
        if (col > 0)
            navigateTo(row, col - 1);
        break;
    case Qt::Key_Right:
        if (col < gridLayout->columnCount() - 1)
            navigateTo(row, col + 1);
        break;
    default:
        QWidget::keyPressEvent(event);  // Llamamos a la implementación por defecto para otras teclas
    }
}

// Navegar a una tarjeta específica por posición en la cuadrícula
void CardTemplate::navigateTo(int row, int col)
{
    QLayoutItem *item = gridLayout->itemAtPosition(row, col);
    if (item && item->widget())
    {
        QLabel *newCard = item->widget()->findChild<QLabel*>();
        if (newCard)
        {
            selectCard(newCard);  // Seleccionar la nueva tarjeta
        }
    }
}
