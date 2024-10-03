#include "CardWidgetInstaller.h"

CardWidgetInstaller::CardWidgetInstaller(QWidget *parent) : QWidget(parent)  {
    card = new QFrame(this);
    layout = new QVBoxLayout(card);
    layout->setContentsMargins(20, 70, 20, 20);
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
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