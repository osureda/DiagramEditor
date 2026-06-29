/**
 * @file selectabledatabutton.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of SelectableDataButton class.
 * @date Monday, July 20, 2026
 */
#include "selectabledatabutton.h"

#include <QLabel>
#include <QSize>
#include <QVBoxLayout>
#include <QWidget>

const QString SelectableDataButton::STYLE_SHEET =
    "text-align: left;"
    "padding-left: 12px;"
    "padding-right: 12px;"
    "padding-top: 12px;"
    "padding-bottom: 12px;";

SelectableDataButton::SelectableDataButton(int iconSize, QWidget *parent)
    : QPushButton(parent)
    , storedIconSize(iconSize)
    , spacingApplied(false)
{}

void SelectableDataButton::loadFromHash(const QVariantHash &hash) {
    loadLeftIconFromVariant(hash["icon"]);
    loadTextFromVariants(hash["name"], hash["description"]);

    storedData = hash;
}

QVariantHash SelectableDataButton::data() const {
    return storedData;
}

SelectableDataButton *SelectableDataButton::leftIconButton() const {
    SelectableDataButton *button = textButton();

    button->setIconSize(QSize(storedIconSize, storedIconSize));
    button->setIcon(storedIcon);

    return button;
}

QPair<QWidget*, SelectableDataButton*> SelectableDataButton::upperIconButton() const {
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    QLabel *iconLabel = new QLabel();
    SelectableDataButton *button = textButton();

    iconLabel->setAlignment(Qt::AlignHCenter);
    iconLabel->setPixmap(storedIcon.pixmap(storedIconSize, storedIconSize));

    layout->addWidget(iconLabel);
    layout->addWidget(button);

    return {widget, button};
}

void SelectableDataButton::loadLeftIconFromVariant(const QVariant &variant) {
    storedIcon = QIcon(variant.toString());
}

void SelectableDataButton::loadTextFromVariants(const QVariant &nameVariant, const QVariant &descriptionVariant) {
    const QString title = nameVariant.toString();
    const QString subtitle = descriptionVariant.toString();

    storedText = subtitle == ""
        ? title
        : title.toUpper() + "\n\n" + subtitle;

    if (!spacingApplied && !storedIcon.isNull()) {
        applyIconTextSpacing();
        spacingApplied = true;
    }
}

void SelectableDataButton::applyIconTextSpacing() {
    QString spacing = "";
    for (int i = 0; i < ICON_TEXT_SPACING; i++) {
        spacing += " ";
    }

    storedText = spacing + storedText.replace("\n", "\n" + spacing);
}

SelectableDataButton *SelectableDataButton::textButton() const {
    SelectableDataButton *button = new SelectableDataButton(storedIconSize, parentWidget());

    button->loadFromHash(storedData);
    button->setStyleSheet(STYLE_SHEET);
    button->setText(storedText);
    button->setCheckable(true);

    return button;
}
