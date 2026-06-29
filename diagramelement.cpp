/**
 * @file diagramelement.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of DiagramElement class.
 * @date Monday, July 20, 2026
 */
#include "diagramelement.h"

#include "diagramitem.h"
#include "specificationsform.h"

#include <QBrush>
#include <QGraphicsItem>
#include <QLineF>
#include <QPolygonF>
#include <QString>

const QColor DiagramElement::OUTLINE_COLOR = Qt::black;

DiagramElement::DiagramElement(DiagramItem *parent)
    : QGraphicsPolygonItem(parent)
    , internalElement(nullptr)
    , resizer(nullptr)
    , specifications(new ElementSpecifications(this))
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    componentGroup = parent;

    connect(specifications, &ElementSpecifications::sizeChanged,
                     this, &DiagramElement::specificationsSizeChanged);
}

DiagramElement::~DiagramElement() {
    delete resizer;
    delete specifications;
}

void DiagramElement::loadFromHash(const QVariantHash &hash) {
    loadBrushColor(hash["color"].toString());

    stroke = GeometryUtils::strokeFromString(hash["stroke"].toString());
    setPen(GeometryUtils::makePen(OUTLINE_COLOR, OUTLINE_WIDTH, stroke));

    externalShape = GeometryUtils::shapeFromString(hash["externalShape"].toString());
    internalShape = GeometryUtils::shapeFromString(hash["internalShape"].toString());
    size = QPointF(hash["width"].toDouble(), hash["height"].toDouble());
    innerShapePadding = hash["innerShapePadding"].toDouble();

    loadExternalShape();
    loadInternalShape();

    addResizer();

    specifications->loadFromHash(hash["specifications"].toHash());
}

QVariantHash DiagramElement::toHash() const {
    QVariantHash hash;

    hash["color"] = brushColor.name();
    hash["stroke"] = GeometryUtils::strokeName(stroke);
    hash["externalShape"] = GeometryUtils::shapeName(externalShape);
    hash["internalShape"] = GeometryUtils::shapeName(internalShape);
    hash["width"] = size.x();
    hash["height"] = size.y();
    hash["innerShapePadding"] = innerShapePadding;

    hash["specifications"] = specifications == nullptr
        ? QVariantHash{}
        : specifications->toHash();

    return hash;
}

SpecificationsForm *DiagramElement::specificationsForm() const {
    return specifications == nullptr
        ? new SpecificationsForm()
        : specifications->form();
}

void DiagramElement::setSpecifications(const SpecificationsForm *formResults, int formIndex) {
    if (specifications != nullptr) {
        specifications->applyFormResults(formResults, formIndex);
    }
}

void DiagramElement::setShadow(bool shadowed) {
    QBrush myBrush = brush();

    if (shadowed) {
        myBrush.setColor(Qt::gray);
    } else {
        myBrush.setColor(brushColor);
    }

    setBrush(myBrush);
}

void DiagramElement::setResizersVisibility(bool visible) {
    if (resizer != nullptr) {
        resizer->setVisible(visible);
    }
}

bool DiagramElement::canResizeTo(const QPointF &pos) const {
    const QPointF minSize = specifications == nullptr
        ? QPointF(0, 0)
        : specifications->size();

    return pos.x() >= minSize.x() && pos.y() >= minSize.y();
}

void DiagramElement::resize() {
    if (resizer != nullptr) {
        size = mapFromScene(resizer->sceneCenterPos());

        loadExternalShape();
        loadInternalShape();

        updateCommentBadgePos();
        specifications->updateSpecificationsPos();

        componentGroup->updateGeometry();

        emit componentResized();
    }
}

void DiagramElement::specificationsSizeChanged() {
    if (resizer != nullptr) {
        const QPointF specificationsSize = specifications->size();

        const QPointF newSize(
            qMax(size.x(), specificationsSize.x()),
            qMax(size.y(), specificationsSize.y())
        );

        if (newSize != size) {
            resizer->setSceneCenterPos(mapToScene(newSize));
            resize();
        }
    }
}

void DiagramElement::loadBrushColor(const QString &colorName) {
    brushColor = QColor(colorName);
    if (brushColor.isValid()) {
        setBrush(QBrush(brushColor));
    }
}

void DiagramElement::loadExternalShape() {
    setPolygon(GeometryUtils::makePolygon(externalShape, size));
}

void DiagramElement::loadInternalShape() {
    delete internalElement;

    internalElement = new QGraphicsPolygonItem(this);
    internalElement->setPen(pen());
    internalElement->setPolygon(GeometryUtils::makePolygon(internalShape, size - 2 * QPointF(innerShapePadding, innerShapePadding)));
    internalElement->setPos(innerShapePadding, innerShapePadding);
}

void DiagramElement::addResizer() {
    if (resizer == nullptr) {
        resizer = new DiagramResizer(this);
        resizer->setSceneCenterPos(mapToScene(boundingRect().bottomRight()));
        resizer->setVisible(isSelected());
    }
}

QPointF DiagramElement::commentBadgePos() {
    return closestConnectionPoint(QPointF(
        boundingRect().right(),
        boundingRect().top() - COMMENT_BADGE_RADIUS
    ), true);
}

QPointF DiagramElement::closestConnectionMappedPoint(const QPointF &mappedPoint) const {
    const QPolygonF polygonPoints = polygon();
    if (polygonPoints.isEmpty()) {
        return mappedPoint;
    }

    int n = polygonPoints.size();
    QPointF closestPoint = polygonPoints.first();
    for (int i = 0; i < n; i++) {
        const QPointF segmentPoint = GeometryUtils::closestPointOnSegment(polygonPoints[i], polygonPoints[(i + 1) % n], mappedPoint);
        if (QLineF(segmentPoint, mappedPoint).length() < QLineF(closestPoint, mappedPoint).length()) {
            closestPoint = segmentPoint;
        }
    }

    return closestPoint;
}
