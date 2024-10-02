#ifndef BROWSERSETUP_H
#define BROWSERSETUP_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>

class BrowserSetup : public QWidget {
    Q_OBJECT  // Asegúrate de que esta macro esté aquí

public:
    BrowserSetup(QWidget *parent = nullptr);

private slots:
    void openFileDialog();

private:
    QLineEdit *pathLineEdit;
};

#endif // BROWSERSETUP_H
