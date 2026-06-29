/**
 * @file diagramspecification.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of DiagramSpecification class.
 * @date Monday, July 20, 2026
 */
#include "longtextspecification.h"

#include <QGraphicsItem>
#include <QTextEdit>
#include <QWidget>

namespace DiagramEditor::Specification {

LongTextSpecification::LongTextSpecification(QGraphicsItem *parent)
    : DiagramSpecification(parent)
{}

QWidget *LongTextSpecification::form() const {
    QTextEdit *textEditor = new QTextEdit();

    textEditor->setPlainText(toPlainText());
    textEditor->setReadOnly(fixed);

    return textEditor;
}

void LongTextSpecification::loadTextFromVariant(const QVariant &variant) {
    setPlainText(variant.toString());
}

QVariant LongTextSpecification::variantFromText() const {
    return toPlainText();
}

void LongTextSpecification::updateTextFromForm(const QWidget *fromResults) {
    const QTextEdit *textEditor = qobject_cast<const QTextEdit*>(fromResults);
    if (textEditor) {
        setPlainText(textEditor->toPlainText());
    }
}

}
