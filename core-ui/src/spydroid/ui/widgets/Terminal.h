#ifndef TERMINAL_H
#define TERMINAL_H

#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <qtermwidget.h>
#include <QFontDatabase>  // Asegurarse de incluir el encabezado correcto

class Terminal : public QWidget {
    Q_OBJECT

public:
    Terminal(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QTermWidget* terminal;
};

#endif // TERMINAL_H
