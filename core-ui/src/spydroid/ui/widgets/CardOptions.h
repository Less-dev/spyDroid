#ifndef CARDOPTIONS_H
#define CARDOPTIONS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>

class CardOptions : public QWidget
{
    Q_OBJECT

public:
    explicit CardOptions(QWidget *parent = nullptr);

    void setImage(const QPixmap &pixmap);  // Función para establecer la imagen
    void setDescription(const QString &description);  // Función para establecer la descripción

protected:
    void paintEvent(QPaintEvent *event) override;  // Para dibujar el fondo
    void resizeEvent(QResizeEvent *event) override;  // Para ajustar los tamaños internos
    void enterEvent(QEvent *event) override;  // Evento al pasar el mouse
    void leaveEvent(QEvent *event) override;  // Evento al salir del mouse
    void mousePressEvent(QMouseEvent *event) override;  // Evento al hacer click

private:
    QLabel *imageLabel;
    QLabel *descriptionLabel;
    bool isHovered;

signals:
    void clicked();  // Señal que se emitirá cuando el componente sea clickeado
};

#endif // CARDOPTIONS_H
