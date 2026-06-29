/**
 * @file shorttextspecification.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of ShortTextSpecification class.
 * @date Monday, July 20, 2026
 */
#include "shorttextspecification.h"

#include <QGraphicsItem>
#include <QLineEdit>
#include <QWidget>

ShortTextSpecification::ShortTextSpecification(QGraphicsItem *parent)
    : DiagramSpecification(parent)
{}

QWidget *ShortTextSpecification::form() const {
    QLineEdit *textEditor = new QLineEdit();

    textEditor->setText(toPlainText());
    textEditor->setReadOnly(fixed);

    return textEditor;
}

void ShortTextSpecification::loadTextFromVariant(const QVariant &variant) {
    setPlainText(variant.toString());
}

QVariant ShortTextSpecification::variantFromText() const {
    return toPlainText();
}

void ShortTextSpecification::updateTextFromForm(const QWidget *fromResults) {
    const QLineEdit *textEditor = qobject_cast<const QLineEdit*>(fromResults);
    if (textEditor) {
        setPlainText(textEditor->text());
    }
}
