/**
 * @file connectableresizer.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of ConnectableResizer class.
 * @date Monday, July 20, 2026
 */
#include "connectableresizer.h"

#include "diagram.h"
#include "diagramcomponent.h"
#include "diagramitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPointF>

namespace DiagramEditor::Diagram {

ConnectableResizer::ConnectableResizer(DiagramComponent *parent)
    : DiagramResizer(parent)
    , fixed(false)
    , connectedItemId(-1)
    , connectedComponentId(-1)
    , connectedComponent(nullptr)
    , shadowedComponent(nullptr)
{}

void ConnectableResizer::loadFromHash(const QVariantHash &hash) {
    setSceneCenterPos(QPointF(hash["x"].toDouble(), hash["y"].toDouble()));

    if (hash.contains("defaultConnect")) {
        connectedItemId = parentComponent->groupId();
        connectedComponentId = hash["defaultConnect"].toInt();
    } else if (hash.contains("connect") && hash["connect"].toList().size() >= 2) {
        const QVariantList idsList = hash["connect"].toList();
        connectedItemId = idsList[0].toInt();
        connectedComponentId = idsList[1].toInt();
    }

    fixed = hash["fixed"].toBool();

    connectableTypes = hash["connectableTypes"].toStringList();
}

QVariantHash ConnectableResizer::toHash() const {
    QVariantHash hash;

    hash["x"] = sceneCenterPos().x();
    hash["y"] = sceneCenterPos().y();

    if (connectedComponent != nullptr) {
        hash["connect"] = QVariantList{
            connectedComponent->groupId(),
            connectedComponent->componentId()
        };
    }

    hash["fixed"] = fixed;
    hash["connectableTypes"] = connectableTypes;

    return hash;
}

void ConnectableResizer::connectResizer() {
    disconnectFrom(connectedComponent);
    connectedComponent = nullptr;

    const Diagram *diagramScene = qobject_cast<Diagram*>(parentItem->scene());

    if (diagramScene != nullptr) {
        connectedComponent = diagramScene->componentByIds(connectedItemId, connectedComponentId);
        connectTo(connectedComponent);
        updateParentPosition();
    }
}

void ConnectableResizer::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    DiagramResizer::mouseMoveEvent(event);

    Diagram *diagramScene = qobject_cast<Diagram*>(scene());
    DiagramComponent *touchedComponent = diagramScene->diagramComponentAt(sceneCenterPos(), parentComponent);

    if (shadowedComponent != touchedComponent) {
        if (shadowedComponent != nullptr) {
            shadowedComponent->setShadow(false);
        }

        if (touchedComponent != nullptr && touchedComponent != parentComponent &&
            DiagramItem::componentTypeMatches(touchedComponent, connectableTypes)) {
            touchedComponent->setShadow(true);
            shadowedComponent = touchedComponent;
        } else {
            shadowedComponent = nullptr;
        }
    }
}

void ConnectableResizer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (!fixed) {
        disconnectFrom(connectedComponent);

        if (shadowedComponent != nullptr) {
            connectTo(shadowedComponent);
            connectedComponent = shadowedComponent;
            updateParentPosition();

            shadowedComponent->setShadow(false);
            shadowedComponent = nullptr;
        } else {
            connectedComponent = nullptr;
        }
    }

    DiagramResizer::mouseReleaseEvent(event);
}

QVariant ConnectableResizer::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionChange && fixed && connectedComponent != nullptr) {
        const QPointF newCenterPos = value.toPointF() + rect().center();
        return connectedComponent->closestConnectionPoint(newCenterPos) - rect().center();
    }

    return DiagramResizer::itemChange(change, value);
}

void ConnectableResizer::updateParentPosition() {
    if (connectedComponent == nullptr) {
        DiagramResizer::updateParentPosition();
    } else  {
        setSceneCenterPos(connectedComponent->closestConnectionPoint(parentItem->mapToScene(parentMappedPos) + rect().center()));
        parentComponent->resize();
    }
}

void ConnectableResizer::connectTo(DiagramComponent *component) {
    if (component != nullptr) {
        connect(component, &DiagramComponent::positionChanged,
                this, &ConnectableResizer::updateParentPosition);

        connect(component, &DiagramComponent::componentResized,
                this, &ConnectableResizer::updateParentPosition);
    }
}

void ConnectableResizer::disconnectFrom(DiagramComponent *component) {
    if (component != nullptr) {
        disconnect(component, &DiagramComponent::positionChanged,
                   this, &ConnectableResizer::updateParentPosition);

        disconnect(component, &DiagramComponent::componentResized,
                this, &ConnectableResizer::updateParentPosition);
    }
}

}
