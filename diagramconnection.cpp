/**
 * @file diagramconnection.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of DiagramConnection class.
 * @date Monday, July 20, 2026
 */
#include "diagramconnection.h"

#include "connectableresizer.h"
#include "connectionspecifications.h"
#include "diagramitem.h"
#include "specificationsform.h"

#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QPainterPath>
#include <QPen>
#include <QString>

const QColor DiagramConnection::DEFAULT_COLOR = Qt::black;

const QPointF DiagramConnection::MARKERS_SIZE = QPointF(20, 20);

const QColor DiagramConnection::MARKERS_BRUSH_COLOR = Qt::white;

DiagramConnection::DiagramConnection(DiagramItem *parent)
    : QGraphicsPathItem(parent)
    , startMarker(nullptr)
    , endMarker(nullptr)
    , specifications(new ConnectionSpecifications(this))
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    componentGroup = parent;
}

DiagramConnection::~DiagramConnection() {
    for (auto it = resizers.begin(); it != resizers.end(); ++it) {
        delete *it;
    }

    delete specifications;
}

int DiagramConnection::definedZValue() const {
    return 20;
}

void DiagramConnection::connectComponent() {
    for (auto it = resizers.begin(); it != resizers.end(); ++it) {
        (*it)->connectResizer();
    }
}

void DiagramConnection::loadFromHash(const QVariantHash &hash) {
    penColor = penColorFromString(hash["color"].toString());
    stroke = GeometryUtils::strokeFromString(hash["stroke"].toString());
    setPen(GeometryUtils::makePen(penColor, LINE_WIDTH, stroke));

    startMarkerShape = GeometryUtils::markerFromString(hash["startMarker"].toString());
    endMarkerShape = GeometryUtils::markerFromString(hash["endMarker"].toString());

    for (const QVariant &vertexData : hash["path"].toList()) {
        ConnectableResizer *resizer = new ConnectableResizer(this);
        resizer->loadFromHash(vertexData.toHash());
        storeResizer(resizer);
    }

    resize();

    loadMarkers();
    updateMarkersPolygon();

    specifications->loadFromHash(hash["specifications"].toHash());
}

QVariantHash DiagramConnection::toHash() const {
    QVariantHash hash;

    hash["color"] = penColor.name();
    hash["stroke"] = GeometryUtils::strokeName(stroke);
    hash["startMarker"] = GeometryUtils::markerName(startMarkerShape);
    hash["endMarker"] = GeometryUtils::markerName(endMarkerShape);

    QVariantList pathData;
    for (auto it = resizers.begin(); it != resizers.end(); ++it) {
        pathData.append((*it)->toHash());
    }
    hash["path"] = pathData;

    hash["specifications"] = specifications == nullptr
        ? QVariantHash{}
        : specifications->toHash();

    return hash;
}

SpecificationsForm *DiagramConnection::specificationsForm() const {
    return specifications == nullptr
        ? new SpecificationsForm()
        : specifications->form();
}

void DiagramConnection::setSpecifications(const SpecificationsForm *formResults, int formIndex) {
    if (specifications != nullptr) {
        specifications->applyFormResults(formResults, formIndex);
    }
}

void DiagramConnection::setShadow(bool shadowed) {
    QPen myPen = pen();

    if (shadowed) {
        myPen.setColor(Qt::white);
    } else {
        myPen.setColor(penColor);
    }

    setPen(myPen);
}

void DiagramConnection::setResizersVisibility(bool visible) {
    for (auto it = resizers.begin(); it != resizers.end(); ++it) {
        (*it)->setVisible(visible);
    }
}

bool DiagramConnection::addResizer(const QPointF &scenePos) {
    bool added = false;

    int resizerIndex = newResizerIndex(mapFromScene(scenePos));
    if (resizerIndex != -1) {
        ConnectableResizer *resizer = new ConnectableResizer(this);
        resizer->setSceneCenterPos(scenePos);
        storeResizer(resizer, resizerIndex);

        resize();

        added = true;
    }

    return added;
}

