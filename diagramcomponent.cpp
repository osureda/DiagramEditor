/**
 * @file diagramcomponent.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of DiagramComponent class.
 * @date Monday, July 20, 2026
 */
#include "diagramcomponent.h"

#include "diagramitem.h"
#include "specificationsform.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPen>

namespace DiagramEditor::Diagram {

const QColor DiagramComponent::COMMENT_BADGE_COLOR = Qt::green;

DiagramComponent::DiagramComponent()
    : commentBadge(nullptr)
{}

QGraphicsItem *DiagramComponent::graphicsItem() {
    return dynamic_cast<QGraphicsItem*>(this);
}

int DiagramComponent::definedZValue() const {
    return 10;
}

void DiagramComponent::connectComponent() {}

SpecificationsForm *DiagramComponent::specificationsForm() const {
    return new SpecificationsForm();
}

void DiagramComponent::setSpecifications(const SpecificationsForm *, int) {}

void DiagramComponent::setShadow(bool) {}

void DiagramComponent::setResizersVisibility(bool) {}

bool DiagramComponent::addResizer(const QPointF &) {
    return false;
}
bool DiagramComponent::removeResizer(const QPointF &) {
    return false;
}

bool DiagramComponent::canResizeTo(const QPointF &) const {
    return true;
}

void DiagramComponent::resize() {}

QPointF DiagramComponent::closestConnectionPoint(const QPointF &point, bool itemMapped) {
    const QPointF mappedPoint = itemMapped
        ? point
        : graphicsItem()->mapFromScene(point);

    const QPointF closestMappedPoint = closestConnectionMappedPoint(mappedPoint);

    return itemMapped
        ? closestMappedPoint
        : graphicsItem()->mapToScene(closestMappedPoint);
}

int DiagramComponent::componentId() const {
    return componentGroup == nullptr
       ? -1
       : componentGroup->componentId(this);
}

int DiagramComponent::groupId() const {
    return componentGroup == nullptr
       ? -1
       : componentGroup->itemId();
}

void DiagramComponent::setCommentBadgeVisibility(bool visible) {
    if (commentBadge == nullptr && visible) {
        commentBadge = makeCommentBadge();
        updateCommentBadgePos();
    } else if (commentBadge != nullptr && !visible) {
        delete commentBadge;
        commentBadge = nullptr;
    }
}

void DiagramComponent::updateCommentBadgePos() {
    if (commentBadge != nullptr) {
        commentBadge->setPos(commentBadgePos());
    }
}

QGraphicsEllipseItem *DiagramComponent::makeCommentBadge() {
    QGraphicsEllipseItem *badge = new QGraphicsEllipseItem(
        -COMMENT_BADGE_RADIUS, -COMMENT_BADGE_RADIUS,
        2 * COMMENT_BADGE_RADIUS, 2 * COMMENT_BADGE_RADIUS,
        graphicsItem()
    );

    badge->setBrush(COMMENT_BADGE_COLOR);
    badge->setPen(QPen(Qt::NoPen));

    return badge;
}

QPointF DiagramComponent::commentBadgePos() {
    return QPointF(0, 0);
}

QPointF DiagramComponent::closestConnectionMappedPoint(const QPointF &mappedPoint) const {
    return mappedPoint;
}

}
