/**
 * @file elementspecifications.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of ElementSpecifications class.
 * @date Monday, July 20, 2026
 */
#include "elementspecifications.h"

#include "diagramelement.h"
#include "diagramspecification.h"
#include "specificationsform.h"

#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPen>
#include <QRectF>

const QColor ElementSpecifications::SEPARATOR_PATH_COLOR = Qt::black;

ElementSpecifications::ElementSpecifications(DiagramElement *parent)
    : SpecificationsGroup(parent)
    , verticalSpecificationsBottom(MARGINS)
{}

void ElementSpecifications::loadFromHash(const QVariantHash &hash) {
    const QPointF oldSize = size();

    SpecificationsGroup::loadFromHash(hash);

    for (auto it = hash.cbegin(); it != hash.cend(); ++it) {
        QVariantHash specificationData = it.value().toHash();

        int order = specificationData["order"].toInt();
        if (specificationsPositions.size() <= order) {
            specificationsPositions.resize(order + 1);
        }

        specificationsPositions[order] = posFromString(specificationData["position"].toString());

        DiagramSpecification *specification = specifications[order];
        specification->setParentItem(diagramComponent->graphicsItem());
    }

    updateSpecificationsPos();

    if (oldSize != size()) {
        emit sizeChanged(size() - oldSize);
    }
}

QVariantHash ElementSpecifications::toHash() const {
    QVariantHash hash = SpecificationsGroup::toHash();

    for (int i = 0; i < specifications.size(); i++) {
        QVariantHash specificationData = hash[specificationsIds[i]].toHash();

        specificationData["position"] = stringFromPos(specificationsPositions[i]);

        hash[specificationsIds[i]] = specificationData;
    }

    return hash;
}

void ElementSpecifications::applyFormResults(const SpecificationsForm *formResults, int formIndex) {
    const QPointF oldSize = size();

    SpecificationsGroup::applyFormResults(formResults, formIndex);

    updateSpecificationsPos();

    if (oldSize != size()) {
        emit sizeChanged(size() - oldSize);
    }
}

void ElementSpecifications::updateSpecificationsPos() {
    clearDecorations();

    verticalSpecificationsBottom = MARGINS;

    for (int i = 0; i < specifications.size(); i++) {
        if (specificationsPositions[i] == SpecificationPos::VerticalSeparated) {
            addVerticalSeparator();
        }

        specifications[i]->setPos(specificationPosPoint(i));

        if (specificationsPositions[i] == SpecificationPos::Vertical || specificationsPositions[i] == SpecificationPos::VerticalSeparated) {
            verticalSpecificationsBottom += specifications[i]->boundingRect().height();
        }
    }
}

QPointF ElementSpecifications::size() const {
    qreal maxX = 2 * MARGINS;
    qreal maxY = 2 * MARGINS;

    for (DiagramSpecification *specification : specifications) {
        maxX = qMax(specification->boundingRect().width() + 2 * MARGINS, maxX);
        maxY = qMax(specification->boundingRect().height() + 2 * MARGINS, maxY);
    }

    maxY = qMax(verticalSpecificationsBottom + MARGINS, maxY);

    return QPointF(maxX, maxY);
}

QPointF ElementSpecifications::specificationPosPoint(int specificationIndex) const {
    const QRectF elementRect = diagramComponent->graphicsItem()->boundingRect();
    const QRectF specificationRect = specifications[specificationIndex]->boundingRect();

    switch (specificationsPositions[specificationIndex]) {
        case SpecificationPos::TopLeft:
            return elementRect.topLeft() + QPointF(MARGINS, MARGINS) - specificationRect.topLeft();
        case SpecificationPos::Center:
            return elementRect.center() - specificationRect.center();
        default:
            return QPointF(
                elementRect.center().x() - specificationRect.center().x(),
                verticalSpecificationsBottom - specificationRect.top()
            );
    }
}

void ElementSpecifications::clear() {
    SpecificationsGroup::clear();

    specificationsPositions.clear();
}

void ElementSpecifications::addVerticalSeparator() {
    QGraphicsPathItem *separator = new QGraphicsPathItem(diagramComponent->graphicsItem());

    QPen pen(SEPARATOR_PATH_COLOR, SEPARATOR_PATH_WIDTH);
    separator->setPen(pen);

    QPainterPath path;
    path.moveTo(diagramComponent->graphicsItem()->boundingRect().left(), 0);
    path.lineTo(diagramComponent->graphicsItem()->boundingRect().right(), 0);
    separator->setPath(path);

    separator->setPos(0, verticalSpecificationsBottom);
    specificationsDecorations.append(separator);
    verticalSpecificationsBottom += SEPARATOR_PATH_WIDTH;
}

void ElementSpecifications::clearDecorations() {
    for (auto it = specificationsDecorations.begin(); it != specificationsDecorations.end(); ++it) {
        delete *it;
    }
    specificationsDecorations.clear();
}

ElementSpecifications::SpecificationPos ElementSpecifications::posFromString(const QString &string) {
    if (string == "center") {
        return SpecificationPos::Center;
    } else if (string == "vertical") {
        return SpecificationPos::Vertical;
    } else if (string == "verticalSeparated") {
        return SpecificationPos::VerticalSeparated;
    } else if (string != "topLeft") {
        qCritical() << "Unrecognized element position type: " << string;
    }
    return SpecificationPos::TopLeft;
}

QString ElementSpecifications::stringFromPos(const ElementSpecifications::SpecificationPos &pos) {
    switch (pos) {
        case SpecificationPos::TopLeft:
            return "topLeft";
        case SpecificationPos::Center:
            return "center";
        case SpecificationPos::Vertical:
            return "vertical";
        default:
            return "verticalSeparated";
    }
}
