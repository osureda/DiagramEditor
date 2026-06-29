/**
 * @file specificationsform.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of SpecificationsForm class.
 * @date Monday, July 20, 2026
 */
#include "specificationsform.h"

#include <QFont>
#include <QLabel>
#include <QVBoxLayout>

SpecificationsForm::SpecificationsForm()
{
    formLayout = new QVBoxLayout(this);
    formLayout->setAlignment(Qt::AlignTop);
}

void SpecificationsForm::appendForm(const SpecificationsForm *form) {
    if (form->fieldCount() > 0) {
        formStartIndices.append(formFields.size());

        for (const FormField &field: form->formFields) {
            appendField(field.name, field.widget);
        }
    }
}

void SpecificationsForm::appendField(const QString &fieldName, QWidget *fieldWidget) {
    if (formStartIndices.isEmpty()) {
        formStartIndices.append(0);
    }
    formFields.append(FormField{fieldName, fieldWidget});

    formLayout->addWidget(field(fieldName, fieldWidget));
}

int SpecificationsForm::formCount() const {
    return formStartIndices.size();
}

int SpecificationsForm::fieldCount() const {
    return formFields.size();
}

QWidget *SpecificationsForm::fieldResults(int formIndex, const QString &fieldName) const {
    if (formIndex >= 0 && formIndex < formStartIndices.size()) {
        int stopIndex = formIndex == formStartIndices.size() - 1
            ? formFields.size()
            : formStartIndices[formIndex + 1];

        for (int i = formStartIndices[formIndex]; i < stopIndex; i++) {
            if (formFields[i].name == fieldName) {
                return formFields[i].widget;
            }
        }
    }

    return nullptr;
}

QWidget *SpecificationsForm::field(const QString &fieldName, QWidget *fieldWidget) const {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setAlignment(Qt::AlignTop);

    QLabel *label = new QLabel(fieldName + ":");
    QFont font = label->font();
    font.setBold(true);
    label->setFont(font);

    layout->addWidget(label);
    layout->addWidget(fieldWidget);

    return widget;
}
