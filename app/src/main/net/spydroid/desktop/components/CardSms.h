#ifndef CARD_SMS_H
#define CARD_SMS_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "../remote/models/SmsHandler.h"  // Incluimos la definición de SmsHandler

class CardSms : public QWidget
{
    Q_OBJECT

public:
    explicit CardSms(const SmsHandler& smsHandler, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel* date;
    QLabel* sms;
    QVBoxLayout* layout;
};

#endif // CARD_SMS_H
