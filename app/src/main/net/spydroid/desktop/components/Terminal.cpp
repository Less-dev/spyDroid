#include "Terminal.h"

Terminal::Terminal(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

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

    layout->addWidget(terminal);
}


void Terminal::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    terminal->update();
}
