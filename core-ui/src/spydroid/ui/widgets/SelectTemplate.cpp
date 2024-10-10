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

SelectTemplate::SelectTemplate(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    content = new CardTemplate();
    
    content->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QMap<QString, QString> templates;
    templates.insert(":template_facebook", "Facebook");
    templates.insert(":template_instagram", "Instagram");
    templates.insert(":template_calculator", "Calculadora");
    templates.insert(":template_yt_music", "Youtube Music");

    content->setTemplates(templates);

    // Definir la lambda de selección de tarjeta
    content->onTemplateSelected = [](QString selectedTemplate) {
        qDebug() << "Template seleccionado: " << selectedTemplate;
    };

    layout->addWidget(content, 0, Qt::AlignTop);  // Evita que se expanda totalmente

    // Añadir la barra inferior con los botones
    bottomBar = new BottomBarInstaller();
    bottomBar->setCustomButtonText("Siguiente");
    bottomBar->setBackButtonEnabled(false);
    bottomBar->setCustomButtonEnabled(true);
    bottomBar->setCancelButtonEnabled(true);

    layout->addWidget(bottomBar, 0, Qt::AlignBottom);

    setLayout(layout);
}
