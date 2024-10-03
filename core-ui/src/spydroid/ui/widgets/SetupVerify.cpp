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
#include <QScrollArea>

class CardWidgetVerify : public QWidget {
public:
CardWidgetVerify(QWidget *parent = nullptr) : QWidget(parent) {
    // Crear el QFrame principal
    QFrame *card = new QFrame(this);

    // Título principal
    QLabel *title = new QLabel("Configuración actual", this);
    title->setStyleSheet(
        "QLabel { color: white; background-color: black; font-size: 16px; padding: 0 10px; }"
    );
    title->move(25, -2);  
    title->raise();  

    // Layout para los elementos que no tendrán scroll (antes de skd_folder)
    QVBoxLayout *mainLayout = new QVBoxLayout(card);
    mainLayout->setContentsMargins(20, 50, 20, 0);  
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft); 

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);  // Asegurarse que el contenido sea redimensionable

    float size_jdk = 493.6;
    float size_sdk_build_tools = 55.6;
    float size_sdk_platform_14 = 60.3;
    float sizeTotal = size_jdk + size_sdk_build_tools + size_sdk_platform_14;

    QFrame *scrollableFrame = new QFrame(this);
    QVBoxLayout *scrollableLayout = new QVBoxLayout(scrollableFrame);
    scrollableLayout->setContentsMargins(0, 0, 0, 0);  // Márgenes internos para el contenido del scroll
    scrollableLayout->setAlignment(Qt::AlignTop);  // Alinear al tope

    TitleLabel* skd_folder = new TitleLabel("Carpeta SDK", this);
    scrollableLayout->addWidget(skd_folder);
    DescriptionLabel* folder = new DescriptionLabel("/home/less/SPYDROID/Sdk", this);
    scrollableLayout->addWidget(folder);
    TitleLabel* total_size_download = new TitleLabel("Tamaño Total de Descarga", this);
    scrollableLayout->addWidget(total_size_download);
    DescriptionLabel* size_download = new DescriptionLabel(QString::number(sizeTotal, 'f', 1) + " MB", this);
    scrollableLayout->addWidget(size_download);
    TitleLabel* jdk_componentent_download = new TitleLabel("JDK Componentes de Descarga", this);
    scrollableLayout->addWidget(jdk_componentent_download);
    scrollableLayout->addSpacing(20); 
    QString jdk = "Open JDK 17 \t\t\t\t\t"+ QString::number(size_jdk) + " MB";
    DescriptionLabel* component_1 = new DescriptionLabel(jdk, this);
    scrollableLayout->addWidget(component_1);
    scrollableLayout->addSpacing(20);  
    
    TitleLabel* sdk_componentes_download = new TitleLabel("SDK Componentes de Descarga", this);
    scrollableLayout->addWidget(sdk_componentes_download);
    scrollableLayout->addSpacing(20); 
    QString sdk_tools = "Android SDK Build-Tools 34  \t\t\t\t\t"+ QString::number(size_sdk_build_tools) + " MB";
    DescriptionLabel* component_2 = new DescriptionLabel(sdk_tools, this);
    scrollableLayout->addWidget(component_2);
    scrollableLayout->addSpacing(20);  
    
    QString sdk_platform = "Android SDK Platform 14  \t\t\t\t\t\t"+ QString::number(size_sdk_platform_14) + " MB";
    DescriptionLabel* component_3 = new DescriptionLabel(sdk_platform, this);
    scrollableLayout->addWidget(component_3);

    scrollableFrame->setLayout(scrollableLayout);

    scrollArea->setWidget(scrollableFrame);
    
    mainLayout->addWidget(scrollArea);

    scrollArea->setFixedHeight(220); 
    scrollArea->setFixedWidth(700);  
    card->setLayout(mainLayout);
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

private:
    class TitleLabel : public QLabel {
    public:
        TitleLabel(const QString &text, QWidget *parent = nullptr) : QLabel(text, parent) {
            setStyleSheet("QLabel { color: #F5F5F5; font-weight: bold; font-size: 15px; }");
        }
    };

    class DescriptionLabel : public QLabel {
    public:
        DescriptionLabel(const QString &text, QWidget *parent = nullptr) : QLabel(text, parent) {
            setStyleSheet("QLabel { color: #F5F5F5; font-weight: light; font-size: 12px; }");
        }
    };
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
    layout->addWidget(content, 0, Qt::AlignCenter);
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
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush(QColor(0, 0, 0, 205));
    painter.setBrush(brush);

    QPen pen(QColor("#800000"));
    pen.setWidth(4);  // Width border
    painter.setPen(pen);

    int margin = 12.5;
    painter.drawRoundedRect(margin, margin, width() - 2 * margin, height() - 2 * margin, 15, 15);
}
