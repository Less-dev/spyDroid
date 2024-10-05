#include "CardWidgetVerify.h"
#include <QResizeEvent>
#include <QDebug>
// Constructor de CardWidgetVerify
CardWidgetVerify::CardWidgetVerify(const QString& path, QWidget *parent)
    : QWidget(parent), installationPath(path) {

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

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);  // Asegurarse que el contenido sea redimensionable

    float size_ssdk = 538.65;
    float size_sdk = 493.6;
    float size_sdk_build_tools = 55.6;
    float size_sdk_platform_14 = 60.3;
    float size_sdk_platform_tools = 5.64;
    float source_android = 43.4;
    float sizeTotal =  size_ssdk + size_sdk + size_sdk_build_tools + size_sdk_platform_14 + size_sdk_platform_tools + source_android;

    QFrame *scrollableFrame = new QFrame(this);
    QVBoxLayout *scrollableLayout = new QVBoxLayout(scrollableFrame);
    scrollableLayout->setContentsMargins(0, 0, 0, 0);  // Márgenes internos para el contenido del scroll
    scrollableLayout->setAlignment(Qt::AlignTop);  // Alinear al tope


    TitleLabel* ssdk_folder = new TitleLabel("Carpeta SSDK", this);
    scrollableLayout->addWidget(ssdk_folder);
    
    folder_ssdk = new DescriptionLabel(installationPath + "/SSdk", this);
    scrollableLayout->addWidget(folder_ssdk);

    TitleLabel* sdk_folder = new TitleLabel("Carpeta SDK", this);
    scrollableLayout->addWidget(sdk_folder);
    folder_sdk = new DescriptionLabel(installationPath + "/Sdk", this);
    scrollableLayout->addWidget(folder_sdk);
    TitleLabel* total_size_download = new TitleLabel("Tamaño Total de Descarga", this);
    scrollableLayout->addWidget(total_size_download);
    DescriptionLabel* size_download = new DescriptionLabel(QString::number(sizeTotal / 1024.0, 'f', 1) + " GB", this);
    scrollableLayout->addWidget(size_download);
    TitleLabel* jdk_componentent_download = new TitleLabel("Spydroid Componentes de Descarga", this);
    scrollableLayout->addWidget(jdk_componentent_download);

    scrollableLayout->addSpacing(20);
    QString ssdk = "Spydroid SDK 0.0.1 \t\t\t\t"+ QString::number(size_ssdk) + " MB";
    DescriptionLabel* component_1 = new DescriptionLabel(ssdk, this);
    scrollableLayout->addWidget(component_1);
    scrollableLayout->addSpacing(20);

    QString jdk = "Open JDK 17 \t\t\t\t\t"+ QString::number(size_sdk) + " MB";
    DescriptionLabel* component_2 = new DescriptionLabel(jdk, this);
    scrollableLayout->addWidget(component_2);
    scrollableLayout->addSpacing(20);  
    
    TitleLabel* sdk_componentes_download = new TitleLabel("SDK Componentes de Descarga", this);
    scrollableLayout->addWidget(sdk_componentes_download);
    scrollableLayout->addSpacing(20); 
    QString sdk_tools = "Android SDK Build-Tools 34  \t\t\t\t\t"+ QString::number(size_sdk_build_tools) + " MB";
    DescriptionLabel* component_3 = new DescriptionLabel(sdk_tools, this);
    scrollableLayout->addWidget(component_3);

    scrollableLayout->addSpacing(20);  
    QString sdk_platform = "Android SDK Platform 14  \t\t\t\t\t\t"+ QString::number(size_sdk_platform_14) + " MB";
    DescriptionLabel* component_4 = new DescriptionLabel(sdk_platform, this);
    scrollableLayout->addWidget(component_4);

    scrollableLayout->addSpacing(20);  
    QString sdk_platform_tools = "Android SDK Platform-Tools  \t\t\t\t\t"+ QString::number(size_sdk_platform_tools) + " MB";
    DescriptionLabel* component_5 = new DescriptionLabel(sdk_platform_tools, this);
    scrollableLayout->addWidget(component_5);

    scrollableLayout->addSpacing(20);  
    QString android_34 = "Sources for Android 34  \t\t\t\t\t\t"+ QString::number(source_android) + " MB";
    DescriptionLabel* component_6 = new DescriptionLabel(android_34, this);
    scrollableLayout->addWidget(component_6);

    scrollableFrame->setLayout(scrollableLayout);

    scrollArea->setWidget(scrollableFrame);
    
    mainLayout->addWidget(scrollArea);

    card->setLayout(mainLayout);
}

void CardWidgetVerify::setPath(const QString& path) {
    installationPath = path;
    if (folder_ssdk) {
        folder_ssdk->setText(installationPath + "/SSdk");
    }

    if (folder_sdk) {
        folder_sdk->setText(installationPath + "/Sdk");
    }

    // Si es necesario, también podrías hacer un repaint
    this->update();
}

// Método paintEvent de CardWidgetVerify
void CardWidgetVerify::paintEvent(QPaintEvent *event) {
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

// Constructor de TitleLabel
CardWidgetVerify::TitleLabel::TitleLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent) {
    setStyleSheet("QLabel { color: #F5F5F5; font-weight: bold; font-size: 15px; }");
}

// Constructor de DescriptionLabel
CardWidgetVerify::DescriptionLabel::DescriptionLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent) {
    setStyleSheet("QLabel { color: #F5F5F5; font-weight: light; font-size: 12px; }");
}


void CardWidgetVerify::resizeEvent(QResizeEvent *event)
{
    // Llamar a la implementación base primero
    QWidget::resizeEvent(event);

    // Obtener el tamaño disponible del widget (CardWidgetVerify)
    QSize availableSize = event->size();

    // Calcular el 80% del ancho disponible
    int newWidth = static_cast<int>(availableSize.width() * 0.97);

    // Calcular el 80% del alto disponible
    int newHeight = static_cast<int>(availableSize.height() * 0.80);

    // Establecer el nuevo tamaño del scrollArea al 80% de ancho y alto
    QScrollArea* scrollArea = findChild<QScrollArea*>();
    if (scrollArea) {
        scrollArea->setFixedHeight(newHeight); 
        scrollArea->setFixedWidth(newWidth);  
    }
}
