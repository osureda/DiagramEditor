/**
 * @file listspecification.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of ListSpecification class.
 * @date Monday, July 20, 2026
 */
#include "listspecification.h"

#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QLayout>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

namespace DiagramEditor::Specification {

ListSpecification::ListSpecification(QGraphicsItem *parent)
    : DiagramSpecification(parent)
{}

void ListSpecification::loadFromHash(const QVariantHash &hash) {
    bullet = hash["bullet"].toString();

    DiagramSpecification::loadFromHash(hash);
}

QVariantHash ListSpecification::toHash() const {
    QVariantHash hash = DiagramSpecification::toHash();

    hash["bullet"] = bullet;

    return hash;
}

QWidget *ListSpecification::form() const {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setAlignment(Qt::AlignTop);

    for (const QString &elem : list) {
        QLineEdit *textEditor = new QLineEdit(elem);
        textEditor->setReadOnly(fixed);
        layout->addWidget(textEditor);
    }

    if (!fixed) {
        formButtons(layout);
    }

    return widget;
}

void ListSpecification::loadTextFromVariant(const QVariant &variant) {
    list = variant.toStringList();

    const QString spacedBullet = bullet == ""
        ? ""
        : bullet + " ";

    QStringList textLines;
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        textLines.append(spacedBullet + *it);
    }

    setPlainText(textLines.join("\n"));
}

QVariant ListSpecification::variantFromText() const {
    return list;
}

void ListSpecification::updateTextFromForm(const QWidget *fromResults) {
    const QLayout *layout = fromResults->layout();
    if (layout) {
        list.clear();

        for (int i = 0; i < layout->count() - 1; i++) {
            const QLineEdit *elemEditor = qobject_cast<QLineEdit*>(layout->itemAt(i)->widget());
            if (elemEditor) {
                list.append(elemEditor->text());
            }
        }

        loadTextFromVariant(list);
    }
}

void ListSpecification::formButtons(QVBoxLayout *formLayout) const {
    QWidget *buttons = new QWidget();
    QHBoxLayout *buttonsLayout = new QHBoxLayout(buttons);
    buttonsLayout->setAlignment(Qt::AlignLeft);

    QToolButton *addElemButton = new QToolButton();
    addElemButton->setFixedSize(FORM_BUTTONS_SIZE, FORM_BUTTONS_SIZE);
    addElemButton->setText("+");
    connect(addElemButton, &QToolButton::clicked, this, [formLayout]() {
        formLayout->insertWidget(formLayout->count() - 1, new QLineEdit());
    });
    buttonsLayout->addWidget(addElemButton);

    QToolButton *removeElemButton = new QToolButton();
    removeElemButton->setFixedSize(FORM_BUTTONS_SIZE, FORM_BUTTONS_SIZE);
    removeElemButton->setText("-");
    connect(removeElemButton, &QToolButton::clicked, this, [formLayout]() {
        if (formLayout->count() > 1) {
            delete formLayout->itemAt(formLayout->count() - 2)->widget();
        }
    });
    buttonsLayout->addWidget(removeElemButton);

    formLayout->addWidget(buttons);
}

}
