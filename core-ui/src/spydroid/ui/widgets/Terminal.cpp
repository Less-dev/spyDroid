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

#include "Terminal.h"
#include <QFrame>

Terminal::Terminal(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Eliminar el espaciado entre los widgets
    layout->setSpacing(0);

    // Eliminar márgenes del layout
    layout->setContentsMargins(0, 0, 0, 0);

    // Crear un QFrame para el borde superior
    QFrame *topBorder = new QFrame(this);
    topBorder->setFixedHeight(2);  // Grosor del borde de 2 px
    topBorder->setStyleSheet("background-color: #f0f0f5;");  // Color blanco pastel

    // Inicializar el widget de terminal
    terminal = new QTermWidget(this);

    // Cambiar el esquema de color del terminal
    terminal->setColorScheme("WhiteOnBlack");

    // Configurar fuente monoespaciada
    QFont monospaceFont("Monospace", 12);

    // Verificar si la fuente monoespaciada está disponible
    if (!QFontDatabase::systemFont(QFontDatabase::FixedFont).fixedPitch()) {
        monospaceFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    }

    terminal->setTerminalFont(monospaceFont);
    terminal->setScrollBarPosition(QTermWidget::ScrollBarRight);

    // Agregar el borde y luego el terminal al layout sin espacio entre ellos
    layout->addWidget(topBorder);  // Agregar el borde superior
    layout->addWidget(terminal);   // Agregar el terminal debajo del borde
}

void Terminal::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    terminal->update();
}

