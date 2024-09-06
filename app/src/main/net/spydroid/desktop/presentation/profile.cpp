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

#include "profile.h"
#include "../components/goBack.h"
#include "QString"

Profile::Profile(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(600, 500);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, QColor("#260006"));  // El mismo color que la ventana principal
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    



    backPage = goBack(this, [this]() {
        emit goToHome();
    });


    vncData.ip = "192.168.100.242";
    vncData.port = 5300;

    vncConnect = new QPushButton("Connect to VNC", this);  // Botón para conectar al VNC

    connect(vncConnect, &QPushButton::clicked, this, &Profile::onConnectToVnc);
    // Crear el layout vertical
    layout = new QVBoxLayout(this);

    // Crear y configurar el QLabel
    label = new QLabel("Vista de Perfil", this);
    label->setAlignment(Qt::AlignCenter);


    layout->addWidget(backPage);
    layout->addWidget(vncConnect);
    layout->addWidget(label);
    // Establecer el layout para esta vista
    this->setLayout(layout);
}


void Profile::onConnectToVnc() {
    QString ip = QString::fromStdString(vncData.ip);
    QString port = QString::number(vncData.port);

    // Crear el comando concatenando la IP y el puerto
    QString command = 
        QString("bash -c '/tmp/vnc_viewer %1:%2 &' 2>/dev/null")
            .arg(ip)
            .arg(port);

    std::cout << command.toStdString().c_str() << std::endl;      

    // Ejecutar el comando
    system(command.toStdString().c_str());
}