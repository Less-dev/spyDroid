#include "CardSms.h"
#include <QPainter>
#include <QBrush>
#include <QString>

CardSms::CardSms(const SmsHandler& smsHandler, QWidget *parent)
    : QWidget(parent)
{
    // Configuración del tamaño del widget
    this->setFixedSize(400, 200);

    // Layout para organizar las etiquetas
    layout = new QVBoxLayout(this);

    // Creamos y configuramos las etiquetas
    idLabel = new QLabel(QString("ID: %1").arg(smsHandler.id), this);
    aliasLabel = new QLabel(QString("Alias: %1").arg(QString::fromStdString(smsHandler.alias)), this);
    smsLabel = new QLabel(QString("Sms: %1").arg(QString::fromStdString(smsHandler.sms)), this);

    // Añadimos las etiquetas al layout
    layout->addWidget(idLabel);
    layout->addWidget(aliasLabel);
    layout->addWidget(smsLabel);

    // Establecemos el layout al widget
    this->setLayout(layout);
}

void CardSms::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Color de relleno y borde
    QBrush brush(QColor("#FFFFFF"));  // Color de fondo blanco
    painter.setBrush(brush);
    
    QPen pen(QColor("#000000"));  // Color del borde negro
    pen.setWidth(2);  // Grosor del borde
    painter.setPen(pen);
    
    // Dibujamos el rectángulo redondeado
    painter.drawRoundedRect(0, 0, width(), height(), 15, 15);
}
