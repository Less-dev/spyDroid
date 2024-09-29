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

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QWidget>
#include <QString>

// Forward declaration de LineNumberArea
class LineNumberArea;

class CodeEditor : public QPlainTextEdit {
    Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = nullptr);

    // Método público para obtener el ancho del área de números de línea.
    int lineNumberAreaWidth() const;
    
    void loadFile(const QString &filePath);

    // Método público para guardar el archivo actual
    bool saveFile(const QString &filePath);

    // Método para solicitar y abrir un archivo
    void openFileDialog();

    // Método para solicitar y guardar el archivo
    void saveFileDialog();

protected:
    // Reimplementamos resizeEvent para ajustar el área de números de línea.
    void resizeEvent(QResizeEvent *event) override;

    // Método que será llamado para pintar los números de línea.
    void lineNumberAreaPaintEvent(QPaintEvent *event);

private slots:
    // Slot para actualizar el ancho del área de números de línea.
    void updateLineNumberAreaWidth(int newBlockCount);

    // Slot para sincronizar el área de números de línea al desplazarse o actualizar el texto.
    void updateLineNumberArea(const QRect &rect, int dy);

    // Slot para resaltar la línea actual donde está el cursor.
    void highlightCurrentLine();

private:
    QWidget *lineNumberArea;  // Widget para el área de números de línea.
    QString currentFilePath;
    // Clase interna para definir el área de números de línea.
    class LineNumberArea : public QWidget {
    public:
        explicit LineNumberArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor) {}

        QSize sizeHint() const override {
            return QSize(codeEditor->lineNumberAreaWidth(), 0);
        }

    protected:
        void paintEvent(QPaintEvent *event) override {
            codeEditor->lineNumberAreaPaintEvent(event);
        }

    private:
        CodeEditor *codeEditor;  // Puntero al editor principal.
    };

    // Método auxiliar para actualizar la geometría y propiedades del área de números de línea.
    void updateLineNumberAreaWidth();
    void paintEvent(QPaintEvent *event);
};

#endif // CODEEDITOR_H
