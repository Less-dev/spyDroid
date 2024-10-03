#include "CardWidgetInstaller.h"

CardWidgetInstaller::CardWidgetInstaller(QWidget *parent) : QWidget(parent)  {
    card = new QFrame(this);
    title = new QLabel("Detalles de descarga", this);
    title->setStyleSheet(
        "QLabel { color: white; background-color: black; font-size: 16px; padding: 0 10px; }"
    );
    title->move(25, -2);  // Posicionarlo fuera del borde superior y a la izquierda
    title->raise();  // Asegurar que el título esté por encima de otros widgets

        // Layout para el contenido dentro de la tarjeta
    layout = new QVBoxLayout(card);
    layout->setContentsMargins(20, 70, 20, 20);  // Padding de 20px en todos los lados
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);  // Alinear los textos en la parte superior izquierda

    card->setLayout(layout);
}

void CardWidgetInstaller::paintEvent(QPaintEvent *event) {
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