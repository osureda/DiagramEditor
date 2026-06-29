/**
 * @file selectablespecification.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of SelectableSpecification class.
 * @date Monday, July 20, 2026
 */
#include "selectablespecification.h"

#include <QComboBox>
#include <QGraphicsItem>
#include <QString>
#include <QWidget>

SelectableSpecification::SelectableSpecification(QGraphicsItem *parent)
    : DiagramSpecification(parent)
{}

void SelectableSpecification::loadFromHash(const QVariantHash &hash) {
    choices = hash["choices"].toStringList();

    DiagramSpecification::loadFromHash(hash);
}

QVariantHash SelectableSpecification::toHash() const {
    QVariantHash hash = DiagramSpecification::toHash();

    hash["choices"] = choices;

    return hash;
}

QWidget *SelectableSpecification::form() const {
    QComboBox *choiceSelector = new QComboBox();

    if (fixed) {
        choiceSelector->addItem(toPlainText());
    } else {
        for (const QString &choice : choices) {
            choiceSelector->addItem(choice);
        }
    }
    choiceSelector->setCurrentText(toPlainText());

    return choiceSelector;
}

void SelectableSpecification::loadTextFromVariant(const QVariant &variant) {
    setPlainText(variant.toString());
}

QVariant SelectableSpecification::variantFromText() const {
    return toPlainText();
}

void SelectableSpecification::updateTextFromForm(const QWidget *fromResults) {
    const QComboBox *choiceSelector = qobject_cast<const QComboBox*>(fromResults);
    if (choiceSelector) {
        setPlainText(choiceSelector->currentText());
    }
}
