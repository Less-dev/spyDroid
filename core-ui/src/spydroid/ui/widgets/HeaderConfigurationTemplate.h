#ifndef HEADERCONFIGURATIONTEMPLATE_H
#define HEADERCONFIGURATIONTEMPLATE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QHBoxLayout>

class HeaderConfigurationTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderConfigurationTemplate(QWidget *parent = nullptr);

    // Método para cambiar la imagen en tiempo de ejecución
    void setImage(const QString &imagePath);

signals:
    // Señal que se emitirá cuando se haga clic en el ícono de editar imagen
    void editImageRequested();

private:
    QLabel *titleLabel;        // Texto centrado: "CONFIGURACIÓN"
    QLabel *imageLabel;        // Imagen con borde rojo
    QPushButton *editButton;   // Botón para editar la imagen
    QPixmap currentImage;      // Imagen actual

    // Método para ajustar el tamaño de la imagen basado en el tamaño de la ventana
    void resizeEvent(QResizeEvent *event) override;
};

#endif // HEADERCONFIGURATIONTEMPLATE_H
