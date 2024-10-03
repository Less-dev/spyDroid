/*
 * Copyright (C) 2024 Daniel Gómez(Less)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "SetupVerify.h"
#include <QPainter>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QCheckBox>

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>

class CardWidgetVerify : public QWidget {
public:
    CardWidgetVerify(QWidget *parent = nullptr) : QWidget(parent) {
        QFrame *card = new QFrame(this);

        QLabel *title = new QLabel("Configuración actual", this);
        title->setStyleSheet(
            "QLabel { color: white; background-color: black; font-size: 16px; padding: 0 10px; }"
        );
        title->move(25, -2);  
        title->raise();  

        QVBoxLayout *layout = new QVBoxLayout(card);
        layout->setContentsMargins(20, 70, 20, 20);  
        layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);  

        card->setLayout(layout);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen pen(Qt::red, 2);  
        painter.setPen(pen);
        painter.setBrush(QBrush(Qt::black));  

        QRect rect = this->rect();
        rect.adjust(1, 1, -1, -1);  
        painter.drawRoundedRect(rect, 15, 15); 

        QWidget::paintEvent(event);
    }
};


SetupVerify::SetupVerify(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    topBarInstaller = new BannerHorizontal();
    topBarInstaller->setTitle("Verificar Configuraciones");
    topBarInstaller->setDescription("Si desea verificar o cambiar alguna de las configuraciones de instalación, haga clic en Volver.");
    layout->addWidget(topBarInstaller, 0, Qt::AlignTop);

    layout->addStretch();
    CardWidgetVerify* content = new CardWidgetVerify();
    content->setMinimumSize(750, 300);
    layout->addWidget(content, 0, Qt::AlignCenter);  // Alinear al centro del layout
    layout->addStretch();

    bottomBarInstaller = new BottomBarInstaller();
    bottomBarInstaller->setCustomButtonText("Finalizar");
    bottomBarInstaller->setBackButtonEnabled(true);
    bottomBarInstaller->setCustomButtonEnabled(true);
    bottomBarInstaller->setCancelButtonEnabled(true);
    layout->addWidget(bottomBarInstaller, 0, Qt::AlignBottom);

    connect(bottomBarInstaller, &BottomBarInstaller::customButtonClicked, this, &SetupVerify::goToNextPage);
    connect(bottomBarInstaller, &BottomBarInstaller::backButtonClicked, this, &SetupVerify::goToBackPage);
}

void SetupVerify::onStartCheckBoxStateChanged(int state)
{
    // El botón de "Siguiente" se habilita si el checkbox está seleccionado (estado "Qt::Checked")
    bool isChecked = (state == Qt::Checked);
    bottomBarInstaller->setCustomButtonEnabled(isChecked);
}


void SetupVerify::goToBackPage() {
    emit backPage();
}

void SetupVerify::goToNextPage() {
    emit nextPage();
}

void SetupVerify::paintEvent(QPaintEvent *event)
{
    // Llamar al método de la clase base
    QWidget::paintEvent(event);

    // Crear un objeto QPainter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Configuración del pincel (brush) con transparencia
    QBrush brush(QColor(0, 0, 0, 205));  // Color negro con transparencia
    painter.setBrush(brush);

    // Configuración del bolígrafo (pen) para el borde
    QPen pen(QColor("#800000"));  // Color del borde (rojo oscuro)
    pen.setWidth(4);  // Ancho del borde
    painter.setPen(pen);

    // Dibujar un rectángulo redondeado con márgenes
    int margin = 12.5;
    painter.drawRoundedRect(margin, margin, width() - 2 * margin, height() - 2 * margin, 15, 15);
}
