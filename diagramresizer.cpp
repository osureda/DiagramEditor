/**
 * @file diagramresizer.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of DiagramResizer class.
 * @date Monday, July 20, 2026
 */
#include "diagramresizer.h"

#include "diagram.h"
#include "diagramcomponent.h"

#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsScene>

const QColor DiagramResizer::COLOR = Qt::black;

DiagramResizer::DiagramResizer(DiagramComponent *parent)
    : QGraphicsRectItem(0, 0, SIZE, SIZE)
    , parentComponent(parent)
    , parentItem(parent->graphicsItem())
{
    setBrush(QBrush(COLOR));

    setZValue(50);

    setAcceptedMouseButtons(Qt::LeftButton);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    if (parentItem->scene() != nullptr) {
        parentItem->scene()->addItem(this);

        connect(parentComponent, &DiagramComponent::positionChanged,
                this, &DiagramResizer::updateParentPosition);
    }
}

QPointF DiagramResizer::sceneCenterPos() const {
    return mapToScene(rect().center());
}

void DiagramResizer::setSceneCenterPos(const QPointF &position) {
    setPos(position - rect().center());
    parentMappedPos = parentItem->mapFromScene(pos());
}

void DiagramResizer::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qobject_cast<Diagram*>(scene())->setDraggingResizer(true);

    QGraphicsRectItem::mousePressEvent(event);
}

void DiagramResizer::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsRectItem::mouseMoveEvent(event);

    parentComponent->resize();
    parentMappedPos = parentItem->mapFromScene(pos());
}

void DiagramResizer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsRectItem::mouseReleaseEvent(event);

    qobject_cast<Diagram*>(scene())->setDraggingResizer(false);
}

QVariant DiagramResizer::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionChange && parentComponent != nullptr) {
        const QPointF newCenterPos = parentItem->mapFromScene(value.toPointF() + rect().center());
        if (!parentComponent->canResizeTo(newCenterPos)) {
            return pos();
        }
    }

    return QGraphicsRectItem::itemChange(change, value);
}

void DiagramResizer::updateParentPosition() {
    if (parentItem != nullptr) {
        setPos(parentItem->mapToScene(parentMappedPos));
    }
}
