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

#include "SelectTemplate.h"
#include <iostream>
#include <QPainter>
#include <QDebug>
#include <QScrollArea>
#include <QPainter>


SelectTemplate::SelectTemplate(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    // Crear el QScrollArea para envolver el contenido
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);  // Hace que el contenido cambie de tamaño dinámicamente
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // Ocupa todo el espacio disponible

    // Hacer que el fondo del QScrollArea sea transparente
    scrollArea->setStyleSheet("QScrollArea { background: transparent; }"
                              "QWidget { background: transparent; }");  // Aplicar fondo transparente

    content = new CardTemplate();
    content->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QMap<QString, QString> templates;
    templates.insert(":template_instagram", "Instagram");
    templates.insert(":template_facebook", "Facebook");
    templates.insert(":template_yt_music", "Youtube Music");
    templates.insert(":template_calculator", "Calculadora");

    content->setTemplates(templates);

    // Definir la lambda de selección de tarjeta
    content->onTemplateSelected = [this](QString selectedTemplate) {
        templateCard = selectedTemplate;        
        qDebug() << "Template seleccionado: " << templateCard;
    };

    // Añadir el contenido al QScrollArea
    scrollArea->setWidget(content);

    // Añadir el QScrollArea al layout en la parte superior
    layout->addWidget(scrollArea, 1);  // Hacer que se expanda y ocupe todo el espacio disponible

    // Añadir la barra inferior con los botones
    bottomBar = new BottomBarInstaller();
    bottomBar->setCustomButtonText("Siguiente");
    bottomBar->setBackButtonEnabled(false);
    bottomBar->setCustomButtonEnabled(true);
    bottomBar->setCancelButtonEnabled(true);

    layout->addWidget(bottomBar, 0, Qt::AlignBottom);

    connect(bottomBar, &BottomBarInstaller::customButtonClicked, this, &SelectTemplate::goToNextPage);
    connect(bottomBar, &BottomBarInstaller::backButtonClicked, this, &SelectTemplate::goToBackPage);
    connect(bottomBar, &BottomBarInstaller::cancelButtonClicked, this, &SelectTemplate::goToCancel);

    setLayout(layout);
}


void SelectTemplate::goToNextPage() {
    emit nextPage(templateCard);
}

void SelectTemplate::goToBackPage() {
    emit backPage();
}

void SelectTemplate::goToCancel() {
    emit cancel();
}