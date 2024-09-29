#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileInfo>
#include <QTimer>

class FileWidget : public QWidget
{
    Q_OBJECT

public:
    // Constructor que recibe la ruta del archivo
    explicit FileWidget(const QString& filePath, QWidget* parent = nullptr);

signals:
    // Señal que se emite cuando el widget se cierra
    void closed();

private slots:
    // Maneja el clic del botón de cerrar
    void onCloseClicked();

    // Se restaura la opacidad después de un tiempo
    void restoreIconOpacity();

protected:
    // Función virtual que puede ser sobrescrita
    virtual void onClick();

private:
    QPushButton* closeButton;  // Botón de cerrar
    QTimer* timer;             // Temporizador para restaurar la opacidad
    void paintEvent(QPaintEvent *event);
};

#endif // FILEWIDGET_H
