#include "CodeEditor.h"
#include "CodeSyntaxHighlighter.h"
#include <QPainter>
#include <QTextBlock>
#include <QBrush>
#include <QFontDatabase>
#include <QFont>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

CodeEditor::CodeEditor(QWidget *parent)
    : QPlainTextEdit(parent), lineNumberArea(new LineNumberArea(this)) {

    // Hacer el fondo del widget completamente transparente
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background: transparent;");  // Asegurar que no haya color de fondo aplicado

    // Configurar el color del texto como blanco
    QPalette p = this->palette();
    p.setColor(QPalette::Text, Qt::white);  // Texto en blanco
    this->setPalette(p);

    QFontDatabase::addApplicationFont(":/fonts/JetBrainsMono-Italic");
    QFontDatabase::addApplicationFont(":/fonts/JetBrainsMono-Regular");
    QFontDatabase::addApplicationFont(":/fonts/JetBrainsMono-Bold");

    CodeSyntaxHighlighter* syntaxHighlighter = new CodeSyntaxHighlighter(this->document());

    // Configurar la fuente predeterminada del editor
    QFont font("JetBrains Mono");
    font.setPointSize(14);
    this->setFont(font);

    // Ejemplo: añadir palabras clave dinámicas
    QFont boldFont("JetBrains Mono", 14, QFont::Bold);  // Fuente JetBrains Mono Bold
    syntaxHighlighter->addHighlightingRule({"class", "if", "else", "for", "while"}, Qt::cyan, boldFont);

    QFont italicFont("JetBrains Mono", 14, QFont::StyleItalic);  // Fuente JetBrains Mono Italic
    syntaxHighlighter->addHighlightingRule({"return", "void", "int"}, Qt::magenta, italicFont);


    this->setLineWrapMode(QPlainTextEdit::NoWrap);
    this->setTabStopDistance(4 * fontMetrics().horizontalAdvance(' '));  // Tab equivale a 4 espacios


    // Conectar señales y slots para el área de los números de línea
    connect(this, &QPlainTextEdit::blockCountChanged, this, [this]() {
        updateLineNumberAreaWidth(0);
    });
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

void CodeEditor::paintEvent(QPaintEvent *event) {
    QPainter painter(viewport());  // Usar el viewport para pintar solo el área visible
    painter.setRenderHint(QPainter::Antialiasing);

    // Color de fondo negro con 45% de opacidad (para líneas no seleccionadas)
    QColor backgroundColor = QColor(0, 0, 0, 115);  // Negro con alfa = 115 (45% de transparencia)
    // Color rojo para la línea seleccionada
    QColor selectedLineColor = QColor(147, 23, 25, 115);  // Rojo #931719 con transparencia

    // Obtenemos el cursor actual para detectar la línea seleccionada
    QTextCursor cursor = textCursor();
    QTextBlock block = firstVisibleBlock();

    int top = static_cast<int>(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + static_cast<int>(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QRectF blockRect(0, top, viewport()->width(), fontMetrics().height());

            if (block.blockNumber() == cursor.blockNumber()) {
                painter.fillRect(blockRect, selectedLineColor);
            } else {
                painter.fillRect(blockRect, backgroundColor); 
            }
        }

        block = block.next();
        top = bottom;
        bottom = top + static_cast<int>(blockBoundingRect(block).height());
    }

    QPlainTextEdit::paintEvent(event);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event) {
    QPainter painter(lineNumberArea);

    QColor backgroundColor = QColor(0, 0, 0, 115);
    painter.fillRect(event->rect(), backgroundColor);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = static_cast<int>(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + static_cast<int>(blockBoundingRect(block).height());

    QFont lineNumberFont("Monaco");
    lineNumberFont.setPointSize(12);
    painter.setFont(lineNumberFont);

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::white);  // Color blanco para los números de línea
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + static_cast<int>(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void CodeEditor::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(147, 23, 25, 166);  // Rojo semitransparente
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}


void CodeEditor::loadFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("No se puede abrir el archivo: %1").arg(filePath));
        return;
    }

    QTextStream in(&file);
    setPlainText(in.readAll());  // Cargar el contenido del archivo en el editor
    file.close();

    currentFilePath = filePath;  // Guardar la ruta del archivo abierto
}

bool CodeEditor::saveFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("No se puede guardar el archivo: %1").arg(filePath));
        return false;
    }

    QTextStream out(&file);
    out << toPlainText();  // Escribir el contenido actual del editor al archivo
    file.close();

    currentFilePath = filePath;  // Actualizar la ruta del archivo guardado
    return true;
}

void CodeEditor::openFileDialog() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Abrir archivo"), "", tr("Archivos de texto (*.txt);;Archivos C++ (*.cpp *.h);;Todos los archivos (*)"));
    if (!filePath.isEmpty()) {
        loadFile(filePath);  // Cargar el archivo seleccionado
    }
}

void CodeEditor::saveFileDialog() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Guardar archivo"), "", tr("Archivos de texto (*.txt);;Archivos C++ (*.cpp *.h);;Todos los archivos (*)"));
    if (!filePath.isEmpty()) {
        saveFile(filePath);  // Guardar el archivo en la ruta seleccionada
    }
}

//

// Calcula el ancho necesario para los números de línea.
int CodeEditor::lineNumberAreaWidth() const {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
    return space;
}

// Responde a los cambios de tamaño y ajusta la geometría del área de números de línea.
void CodeEditor::resizeEvent(QResizeEvent *event) {
    QPlainTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

// Actualiza el ancho del área de números de línea.
void CodeEditor::updateLineNumberAreaWidth(int) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

// Actualiza el área de números de línea cuando hay cambios en el contenido o se hace scroll.
void CodeEditor::updateLineNumberArea(const QRect &rect, int dy) {
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}