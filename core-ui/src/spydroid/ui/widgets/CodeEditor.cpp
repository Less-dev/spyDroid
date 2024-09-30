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
#include <QMimeDatabase>

CodeEditor::CodeEditor(QWidget *parent)
    : QPlainTextEdit(parent), lineNumberArea(new LineNumberArea(this)) {

    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background: transparent;");

    QPalette p = this->palette();
    p.setColor(QPalette::Text, Qt::white);
    this->setPalette(p);

    QFontDatabase::addApplicationFont(":/fonts/JetBrainsMono-Italic");
    QFontDatabase::addApplicationFont(":/fonts/JetBrainsMono-Regular");
    QFontDatabase::addApplicationFont(":/fonts/JetBrainsMono-Bold");

    CodeSyntaxHighlighter* syntaxHighlighter = new CodeSyntaxHighlighter(this->document());

    QFont font("JetBrains Mono");
    font.setPointSize(14);
    this->setFont(font);

    QFont boldFont("JetBrains Mono", 14, QFont::Bold);
    syntaxHighlighter->addHighlightingRule({"class", "if", "else", "for", "while"}, Qt::cyan, boldFont);

    QFont italicFont("JetBrains Mono", 14, QFont::StyleItalic);
    syntaxHighlighter->addHighlightingRule({"return", "void", "int"}, Qt::magenta, italicFont);


    this->setLineWrapMode(QPlainTextEdit::NoWrap);
    this->setTabStopDistance(4 * fontMetrics().horizontalAdvance(' '));  // Tab 4 space


    connect(this, &QPlainTextEdit::blockCountChanged, this, [this]() {
        updateLineNumberAreaWidth(0);
    });
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

void CodeEditor::paintEvent(QPaintEvent *event) {
    QPainter painter(viewport());  
    painter.setRenderHint(QPainter::Antialiasing);

    QColor backgroundColor = QColor(0, 0, 0, 115); 
    QColor selectedLineColor = QColor(147, 23, 25, 115);  

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

        QColor lineColor = QColor(147, 23, 25, 166);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}


void CodeEditor::loadFile(const QString &filePath) {
    if (filePath.isEmpty()) {
        return;
    }

    if (filePath == currentFilePath) {
        return;
    }

    QMimeDatabase mimeDatabase;
    QMimeType mimeType = mimeDatabase.mimeTypeForFile(filePath);

    if (mimeType.name().startsWith("video/") || mimeType.name().startsWith("audio/") ||
        mimeType.name().startsWith("image/") || mimeType.name().startsWith("application/octet-stream")) {
        QMessageBox::warning(this, tr("Error"), tr("El archivo no es un archivo de texto compatible"));
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("No se puede abrir el archivo"));
        return;
    }

    QByteArray fileContent = file.peek(1024);
    for (char c : fileContent) {
        if (static_cast<unsigned char>(c) < 0x09 || (static_cast<unsigned char>(c) > 0x0D && static_cast<unsigned char>(c) < 0x20)) {
            QMessageBox::warning(this, tr("Error"), tr("El archivo parece ser binario y no se puede abrir"));
            file.close();
            return;
        }
    }

    QTextStream in(&file);
    setPlainText(in.readAll());
    file.close();

    currentFilePath = filePath;
}

bool CodeEditor::saveFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("No se puede guardar el archivo: %1").arg(filePath));
        return false;
    }

    QTextStream out(&file);
    out << toPlainText();
    file.close();

    currentFilePath = filePath;
    return true;
}

void CodeEditor::openFileDialog() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Abrir archivo"), "", tr("Archivos de texto (*.txt);;Archivos C++ (*.cpp *.h);;Todos los archivos (*)"));
    if (!filePath.isEmpty()) {
        loadFile(filePath);
    }
}

void CodeEditor::saveFileDialog() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Guardar archivo"), "", tr("Archivos de texto (*.txt);;Archivos C++ (*.cpp *.h);;Todos los archivos (*)"));
    if (!filePath.isEmpty()) {
        saveFile(filePath);
    }
}

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

void CodeEditor::resizeEvent(QResizeEvent *event) {
    QPlainTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::updateLineNumberAreaWidth(int) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy) {
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}