#ifndef CARDTEMPLATE_H
#define CARDTEMPLATE_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QLabel>
#include <QGridLayout>
#include <QMouseEvent>
#include <functional>

class CardTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit CardTemplate(QWidget *parent = nullptr);
    void setTemplates(const QMap<QString, QString> &templates);  // Diccionario imagen:descripción
    std::function<void(QString)> onTemplateSelected;  // Lambda para devolver la plantilla seleccionada

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;  // Manejar eventos de teclado

private:
    QGridLayout *gridLayout;
    QMap<QLabel*, QString> templateMap;  // Mapear QLabel a descripciones
    QLabel *selectedCard;  // La tarjeta seleccionada

    void selectCard(QLabel *card);  // Seleccionar tarjeta
    void updateBorders(QLabel *card, bool selected);  // Actualizar bordes al seleccionar/deseleccionar
    void navigateTo(int row, int col);  // Navegar a una tarjeta específica
};

#endif // CARDTEMPLATE_H
