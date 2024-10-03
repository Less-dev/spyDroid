#ifndef CARD_WIDGET_INSTALLER_H
#define CARD_WIDGET_INSTALLER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>
#include <QFrame>
#include <QVBoxLayout>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QRect>

class CardWidgetInstaller : public QWidget {
    Q_OBJECT

public:
    explicit CardWidgetInstaller(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QFrame* card;
    QLabel* title;
    QVBoxLayout* layout;
};

#endif // CARD_WIGET_INSTALLER_H