/**
 * @file connectionspecifications.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of ConnectionSpecifications class.
 * @date Monday, July 20, 2026
 */
#include "connectionspecifications.h"

#include "diagramconnection.h"
#include "diagramspecification.h"
#include "specificationsform.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QRectF>

namespace DiagramEditor::Specification {

ConnectionSpecifications::ConnectionSpecifications(DiagramConnection *parent)
    : SpecificationsGroup(parent)
{
    connect(parent, &DiagramConnection::positionChanged,
            this, &ConnectionSpecifications::updateSpecificationsPos);
}

void ConnectionSpecifications::loadFromHash(const QVariantHash &hash) {
    SpecificationsGroup::loadFromHash(hash);

    for (auto it = hash.cbegin(); it != hash.cend(); ++it) {
        QVariantHash specificationData = it.value().toHash();

        int order = specificationData["order"].toInt();
        if (specificationsPositions.size() <= order) {
            specificationsPositions.resize(order + 1);
        }

        specificationsPositions[order] = {
            horizontalPosFromString(specificationData["horizontalPos"].toString()),
            verticalPosFromString(specificationData["verticalPos"].toString())
        };

        DiagramSpecification *specification = specifications[order];
        diagramComponent->graphicsItem()->scene()->addItem(specification);
        specification->setAcceptedMouseButtons(Qt::LeftButton);
        specification->setFlag(QGraphicsItem::ItemIsSelectable, true);
        specification->setFlag(QGraphicsItem::ItemIsMovable, true);
        specification->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    }

    updateSpecificationsPos();
}

QVariantHash ConnectionSpecifications::toHash() const {
    QVariantHash hash = SpecificationsGroup::toHash();

    for (int i = 0; i < specifications.size(); i++) {
        QVariantHash specificationData = hash[specificationsIds[i]].toHash();

        specificationData["horizontalPos"] = stringFromHorizontalPos(specificationsPositions[i].first);
        specificationData["verticalPos"] = stringFromVerticalPos(specificationsPositions[i].second);

        hash[specificationsIds[i]] = specificationData;
    }

    return hash;
}

void ConnectionSpecifications::applyFormResults(const SpecificationsForm *formResults, int formIndex) {
    SpecificationsGroup::applyFormResults(formResults, formIndex);

    updateSpecificationsPos();
}

void ConnectionSpecifications::updateSpecificationsPos() {
    for (int i = 0; i < specifications.size(); i++) {
        QPointF pos = horizontalPosPoint(i);
        const QRectF specificationRect = specifications[i]->boundingRect();

        pos += specificationsPositions[i].second == VerticalPos::Above
            ? QPointF(0, -VERTICAL_SPACING - specificationRect.bottom())
            : QPointF(0, VERTICAL_SPACING - specificationRect.top());

        specifications[i]->setPos(pos + specifications[i]->movingTranslation());
    }
}

void ConnectionSpecifications::clear() {
    SpecificationsGroup::clear();

    specificationsPositions.clear();
}

QPointF ConnectionSpecifications::horizontalPosPoint(int specificationIndex) const {
    DiagramConnection *connection = dynamic_cast<DiagramConnection*>(diagramComponent);
    const QRectF specificationRect = specifications[specificationIndex]->boundingRect();

    QPointF connectionPos;

    switch (specificationsPositions[specificationIndex].first) {
        case (HorizontalPos::Center):
            connectionPos = connection->path().pointAtPercent(0.5) - QPointF(specificationRect.center().x(), 0);
            break;
        case (HorizontalPos::Begin):
            connectionPos = connection->path().pointAtPercent(0) - QPointF(specificationRect.left() - HORIZONTAL_SPACING, 0);
            break;
        default:
            connectionPos = connection->path().pointAtPercent(1) - QPointF(specificationRect.right() + HORIZONTAL_SPACING, 0);
            break;
    }

    return connection->mapToScene(connectionPos);
}

ConnectionSpecifications::HorizontalPos ConnectionSpecifications::horizontalPosFromString(const QString &string) {
    if (string == "begin") {
        return HorizontalPos::Begin;
    } else if (string == "end") {
        return HorizontalPos::End;
    } else if (string != "center") {
        qCritical() << "Unrecognized connection horizontal position type: " << string;
    }
    return HorizontalPos::Center;
}

ConnectionSpecifications::VerticalPos ConnectionSpecifications::verticalPosFromString(const QString &string) {
    if (string == "below") {
        return VerticalPos::Below;
    } else if (string != "above") {
        qCritical() << "Unrecognized connection vertical position type: " << string;
    }
    return VerticalPos::Above;
}

QString ConnectionSpecifications::stringFromHorizontalPos(const ConnectionSpecifications::HorizontalPos &horizontalPos) {
    switch (horizontalPos) {
        case HorizontalPos::Center:
            return "center";
        case HorizontalPos::Begin:
            return "begin";
        default:
            return "end";
    }
}

QString ConnectionSpecifications::stringFromVerticalPos(const ConnectionSpecifications::VerticalPos &verticalPos) {
    switch (verticalPos) {
        case VerticalPos::Above:
            return "above";
        default:
            return "below";
    }
}

}
