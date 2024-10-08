#ifndef CARDWIDGETVERIFY_H
#define CARDWIDGETVERIFY_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QRect>

class CardWidgetVerify : public QWidget {
    Q_OBJECT

public:
    explicit CardWidgetVerify(const QString& path = "", QWidget *parent = nullptr);
    void setPath(const QString& path);
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event);

private:
    class TitleLabel : public QLabel {
    public:
        explicit TitleLabel(const QString &text, QWidget *parent = nullptr);
    };

    class DescriptionLabel : public QLabel {
    public:
        explicit DescriptionLabel(const QString &text, QWidget *parent = nullptr);
    };
    QScrollArea* scrollArea;
    QString installationPath;  // Variable para almacenar la ruta de instalación
    DescriptionLabel* folder_ssdk;
    DescriptionLabel*folder_sdk;
};

#endif // CARDWIDGETVERIFY_H