bool DiagramConnection::removeResizer(const QPointF &scenePos) {
    bool removed = false;

    int i = 1;
    while (!removed && i < resizers.size() - 1) {
        DiagramResizer *resizer = resizers[i];
        if (resizer->contains(resizer->mapFromScene(scenePos))) {
            resizers.removeOne(resizer);
            delete resizer;

            resize();

            removed = true;
        } else {
            i++;
        }
    }

    return removed;
}

void DiagramConnection::resize() {
    QPainterPath path;

    if (!resizers.isEmpty()) {
        path.moveTo(mapFromScene(resizers.first()->sceneCenterPos()));
        for (int i = 1; i < resizers.size(); i++) {
            path.lineTo(mapFromScene(resizers[i]->sceneCenterPos()));
        }
    }

    setPath(path);

    updateMarkersPolygon();
    updateCommentBadgePos();
    specifications->updateSpecificationsPos();

    componentGroup->updateGeometry();

    emit componentResized();
}

QColor DiagramConnection::penColorFromString(const QString &string) {
    const QColor color(string);
    return color.isValid()
        ? color
        : DEFAULT_COLOR;
}

QLineF DiagramConnection::segmentAt(int pos, bool reverted) const {
    const QPointF p1(path().elementAt(pos).x, path().elementAt(pos).y);
    const QPointF p2(path().elementAt(pos + 1).x, path().elementAt(pos + 1).y);

    return reverted
        ? QLineF(p2, p1)
        : QLineF(p1, p2);
}

int DiagramConnection::newResizerIndex(const QPointF &pos) const {
    int closestSegmentIndex = 0;
    const QLineF firstSegment = segmentAt(0);
    qreal minDist = QLineF(GeometryUtils::closestPointOnSegment(firstSegment.p1(), firstSegment.p2(), pos), pos).length();

    for (int i = 1 ; i < path().elementCount() - 1; i++) {
        const QLineF segment = segmentAt(i);
        qreal dist = QLineF(GeometryUtils::closestPointOnSegment(segment.p1(), segment.p2(), pos), pos).length();
        if (dist < minDist) {
            closestSegmentIndex = i;
            minDist = dist;
        }
    }

    return minDist <= CLICK_MARGIN
        ? closestSegmentIndex + 1
        : -1;
}

void DiagramConnection::storeResizer(ConnectableResizer *resizer, int index) {
    resizer->setVisible(isSelected());

    if (index == -1) {
        resizers.append(resizer);
    } else {
        resizers.insert(index, resizer);
    }

    resize();
}

void DiagramConnection::loadMarkers() {
    delete startMarker;
    startMarker = makeMarker();

    delete endMarker;
    endMarker = makeMarker();
}

QGraphicsPolygonItem *DiagramConnection::makeMarker() {
    QGraphicsPolygonItem *polygon = new QGraphicsPolygonItem(this);

    QPen markerPen(pen().color(), LINE_WIDTH);
    polygon->setPen(markerPen);
    polygon->setBrush(MARKERS_BRUSH_COLOR);

    return polygon;
}

void DiagramConnection::updateMarkersPolygon() {
    int nVertices = path().elementCount();
    if (nVertices >= 2) {
        if (startMarker != nullptr) {
            startMarker->setPolygon(GeometryUtils::makeMarkerPolygon(startMarkerShape, segmentAt(0), MARKERS_SIZE));
        }

        if (endMarker != nullptr) {
            endMarker->setPolygon(GeometryUtils::makeMarkerPolygon(endMarkerShape, segmentAt(nVertices - 2, true), MARKERS_SIZE));
        }
    }
}

QPointF DiagramConnection::commentBadgePos() {
    return path().pointAtPercent(0.8);
}

QPointF DiagramConnection::closestConnectionMappedPoint(const QPointF &mappedPoint) const {
    const QPainterPath myPath = path();
    if (myPath.isEmpty()) {
        return mappedPoint;
    }

    QPointF closestPoint = myPath.elementAt(0);
    for (int i = 0; i < myPath.elementCount() - 1; i++) {
        const QLineF segment = segmentAt(i);
        const QPointF segmentPoint = GeometryUtils::closestPointOnSegment(segment.p1(), segment.p2(), mappedPoint);
        if (QLineF(segmentPoint, mappedPoint).length() < QLineF(closestPoint, mappedPoint).length()) {
            closestPoint = segmentPoint;
        }
    }

    return closestPoint;
}
