#ifndef BROWSERSETUP_H
#define BROWSERSETUP_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QHideEvent>
#include "../../../../../core-data/src/spydroid/data/local/SettingsManager.h"

class BrowserSetup : public QWidget {
    Q_OBJECT  // Asegúrate de que esta macro esté aquí

public:
    BrowserSetup(QWidget *parent = nullptr);
protected:
    void hideEvent(QHideEvent *event) override;
    void onPathEditingFinished();
    

private slots:
    void openFileDialog();

private:
    QLineEdit *pathLineEdit;
    SettingsManager* settingsManager;
};

#endif // BROWSERSETUP_H
