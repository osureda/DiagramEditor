/**
 * @file wizard.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of Wizard class.
 * @date Monday, July 20, 2026
 */
#include "wizard.h"
#include "./ui_wizard.h"

#include "diagramtypegroup.h"
#include "jsonserializable.h"
#include "scrollabledatabuttonsselector.h"

#include <QWidget>

namespace DiagramEditor::Gui {

using DiagramEditor::Serialization::JsonSerializable;

Wizard::Wizard(const QVariantHash &diagramGroups, const QVariantHash &diagramTypes, QWidget *parent)
    : QWizard(parent)
    , ui(new Ui::Wizard)
    , allDiagramTypes(diagramTypes)
{
    ui->setupUi(this);

    ScrollableDataButtonsSelector *diagramGroupsSelector =
        new ScrollableDataButtonsSelector(DIAGRAM_GROUPS_GRID_SIZE, DIAGRAM_GROUP_ICON_SIZE, true);
    diagramGroupsSelector->addButtons(diagramGroups);
    ui->chooseDiagramModelSelectorLayout->addWidget(diagramGroupsSelector);

    diagramTypesSelector = new ScrollableDataButtonsSelector(DIAGRAM_TYPES_GRID_SIZE, DIAGRAM_TYPE_ICON_SIZE, false);
    ui->chooseDiagramModelSelectorLayout->addWidget(diagramTypesSelector);

    connect(diagramGroupsSelector, &ScrollableDataButtonsSelector::selectionChanged,
            this, &Wizard::selectedGroupChanged);
}

Wizard::~Wizard()
{
    delete ui;
}

Wizard::Configuration Wizard::selectedConfiguration() const {
    DiagramType selectedDiagramType;
    selectedDiagramType.loadFromHash(diagramTypesSelector->selectedButtonData());

    return {selectedDiagramType.diagramItems()};
}

void Wizard::selectedGroupChanged(const QVariantHash &selectedGroupData) {
    DiagramTypeGroup selectedGroup;
    selectedGroup.loadFromHash(selectedGroupData);
    QVariantHash requiredDiagramTypes = JsonSerializable::filteredHashByKeys(allDiagramTypes, selectedGroup.diagramTypes());

    diagramTypesSelector->clear();
    diagramTypesSelector->addButtons(requiredDiagramTypes);
}

}
