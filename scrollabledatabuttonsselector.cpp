/**
 * @file scrollabledatabuttonsselector.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of ScrollableDataButtonsSelector class.
 * @date Monday, July 20, 2026
 */
#include "scrollabledatabuttonsselector.h"

#include "selectabledatabutton.h"

#include <QAbstractButton>
#include <QButtonGroup>
#include <QDebug>
#include <QGridLayout>
#include <QWidget>

namespace DiagramEditor::Gui {

ScrollableDataButtonsSelector::ScrollableDataButtonsSelector(QWidget *parent)
    : ScrollableDataButtonsSelector(1, 0, false, parent)
{}

ScrollableDataButtonsSelector::ScrollableDataButtonsSelector(int nColumns, int iconsSize, bool upperIcons, QWidget *parent)
    : QScrollArea(parent)
    , buttons(new QButtonGroup(this))
    , nColumns(nColumns)
    , nButtons(0)
    , iconsSize(iconsSize)
    , upperIcons(upperIcons)
{
    buttons->setExclusive(true);

    QWidget *widget = new QWidget();
    layout = new QGridLayout(widget);
    layout->setAlignment(Qt::AlignTop);
    if (upperIcons) {
        layout->setSpacing(UPPER_ICONS_SPACING);
    }
    setWidgetResizable(true);
    setWidget(widget);

    connect(buttons, &QButtonGroup::idToggled,
            this, &ScrollableDataButtonsSelector::buttonToggled);
}

void ScrollableDataButtonsSelector::addButtons(const QVariantHash &buttonsData) {
    for (auto it = buttonsData.cbegin(); it != buttonsData.cend(); ++it) {
        const QVariantHash buttonData = it.value().toHash();
        if (buttonData.isEmpty()) {
            qCritical() << "No JSON object was found for key " << it.key();
        } else {
            addButton(buttonData);
        }
    }
}

QVariantHash ScrollableDataButtonsSelector::selectedButtonData() const {
    const SelectableDataButton *button = qobject_cast<SelectableDataButton*>(buttons->checkedButton());

    return button == nullptr
        ? QVariantHash{}
        : button->data();
}

void ScrollableDataButtonsSelector::clear() {
    while (layout->count() > 0) {
        QLayoutItem *layoutItem = layout->takeAt(0);
        delete layoutItem->widget();
        delete layoutItem;

        nButtons--;
    }
}

void ScrollableDataButtonsSelector::buttonToggled(int buttonId, bool checked) {
    if (checked) {
        const SelectableDataButton *button = qobject_cast<SelectableDataButton*>(buttons->button(buttonId));
        emit selectionChanged(button->data());
    }
}

void ScrollableDataButtonsSelector::addButton(const QVariantHash &buttonData) {
    SelectableDataButton *newButton = new SelectableDataButton(iconsSize);
    newButton->loadFromHash(buttonData);
    QWidget *newButtonWidget;

    if (upperIcons) {
        QPair<QWidget*, SelectableDataButton*> upperIconButton = newButton->upperIconButton();
        newButtonWidget = upperIconButton.first;
        newButton = upperIconButton.second;
    } else {
        newButton = newButton->leftIconButton();
        newButtonWidget = newButton;
    }

    buttons->addButton(newButton, nButtons);
    layout->addWidget(newButtonWidget, nButtons / nColumns, nButtons % nColumns);
    nButtons++;
}

}
