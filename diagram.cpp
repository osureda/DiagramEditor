/**
 * @file diagram.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of Diagram class.
 * @date Monday, July 20, 2026
 */
#include "diagram.h"

#include "diagramcomponent.h"
#include "diagramitem.h"
#include "specificationsform.h"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QLabel>
#include <QPointF>
#include <QTransform>
#include <QWidget>

Diagram::Diagram(int sceneSize, QObject *parent)
    : QGraphicsScene(parent)
    , editionMode(EditionMode::AddItemMode)
    , draggingResizer(false)
    , shadowedItem(nullptr)
    , selectedSingleItemIndex(-1)
{
    setSceneRect(0, 0, sceneSize, sceneSize);

    connect(this, &QGraphicsScene::selectionChanged,
            this, &Diagram::updateSelectedItem);
}

void Diagram::loadFromHash(const QVariantHash &hash) {
    clear();

    for (const QVariant &itemData : hash["items"].toList()) {
        DiagramItem *newItem = new DiagramItem(this);
        newItem->loadFromHash(itemData.toHash());
    }
    for (DiagramItem *item : diagramItems()) {
        item->connectComponents();
    }
}

QVariantHash Diagram::toHash() const {
    QVariantList itemsData;

    for (const DiagramItem *item : diagramItems()) {
        itemsData.append(item->toHash());
    }

    return {
        {"items", itemsData}
    };
}

void Diagram::setEditionMode(const Diagram::EditionMode &mode) {
    QList<QGraphicsView*> myViews = views();

    if (mode == EditionMode::SelectionMode) {
        myViews.first()->setDragMode(QGraphicsView::RubberBandDrag);
    } else {
        myViews.first()->setDragMode(QGraphicsView::NoDrag);
    }

    editionMode = mode;
}

void Diagram::setDraggingResizer(bool dragging) {
    for (DiagramItem *item : diagramItems()) {
        item->setFlag(QGraphicsItem::ItemIsMovable, !dragging);
    }

    draggingResizer = dragging;
}

void Diagram::setSpecifications(const QWidget *formResults) {
    DiagramItem *selectedItem = selectedSingleItem();
    if (selectedItem != nullptr) {
        selectedItem->setSpecifications(qobject_cast<const SpecificationsForm*>(formResults));
    }
}

DiagramItem *Diagram::diagramItemAt(const QPointF &pos) const {
    for (DiagramItem *item : diagramItems()) {
        if (item->boundingRect().contains(item->mapFromScene(pos))) {
            return item;
        }
    }

    return nullptr;
}

int Diagram::newDiagramItemId() const {
    int maxId = 0;

    for (const DiagramItem *item : diagramItems()) {
        if (item->itemId() > maxId) {
            maxId = item->itemId();
        }
    }

    return maxId + 1;
}

DiagramComponent *Diagram::diagramComponentAt(const QPointF &pos, DiagramComponent *exception) const {
    for (DiagramItem *item : diagramItems()) {
        DiagramComponent *component = item->componentAt(pos);
        if (component != nullptr && component != exception) {
            return component;
        }
    }

    return nullptr;
}

DiagramComponent *Diagram::componentByIds(int itemId, int componentId) const {
    for (const DiagramItem *item : diagramItems()) {
        if (item->itemId() == itemId) {
            return item->componentById(componentId);
        }
    }

    return nullptr;
}

void Diagram::selectNextItem() {
    const QList<DiagramItem*> items = diagramItems();

    if (!items.isEmpty()) {
        int nextItemIndex = selectedSingleItemIndex < items.size() - 1
            ? selectedSingleItemIndex + 1
            : 0;

        clearSelection();
        items[nextItemIndex]->setSelected(true);

        selectedSingleItemIndex = nextItemIndex;
    }
}

void Diagram::moveSelectedItems(const QPointF &moveStep) {
    for (QGraphicsItem *item : selectedDiagramItems()) {
        item->moveBy(moveStep.x(), moveStep.y());
    }
}

void Diagram::deleteSelectedItems() {
    for (QGraphicsItem *item : selectedDiagramItems()) {
        if (diagramItems().indexOf(item) <= selectedSingleItemIndex) {
            selectedSingleItemIndex--;
        }

        removeItem(item);
        delete item;
    }
}

void Diagram::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (!draggingResizer) {
        DiagramItem *touchedItem = diagramItemAt(event->scenePos());
        if (touchedItem != shadowedItem) {
            if (shadowedItem != nullptr) {
                shadowedItem->setShadow(false);
            }
            if (touchedItem != nullptr) {
                touchedItem->setShadow(true);
            }
            shadowedItem = touchedItem;
        }
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void Diagram::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    const QPointF pressPos = event->scenePos();
    bool handleMousePress = true;

    if (editionMode == EditionMode::AddResizerMode || editionMode == EditionMode::RemoveResizerMode) {
        DiagramItem *diagramItem = diagramItemAt(pressPos);
        if (diagramItem != nullptr && diagramItem->isSelected() &&
            diagramItem->setResizerEnabled(pressPos, editionMode == EditionMode::AddResizerMode)) {
            handleMousePress = false;
        }
    }

    if (handleMousePress) {
        QGraphicsScene::mousePressEvent(event);
    }

    if (editionMode == EditionMode::AddItemMode && !itemAt(pressPos, QTransform())) {
        emit itemRequested(pressPos);
    }
}

void Diagram::updateSelectedItem() {
    const DiagramItem *selectedItem = selectedSingleItem();

    if (selectedItem == nullptr) {
        emit selectedItemChanged(emptySpecificationsForm());
    } else {
        selectedSingleItemIndex = diagramItems().indexOf(selectedItem);
        emit selectedItemChanged(selectedItem->specificationsForm());
    }
}

QList<DiagramItem*> Diagram::diagramItems() const {
    QList<DiagramItem*> diagramItems;

    for (QGraphicsItem *item : items()) {
        DiagramItem *diagramItem = qgraphicsitem_cast<DiagramItem*>(item);
        if (diagramItem) {
            diagramItems.append(diagramItem);
        }
    }

    return diagramItems;
}

QList<DiagramItem*> Diagram::selectedDiagramItems() const {
    QList<DiagramItem*> selectedDiagramItems;

    for (QGraphicsItem *item : selectedItems()) {
        DiagramItem *diagramItem = qgraphicsitem_cast<DiagramItem*>(item);
        if (diagramItem) {
            selectedDiagramItems.append(diagramItem);
        }
    }

    return selectedDiagramItems;
}

DiagramItem *Diagram::selectedSingleItem() const {
    const QList<QGraphicsItem*> items = selectedItems();

    return items.size() == 1
       ? qgraphicsitem_cast<DiagramItem*>(items.first())
       : nullptr;
}

QWidget *Diagram::emptySpecificationsForm() {
    return new QLabel("Select a single item");
}
