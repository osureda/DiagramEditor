#include "fixedspecification.h"

#include "formwidget.h"

#include <QVariant>
#include <QWidget>

FixedSpecification::FixedSpecification()
    : defaultText("")
    , text("")
{}

FixedSpecification::FixedSpecification(const FixedSpecification *other)
    : DiagramSpecification(other)
    , defaultText(other->defaultText)
    , text(other->text)
{}

DiagramSpecification *FixedSpecification::clone() const {
    return new FixedSpecification(this);
}

QString FixedSpecification::specificationType() const {
    return "fixed";
}

QList<QWidget*> FixedSpecification::specificationsForm() const {
    FormWidget *form = new FormWidget();
    form->addSingleField(displayName, text, false);

    return {form};
}

void FixedSpecification::setSpecifications(QList<QWidget*>) {}

void FixedSpecification::setNull() {
    text = "";
    setPlainText(text);
}

void FixedSpecification::initialize() {
    text = defaultText;
    setPlainText(text);

    DiagramSpecification::initialize();
}

QVariant FixedSpecification::specificationValue() const {
    return text;
}

void FixedSpecification::loadSpecificDataFromHash(const QVariantHash &hash) {
    defaultText = hash["value"].toString();
}
