#include "CardWidgetVerify.h"
#include <QResizeEvent>

// Constructor de CardWidgetVerify
CardWidgetVerify::CardWidgetVerify(QWidget *parent)
    : QWidget(parent) {

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

    card->setLayout(mainLayout);
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
