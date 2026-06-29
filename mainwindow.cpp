/**
 * @file mainwindow.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of MainWindow class.
 * @date Monday, July 20, 2026
 */
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "diagram.h"
#include "diagramitem.h"
#include "jsonfile.h"
#include "jsonserializable.h"
#include "scrollabledatabuttonsselector.h"
#include "wizard.h"

#include <QAbstractButton>
#include <QApplication>
#include <QButtonGroup>
#include <QClipboard>
#include <QKeySequence>
#include <QLayoutItem>
#include <QPointF>
#include <QPushButton>
#include <QShortcut>
#include <QToolButton>
#include <QWidget>

namespace DiagramEditor::Gui {

using DiagramEditor::Diagram::Diagram;
using DiagramEditor::Diagram::DiagramItem;
using DiagramEditor::Serialization::JsonFile;
using DiagramEditor::Serialization::JsonSerializable;

MainWindow::MainWindow(const QVariantHash &diagramGroups,
                       const QVariantHash &diagramTypes,
                       const QVariantHash &diagramItems,
                       QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , wizard(new Wizard(diagramGroups, diagramTypes))
    , allDiagramItems(diagramItems)
{
    ui->setupUi(this);

    ui->diagramEditorLayout->insertWidget(0, wizard);
    ui->itemSelectorWidget->hide();
    ui->propertiesPanel->hide();
    ui->editingToolsFrame->hide();
    ui->diagramView->hide();

    connect(wizard, &QWizard::accepted,
            this, &MainWindow::wizardAccepted);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::wizardAccepted() {
    ui->itemSelectorWidget->show();
    ui->propertiesPanel->show();
    ui->editingToolsFrame->show();
    ui->diagramView->show();

    diagram = new Diagram(CANVAS_SIZE);
    ui->diagramView->setScene(diagram);

    const Wizard::Configuration configuration = wizard->selectedConfiguration();
    displayDiagramItems(configuration.diagramItems);

    ui->specificationsContainerLayout->setAlignment(Qt::AlignTop);

    connectWindowActions();
    connectKeyboardActions();
}

void MainWindow::drawItem(const QPointF &pos) {
    const ScrollableDataButtonsSelector *currentSelector =
        qobject_cast<ScrollableDataButtonsSelector*>(ui->itemSelectorWidget->currentWidget());
    const QVariantHash itemData = currentSelector->selectedButtonData();

    if (itemData != QVariantHash{}) {
        DiagramItem *item = new DiagramItem(diagram);
        item->loadFromHash(itemData);
        item->setPos(pos - item->centerOffset());
        item->connectComponents();
        item->setLoaded(true);
    }
}

void MainWindow::setEditionMode(const QAbstractButton *modeButton) {
    if (modeButton == ui->selectionToolButton) {
        diagram->setEditionMode(Diagram::EditionMode::SelectionMode);
    } else if (modeButton == ui->addResizerToolButton) {
        diagram->setEditionMode(Diagram::EditionMode::AddResizerMode);
    } else if (modeButton == ui->removeResizerToolButton) {
        diagram->setEditionMode(Diagram::EditionMode::RemoveResizerMode);
    } else {
        diagram->setEditionMode(Diagram::EditionMode::AddItemMode);
    }
}

void MainWindow::showSpecificationsForm(QWidget *form) {
    clearSpecificationsForm();

    ui->specificationsContainerLayout->addWidget(form);
}

void MainWindow::saveSpecificationsForm() {
    QLayoutItem *formItem = ui->specificationsContainerLayout->itemAt(0);
    if (formItem) {
        diagram->setSpecifications(formItem->widget());
    }
}

void MainWindow::copyJsonToClipboard() const {
    QApplication::clipboard()->setText(ui->jsonTextEdit->toPlainText());
}

void MainWindow::pasteJsonFromClipboard() {
    ui->jsonTextEdit->setPlainText(QApplication::clipboard()->text());
}

void MainWindow::loadJsonFromScene() {
    ui->jsonTextEdit->setPlainText(JsonFile::hashToText(diagram->toHash()));
}

void MainWindow::saveJsonToScene() {
    diagram->loadFromHash(JsonFile::textToHash(ui->jsonTextEdit->toPlainText()));
}

void MainWindow::keyUpPressed() {
    moveDiagramItems(QPointF(0, -ITEM_MOVE_STEP));
}

void MainWindow::keyDownPressed() {
    moveDiagramItems(QPointF(0, ITEM_MOVE_STEP));
}

void MainWindow::keyLeftPressed() {
    moveDiagramItems(QPointF(-ITEM_MOVE_STEP, 0));
}

void MainWindow::keyRightPressed() {
    moveDiagramItems(QPointF(ITEM_MOVE_STEP, 0));
}

void MainWindow::displayDiagramItems(const DiagramType::DiagramItemsIds &requiredDiagramItemsTabs) {
    for (auto it = requiredDiagramItemsTabs.cbegin(); it != requiredDiagramItemsTabs.cend(); ++it) {
        ScrollableDataButtonsSelector *tab = new ScrollableDataButtonsSelector(1, ITEM_ICON_SIZE, false);
        tab->addButtons(JsonSerializable::filteredHashByKeys(allDiagramItems, it.value()));

        ui->itemSelectorWidget->addTab(tab, it.key());
    }
}

void MainWindow::keyEnterPressed() {
    int currentPropertiesTabIndex = ui->propertiesPanel->currentIndex();

    switch (currentPropertiesTabIndex) {
        case 0:
            saveSpecificationsForm();
            break;
        case 1:
            saveJsonToScene();
            break;
    }
}

void MainWindow::connectWindowActions() {
    connect(ui->editionModesButtonGroup, &QButtonGroup::buttonClicked,
            this, &MainWindow::setEditionMode);

    connect(ui->removeItemsToolButton, &QToolButton::clicked,
            diagram, &Diagram::deleteSelectedItems);

    connect(diagram, &Diagram::itemRequested,
            this, &MainWindow::drawItem);

    connect(diagram, &Diagram::selectedItemChanged,
            this, &MainWindow::showSpecificationsForm);

    connect(ui->saveSpecificationsButton, &QPushButton::clicked,
            this, &MainWindow::saveSpecificationsForm);

    connect(ui->copyJsonButton, &QPushButton::clicked,
            this, &MainWindow::copyJsonToClipboard);

    connect(ui->pasteJsonButton, &QPushButton::clicked,
            this, &MainWindow::pasteJsonFromClipboard);

    connect(ui->loadJsonButton, &QPushButton::clicked,
            this, &MainWindow::loadJsonFromScene);

    connect(ui->saveJsonButton, &QPushButton::clicked,
            this, &MainWindow::saveJsonToScene);
}

void MainWindow::connectKeyboardActions() {
    QShortcut *keyTabShortcut = new QShortcut(QKeySequence(Qt::Key_Tab), this);
    QShortcut *keyUpShortcut = new QShortcut(QKeySequence(Qt::Key_Up), this);
    QShortcut *keyDownShortcut = new QShortcut(QKeySequence(Qt::Key_Down), this);
    QShortcut *keyLeftShortcut = new QShortcut(QKeySequence(Qt::Key_Left), this);
    QShortcut *keyRightShortcut = new QShortcut(QKeySequence(Qt::Key_Right), this);
    QShortcut *keyDeleteShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    QShortcut *keyReturnShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    QShortcut *keyEnterShortcut = new QShortcut(QKeySequence(Qt::Key_Enter), this);

    connect(keyTabShortcut, &QShortcut::activated,
            diagram, &Diagram::selectNextItem);

    connect(keyUpShortcut, &QShortcut::activated,
            this, &MainWindow::keyUpPressed);

    connect(keyDownShortcut, &QShortcut::activated,
            this, &MainWindow::keyDownPressed);

    connect(keyLeftShortcut, &QShortcut::activated,
            this, &MainWindow::keyLeftPressed);

    connect(keyRightShortcut, &QShortcut::activated,
            this, &MainWindow::keyRightPressed);

    connect(keyDeleteShortcut, &QShortcut::activated,
            diagram, &Diagram::deleteSelectedItems);

    connect(keyReturnShortcut, &QShortcut::activated,
            this, &MainWindow::keyEnterPressed);

    connect(keyEnterShortcut, &QShortcut::activated,
            this, &MainWindow::keyEnterPressed);
}

void MainWindow::clearSpecificationsForm() {
    while (ui->specificationsContainerLayout->count() > 0) {
        QLayoutItem *item = ui->specificationsContainerLayout->takeAt(0);
        delete item->widget();
        delete item;
    }
}

void MainWindow::moveDiagramItems(const QPointF &moveStep) {
    diagram->moveSelectedItems(moveStep);
}

}
