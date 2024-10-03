#include "CardWidgetSettings.h"

CardWidgetSettings::CardWidgetSettings(QWidget *parent) 
 : QWidget(parent)  {
        // Configurar el marco (la tarjeta) sin aplicar tamaños fijos, ajustándose al contenido
        QFrame *card = new QFrame(this);

        // Título que sobresale de la parte superior y está alineado a la izquierda
        title = new QLabel("Ubicación de instalación de spydroid", this);
        title->setStyleSheet(
            "QLabel { color: white; background-color: black; font-size: 16px; padding: 0 10px; }"
        );
        title->move(25, -2);  // Posicionarlo fuera del borde superior y a la izquierda
        title->raise();  // Asegurar que el título esté por encima de otros widgets

        // Layout para el contenido dentro de la tarjeta
        layout = new QVBoxLayout(card);
        layout->setContentsMargins(20, 70, 20, 20);  // Padding de 20px en todos los lados
        layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);  // Alinear los textos en la parte superior izquierda

        // Crear un QLabel para el texto principal (renombrado a textDescription)
        textDescription = new QLabel("La ubicación especificada debe tener al menos 500 MB de espacio libre", card);
        textDescription->setStyleSheet("QLabel { color: white; font-size: 20px; }");

        secondaryText = new QLabel("Haga click en Explorador para personalizar", card);
        secondaryText->setStyleSheet("QLabel { color: white; font-size: 13.5px; }");  // Tamaño de fuente más pequeño

        layout->addWidget(textDescription);
        layout->addWidget(secondaryText);

        layout->addSpacing(20);

        browserSetup = new BrowserSetup(card);
        layout->addWidget(browserSetup);

        card->setLayout(layout);  // Aplicar el layout a la tarjeta
    }


void CardWidgetSettings::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::red, 2);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::black));
    QRect rect = this->rect();
    rect.adjust(1, 1, -1, -1);  // Ajustar para evitar que el borde sobresalga del widget
    painter.drawRoundedRect(rect, 15, 15);  // Esquinas redondeadas de 15px de radio

    QWidget::paintEvent(event);
}