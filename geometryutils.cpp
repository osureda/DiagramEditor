/**
 * @file geometryutils.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of GeometryUtils class.
 * @date Monday, July 20, 2026
 */
#include "geometryutils.h"

#include <cmath>
#include <QColor>
#include <QDebug>
#include <QLineF>
#include <QtGlobal>
#include <QTransform>

namespace DiagramEditor::GeometryUtils
{
    Stroke strokeFromString(const QString &string) {
        if (string == "dashed") {
            return Stroke::Dashed;
        }
        if (string != "solid") {
            qCritical() << "Unrecognized stroke type: " << string;
        }
        return Stroke::Solid;
    }

    PolygonShape shapeFromString(const QString &string) {
        if (string == "square") {
            return PolygonShape::Square;
        }
        if (string == "circle") {
            return PolygonShape::Circle;
        }
        if (string == "diamond") {
            return PolygonShape::Diamond;
        }
        if (string == "paper") {
            return PolygonShape::Paper;
        }
        if (string != "none") {
            qCritical() << "Unrecognized shape type: " << string;
        }
        return PolygonShape::None;
    }

    LineMarker markerFromString(const QString &string) {
        if (string == "openedArrow") {
            return LineMarker::OpenedArrow;
        }
        if (string == "closedArrow") {
            return LineMarker::ClosedArrow;
        }
        if (string != "none") {
            qCritical() << "Unrecognized line marker type: " << string;
        }
        return LineMarker::None;
    }

    QString strokeName(const Stroke &stroke) {
        switch (stroke) {
            case Stroke::Solid:
                return "solid";
            default:
                return "dashed";
        }
    }

    QString shapeName(const PolygonShape &shape) {
        switch (shape) {
            case PolygonShape::Square:
                return "square";
            case PolygonShape::Circle:
                return "circle";
            case PolygonShape::Diamond:
                return "diamond";
            case PolygonShape::Paper:
                return "paper";
            default:
                return "none";
        }
    }

    QString markerName(const LineMarker &marker) {
        switch (marker) {
            case LineMarker::OpenedArrow:
                return "openedArrow";
            case LineMarker::ClosedArrow:
                return "closedArrow";
            default:
                return "none";
        }
    }

    QPen makePen(const QColor &color, qreal width, const Stroke &style) {
        QPen pen(color, width);

        switch (style) {
            case Stroke::Solid:
                pen.setStyle(Qt::SolidLine);
                break;
            case Stroke::Dashed:
                pen.setStyle(Qt::DashLine);
                break;
        }

        return pen;
    }

    QPolygonF makePolygon(const PolygonShape &shape, const QPointF &size) {
        QPolygonF polygon;

        switch (shape) {
            case PolygonShape::Square:
                polygon = unitarySquare();
                break;
            case PolygonShape::Circle:
                polygon = unitaryCircle();
                break;
            case PolygonShape::Diamond:
                polygon = unitaryDiamond();
                break;
            case PolygonShape::Paper:
                polygon = unitaryPaper();
                break;
        }

        QTransform transform;
        transform.scale(size.x(), size.y());
        return transform.map(polygon);
    }

    QPolygonF unitarySquare() {
        return QPolygonF{
            QPointF(0, 0),
            QPointF(1, 0),
            QPointF(1, 1),
            QPointF(0, 1)
        };
    }

    QPolygonF unitaryCircle() {
        QPolygonF circle;

        for (int i = 0; i < N_CIRCLE_POINTS; i++) {
            const qreal angle = (2 * PI * i) / N_CIRCLE_POINTS;
            circle << QPointF(
                std::cos(angle) * 0.5 + 0.5,
                std::sin(angle) * 0.5 + 0.5
            );
        }

        return circle;
    }

    QPolygonF unitaryDiamond() {
        return QPolygonF{
            QPointF(0.5, 0),
            QPointF(1, 0.5),
            QPointF(0.5, 1),
            QPointF(0, 0.5)
        };
    }

    QPolygonF unitaryPaper() {
        return QPolygonF{
            QPointF(0, 0),
            QPointF(0.8, 0),
            QPointF(0.8, 0.2),
            QPointF(1, 0.2),
            QPointF(0.8, 0.2),
            QPointF(0.8, 0),
            QPointF(1, 0.2),
            QPointF(1, 1),
            QPointF(0, 1),
        };
    }

    QPolygonF makeMarkerPolygon(const LineMarker &markerShape, const QLineF &line, const QPointF &size) {
        switch (markerShape) {
            case LineMarker::OpenedArrow:
                return openedArrowHead(line, size);
            case LineMarker::ClosedArrow:
                return closedArrowHead(line, size);
            default:
                return QPolygonF();
        }
    }

    QPolygonF openedArrowHead(const QLineF &tail, const QPointF &headSize) {
        const QVector<QPointF> headVertices = arrowHeadVertices(tail, headSize);

        return QPolygonF{
            headVertices[0],
            headVertices[1],
            headVertices[2],
            headVertices[1]
        };
    }

    QPolygonF closedArrowHead(const QLineF &tail, const QPointF &headSize) {
        const QVector<QPointF> headVertices = arrowHeadVertices(tail, headSize);

        return QPolygonF{
            headVertices[0],
            headVertices[1],
            headVertices[2],
        };
    }

    QVector<QPointF> arrowHeadVertices(const QLineF &tail, const QPointF &headSize) {
        const QPointF tailBeginning = tail.p1();
        const QPointF tailEnd = tail.p2();

        const qreal orientation = std::atan2(tailEnd.y() - tailBeginning.y(), tailEnd.x() - tailBeginning.x());

        return {
            QPointF(
                tailBeginning.x() + std::cos(orientation + ARROW_HEAD_ANGLE) * headSize.x(),
                tailBeginning.y() + std::sin(orientation + ARROW_HEAD_ANGLE) * headSize.y()
            ),

            tailBeginning,

            QPointF(
                tailBeginning.x() + std::cos(orientation - ARROW_HEAD_ANGLE) * headSize.x(),
                tailBeginning.y() + std::sin(orientation - ARROW_HEAD_ANGLE) * headSize.y()
            ),
        };
    }

    QPointF closestPointOnSegment(const QPointF &a, const QPointF &b, const QPointF &p) {
        qreal dx = b.x() - a.x();
        qreal dy = b.y() - a.y();

        qreal length2 = dx * dx + dy * dy;
        if (length2 == 0) {
            return a;
        }

        qreal t = ((p.x() - a.x()) * dx + (p.y() - a.y()) * dy) / length2;
        return QLineF(a, b).pointAt(qBound(0.0, t, 1.0));
    }
}
