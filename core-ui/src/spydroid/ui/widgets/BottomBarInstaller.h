#ifndef BOTTOMBARINSTALLER_H
#define BOTTOMBARINSTALLER_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>

class BottomBarInstaller : public QWidget
{
    Q_OBJECT

public:
    explicit BottomBarInstaller(QWidget *parent = nullptr);
    
    // Setters para habilitar/deshabilitar los botones
    void setBackButtonEnabled(bool enabled);
    void setCustomButtonEnabled(bool enabled);
    void setCancelButtonEnabled(bool enabled);

    // Setter para cambiar el texto del botón personalizado
    void setCustomButtonText(const QString &text);

signals:
    // Señales para manejar los clics de los botones
    void backButtonClicked();
    void customButtonClicked();
    void cancelButtonClicked();

private:
    // Elementos del layout
    QPushButton *m_backButton;
    QPushButton *m_customButton;
    QPushButton *m_cancelButton;
    QFrame *m_separator;
};

#endif // BOTTOMBARINSTALLER_H
