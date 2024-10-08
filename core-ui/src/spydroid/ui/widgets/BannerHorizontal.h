#ifndef BANNERHORIZONTAL_H
#define BANNERHORIZONTAL_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QFrame>
#include <QPaintEvent>

class BannerHorizontal : public QWidget
{
    Q_OBJECT

public:
    explicit BannerHorizontal(QWidget *parent = nullptr);

    // Setters para el título y la descripción
    void setTitle(const QString &title);
    void setDescription(const QString &description);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QLabel *imageLabel;
    QLabel *titleLabel;
    QLabel *descriptionLabel;
    QFrame *divider;

    void setupUI();
};

#endif // BANNERHORIZONTAL_H
