#ifndef CARD_WIDGET_SETTINGS
#define CARD_WIDGET_SETTINGS

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>
#include "BrowserSetup.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QRect>


class CardWidgetSettings : public QWidget {
    Q_OBJECT

public:
    explicit CardWidgetSettings(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    BrowserSetup* browserSetup;
    QVBoxLayout* layout;
    QLabel* title;
    QLabel* textDescription;
    QLabel* secondaryText;
};

#endif