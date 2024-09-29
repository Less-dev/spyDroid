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

#ifndef CODE_SYNTAX_HIGHLIGTHER_H
#define CODE_SYNTAX_HIGHLIGTHER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QBrush>
#include <QFont>
#include <QFontDatabase>

class CodeSyntaxHighlighter : public QSyntaxHighlighter {
public:
    CodeSyntaxHighlighter(QTextDocument *parent = nullptr)
        : QSyntaxHighlighter(parent) {

        // Cargar fuentes JetBrains Mono
        QFontDatabase::addApplicationFont(":fonts/JetBrainsMono-Italic");
        QFontDatabase::addApplicationFont(":fonts/JetBrainsMono-Regular");
        QFontDatabase::addApplicationFont(":fonts/JetBrainsMono-Bold");

        // Configurar la fuente base para el editor
        QFont baseFont("JetBrains Mono", 12.5);

        // 1. Reglas para palabras clave (color cian)
        QFont boldFont("JetBrains Mono", 12.5, QFont::Bold);
        addHighlightingRule({
            "class", "fun", "val", "var", "if", "else", "for", "while", "when", "do", "return",
            "null", "is", "in", "as", "break", "continue", "package", "import", "throw", "try",
            "catch", "finally", "interface", "object", "enum", "sealed", "constructor", "init",
            "super", "this", "typeof"
        }, QColor("#C792EA"), boldFont);

        // 2. Reglas para tipos (color amarillo)
        QFont typeFont("JetBrains Mono", 12.5, QFont::Bold);
        addHighlightingRule({"Int", "String", "Boolean", "Float", "Double", "Unit", "Long", "Short", "Byte", "Char"},
                            QColor("#FFCB6B"), typeFont);

        // 3. Reglas para literales booleanos (color rosa)
        QFont literalFont("JetBrains Mono", 12.5);
        addHighlightingRule({"true", "false"}, QColor("#F07178"), literalFont);

        // 4. Reglas para números (color naranja)
        QTextCharFormat numberFormat;
        numberFormat.setForeground(QColor("#F78C6C"));
        numberFormat.setFont(baseFont);
        rulePatterns.append({QRegularExpression("\\b[0-9]+(\\.[0-9]+)?\\b"), numberFormat});

        // 5. Reglas para operadores (color azul claro)
        QTextCharFormat operatorFormat;
        operatorFormat.setForeground(QColor("#89DDFF"));
        operatorFormat.setFont(baseFont);
        rulePatterns.append({QRegularExpression("[\\+\\-\\*/%=!<>|&^~]+"), operatorFormat});

        // 6. Reglas para cadenas (color verde)
        QTextCharFormat stringFormat;
        stringFormat.setForeground(QColor("#C3E88D"));
        stringFormat.setFont(baseFont);
        rulePatterns.append({QRegularExpression("\".*\""), stringFormat});
        rulePatterns.append({QRegularExpression("'.?'"), stringFormat});  // Literales de caracteres

        // 7. Reglas para anotaciones (color lila)
        QTextCharFormat annotationFormat;
        annotationFormat.setForeground(QColor("#BB80B3"));
        annotationFormat.setFont(baseFont);
        rulePatterns.append({QRegularExpression("@[A-Za-z]+"), annotationFormat});

        // 8. Reglas para comentarios de una línea (color gris)
        QTextCharFormat singleLineCommentFormat;
        singleLineCommentFormat.setFont(QFont(":fonts/JetBrainsMono-Italic", 12.5));
        singleLineCommentFormat.setFontItalic(true);  // Aplicar cursiva
        singleLineCommentFormat.setForeground(QColor(169, 169, 169));  // Gris claro

        rulePatterns.append({QRegularExpression("//[^\n]*"), singleLineCommentFormat});

        // 9. Reglas para comentarios multilínea (color gris claro)
        multiLineCommentFormat = singleLineCommentFormat;
        commentStartPattern = QRegularExpression("/\\*");
        commentEndPattern = QRegularExpression("\\*/");

        QFont visibilityFont("JetBrains Mono", 12.5, QFont::ExtraBold);
        addHighlightingRule({"protected", "private", "public", "internal"}, QColor("#82AAFF"), visibilityFont);
    }

    // Función para agregar reglas dinámicas
    void addHighlightingRule(const QStringList &words, const QColor &color, const QFont &font) {
        QTextCharFormat format;
        format.setForeground(QBrush(color));
        format.setFont(font);

        for (const QString &word : words) {
            HighlightingRule rule;
            rule.pattern = QRegularExpression(QStringLiteral("\\b%1\\b").arg(QRegularExpression::escape(word)));
            rule.format = format;
            rulePatterns.append(rule);
        }
    }

protected:
    void highlightBlock(const QString &text) override {
        // Aplicar las reglas de resaltado de palabras clave, tipos, literales, etc.
        for (const HighlightingRule &rule : rulePatterns) {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }

        // Aplicar reglas de resaltado de comentarios multilínea
        setCurrentBlockState(0);

        int startIndex = 0;
        if (previousBlockState() != 1)
            startIndex = text.indexOf(commentStartPattern);

        while (startIndex >= 0) {
            QRegularExpressionMatch endMatch = commentEndPattern.match(text, startIndex);
            int endIndex = endMatch.hasMatch() ? endMatch.capturedStart() : text.length();
            int commentLength = endIndex - startIndex + (endMatch.hasMatch() ? endMatch.capturedLength() : 0);

            setFormat(startIndex, commentLength, multiLineCommentFormat);

            // Si no se encuentra el final del comentario, marcamos el estado del bloque
            if (!endMatch.hasMatch())
                setCurrentBlockState(1);

            startIndex = text.indexOf(commentStartPattern, startIndex + commentLength);
        }
    }

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> rulePatterns;  // Almacena las reglas de resaltado

    QTextCharFormat multiLineCommentFormat;
    QRegularExpression commentStartPattern;
    QRegularExpression commentEndPattern;
};


#endif // CODE_SYNTAX_HIGHLIGTHER_H