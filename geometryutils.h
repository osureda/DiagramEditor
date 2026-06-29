/**
 * @file geometryutils.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of GeometryUtils namespace.
 * @date Monday, July 20, 2026
 */
#pragma once

#include <QPen>
#include <QPointF>
#include <QPolygonF>
#include <QString>
#include <QVector>

QT_BEGIN_NAMESPACE
class QColor;
class QLineF;
QT_END_NAMESPACE

/**
 * @namespace GeometryUtils
 * @brief Contains helper functions and constants for geometry.
 */
namespace GeometryUtils
{
    /// The value of PI.
    const qreal PI = 3.1416;

    /// The number of points used to draw a circle.
    const int N_CIRCLE_POINTS = 100;

    /// The angle used to draw an arrow head.
    const qreal ARROW_HEAD_ANGLE = 0.5;

    /**
     * @enum Stroke
     * @brief The types of line strokes.
     */
    enum class Stroke {
        Solid,  ///< The stroke is solid.
        Dashed  ///< The stroke is dashed.
    };

    /**
     * @enum PolygonShape
     * @brief The types of polygon shapes.
     */
    enum class PolygonShape {
        Square,     ///< The polygon is a square.
        Circle,     ///< The polygon is a circle.
        Diamond,    ///< The polygon is a diamond.
        Paper,      ///< The polygon has a paper shape.
        None        ///< There is no polygon.
    };

    /**
     * @enum LineMarker
     * @brief The types of line markers.
     */
    enum class LineMarker {
        OpenedArrow,    ///< The marker is an opened arrow.
        ClosedArrow,    ///< The marker is a closed arrow.
        None            ///< There is no marker.
    };

    /**
     * @return The stroke associated with the given string.
     * @param string The string whose associated stroke we want to obtain.
     * @pre True.
     * @post The stroke associated with the given string has been returned.
     */
    Stroke strokeFromString(const QString &string);

    /**
     * @return The polygon shape associated with the given string.
     * @param string The string whose associated polygon shape we want to obtain.
     * @pre True.
     * @post The polygon shape associated with the given string has been returned.
     */
    PolygonShape shapeFromString(const QString &string);

    /**
     * @return The line marker associated with the given string.
     * @param string The string whose associated line marker we want to obtain.
     * @pre True.
     * @post The line marker associated with the given string has been returned.
     */
    LineMarker markerFromString(const QString &string);

    /**
     * @return The name of the given stroke.
     * @param stroke The stroke whose name we want to obtain.
     * @pre True.
     * @post The name of the given stroke has been returned.
     */
    QString strokeName(const Stroke &stroke);

    /**
     * @return The name of the given polygon shape.
     * @param shape The polygon shape whose name we want to obtain.
     * @pre True.
     * @post The name of the given polygon shape has been returned.
     */
    QString shapeName(const PolygonShape &shape);

    /**
     * @return The name of the given line marker.
     * @param marker The line marker whose name we want to obtain.
     * @pre True.
     * @post The name of the given line marker has been returned.
     */
    QString markerName(const LineMarker &marker);

    /**
     * @return A pen with the given properties.
     * @param color The color of the pen we want to obtain.
     * @param width The width of the pen we want to obtain.
     * @param style The stroke type of the pen we want to obtain.
     * @pre width >= 0.
     * @post A pen with the given color and width and stroke style has been
     *       returned.
     */
    QPen makePen(const QColor &color, qreal width, const Stroke &style);

    /**
     * @return A polygon with the given properties.
     * @param shape The shape of the polygon we want to obtain.
     * @param size The size of the polygon we want to obtain.
     * @pre size.x() >= 0 && size.y() >= 0.
     * @post A polygon with the given shape and size has been returned.
     */
    QPolygonF makePolygon(const PolygonShape &shape, const QPointF &size);

    /**
     * @return A unit square polygon.
     * @pre True.
     * @post A unit square polygon has been returned.
     */
    QPolygonF unitarySquare();

    /**
     * @return A unit circle polygon.
     * @pre True.
     * @post A unit circle polygon has been returned.
     */
    QPolygonF unitaryCircle();

    /**
     * @return A unit diamond polygon.
     * @pre True.
     * @post A unit diamond polygon has been returned.
     */
    QPolygonF unitaryDiamond();

    /**
     * @return A unit polygon with a paper shape.
     * @pre True.
     * @post A unit polygon with a paper shape has been returned.
     */
    QPolygonF unitaryPaper();

    /**
     * @return A line marker with the given properties.
     * @param markerShape The shape of the line marker we want to obtain.
     * @param line The line whose marker we want to obtain.
     * @param size The size of the line marker we want to obtain.
     * @pre size.x() >= 0 && size.y() >= 0.
     * @post A line marker with shape markerShape, the given size and for the given
     *       line has been returned.
     */
    QPolygonF makeMarkerPolygon(const LineMarker &markerShape, const QLineF &line, const QPointF &size);

    /**
     * @return An opened arrow head for a tail.
     * @param tail The arrow tail whose head we want to obtain.
     * @param headSize The size of the arrow head we want to obtain.
     * @pre headSize.x() >= 0 && headSize.y() >= 0.
     * @post An opened arrow head with size headSize for the given tail has been
     *       returned.
     */
    QPolygonF openedArrowHead(const QLineF &tail, const QPointF &headSize);

    /**
     * @return A closed arrow head for a tail.
     * @param tail The arrow tail whose head we want to obtain.
     * @param headSize The size of the arrow head we want to obtain.
     * @pre headSize.x() >= 0 && headSize.y() >= 0.
     * @post A closed arrow head with size headSize for the given tail has been
     *       returned.
     */
    QPolygonF closedArrowHead(const QLineF &tail, const QPointF &headSize);

    /**
     * @return The vertices of the arrow head for a tail.
     * @param tail The arrow tail whose head vertices we want to obtain.
     * @param headSize The size of the arrow head whose vertices we want to obtain.
     * @pre headSize.x() >= 0 && headSize.y() >= 0.
     * @post The vertices of the arrow head with size headSize for the given tail
     *       have been returned.
     */
    QVector<QPointF> arrowHeadVertices(const QLineF &tail, const QPointF &headSize);

    /**
     * @return The closest point to a point in a segment.
     * @param a The first endpoint of the segment.
     * @param b The second endpoint of the segment.
     * @param p The point whose closest point on the segment we want to obtain.
     * @pre True.
     * @post The closest point to p on the segment between a and b.
     */
    QPointF closestPointOnSegment(const QPointF &a, const QPointF &b, const QPointF &p);
}
