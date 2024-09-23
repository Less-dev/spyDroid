#ifndef ITEMBOARD_H
#define ITEMBOARD_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QMouseEvent>

class ItemBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ItemBoard(QWidget *parent = nullptr);

    // Setters for image and text
    void setImage(const QPixmap &image);
    void setText(const QString &text);

signals:
    // Signal for when the widget is clicked
    void clicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *imageLabel;
    QLabel *textLabel;
    QVBoxLayout *layout;
    QTimer *clickTimer;  // Timer to revert the color after click

    // Color constants
    const QColor redColor = QColor(255, 0, 0);
    const QColor darkRedColor = QColor(139, 0, 0);
    const QSize imageSize = QSize(35, 35);  // Size for the image

    void changeColor(const QColor &color);
};

#endif // ITEMBOARD_H
