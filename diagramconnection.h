/**
 * @file diagramconnection.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of DiagramConnection class.
 * @date Monday, July 20, 2026
 */
#ifndef DIAGRAMCONNECTION_H
#define DIAGRAMCONNECTION_H

#include "diagramcomponent.h"
#include "geometryutils.h"

#include <QColor>
#include <QGraphicsPathItem>
#include <QLineF>
#include <QList>
#include <QPointF>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QString;
QT_END_NAMESPACE

namespace DiagramEditor::Specification {
class ConnectionSpecifications;
class SpecificationsForm;
}

namespace DiagramEditor::Diagram {

class ConnectableResizer;
class DiagramItem;
using DiagramEditor::Specification::ConnectionSpecifications;
using DiagramEditor::Specification::SpecificationsForm;
namespace GeometryUtils = DiagramEditor::GeometryUtils;

/**
 * @class DiagramConnection
 * @brief A diagram component represented by a path that connects other components.
 */
class DiagramConnection : public QGraphicsPathItem, public DiagramComponent
{
    public:
        /// The color of the connection path.
        static const QColor DEFAULT_COLOR;

        /// The width of the connection path.
        static const int LINE_WIDTH = 3;

        /// The size of the path endpoint markers.
        static const QPointF MARKERS_SIZE;

        /// The fill color of the path endpoint markers.
        static const QColor MARKERS_BRUSH_COLOR;

        /// The margin of the area where the connection can be clicked regarding its path.
        static const int CLICK_MARGIN = 2;

        /**
         * @param parent The diagram item to which the connection belongs.
         * @pre True.
         * @post The connection belongs to diagram item parent.
         */
        explicit DiagramConnection(DiagramItem *parent);

        /**
         * @pre True.
         * @post The connection has been deleted.
         */
        ~DiagramConnection() override;

        /**
         * @return The z-value that has to be assigned to the connection.
         * @pre True.
         * @post The z-value that has to be assigned to the connection has
         *       been returned.
         */
        int definedZValue() const override;

        /**
         * @pre True.
         * @post The connection is connecting its corresponding components.
         */
        void connectComponent() override;

        /**
         * @param hash The hash containing the data to load.
         * @pre True.
         * @post The connection has been loaded using the data from the given hash.
         */
        void loadFromHash(const QVariantHash &hash) override;

        /**
         * @return The hash containing the connection's data.
         * @pre True.
         * @post The hash containing the connection's data has been returned.
         */
        QVariantHash toHash() const override;

        /**
         * @return The specifications form of the connection.
         * @pre True.
         * @post The specifications form of the connection has been returned.
         */
        SpecificationsForm *specificationsForm() const override;

        /**
         * @param formResults The specifications form containing the results to
         *        apply.
         * @param formIndex The index of the component form in formResults.
         * @pre True.
         * @post The results in the specifications form with index formIndex in
         *       formResults have been applied to the connection.
         */
        void setSpecifications(const SpecificationsForm *formResults, int formIndex) override;

        /**
         * @param shadowed Whether we want to shadow the connection or not.
         * @pre True.
         * @post If shadowed is true, the connection is shadowed;
         *       otherwise, it's not shadowed.
         */
        void setShadow(bool shadowed) override;

        /**
         * @param visible Whether we want to set the connection resizers visible.
         * @pre True.
         * @post If visible is true, the connection resizers are visible;
         *       otherwise, the connection resizers are not visible.
         */
        void setResizersVisibility(bool visible) override;

        /**
         * @return true if a resizer has been added to the position;
         *         false otherwise.
         * @param scenePos The scene position of the resizer we want to add.
         * @pre True.
         * @post If the function returns true, a resizer has been added to the scene
         *       position scenePos;
         *       otherwise, a resizer can't be added to the scene position scenePos.
         */
        bool addResizer(const QPointF &scenePos) override;

        /**
         * @return true if a resizer has been removed from the position;
         *         false otherwise.
         * @param scenePos The scene position of the resizer we want to remove.
         * @pre True.
         * @post If the function returns true, a resizer has been removed from the
         *       scene position scenePos;
         *       otherwise, a resizer can't be removed from the scene position
         *       sscenePos.
         */
        bool removeResizer(const QPointF &scenePos) override;

        /**
         * @pre specifications != nullptr.
         * @post The connection has been resized to its resizer position.
         */
        void resize() override;

    private:
        /**
         * @invariant resizers[0..resizers.size()-1].
         */
        QColor penColor; ///< The default color of the path pen
        GeometryUtils::Stroke stroke; ///< The stroke type of the path

        QGraphicsPolygonItem *startMarker; ///< The path starting marker
        QGraphicsPolygonItem *endMarker; ///< The path ending marker
        GeometryUtils::LineMarker startMarkerShape; ///< The path starting marker type
        GeometryUtils::LineMarker endMarkerShape; ///< The path ending marker type

        QList<ConnectableResizer*> resizers; ///< The resizers of the connection
        ConnectionSpecifications *specifications; ///< The specifications of the connection

        /**
         * @return The connection path pen color named string.
         * @param string The name of the color we want to obtain.
         * @pre True.
         * @post The connection path pen color named string or the connection path pen
         *       default color has been returned.
         */
        static QColor penColorFromString(const QString &string);

        /**
         * @return The connection path segment at the order pos.
         * @param pos The order of the connection path segment we want to obtain.
         * @param reverted Whether we want to obtain the segment reverted or not.
         * @pre 0 <= pos < path().elementCount().
         * @post The connection path segment at the order pos has been returned
         *       and reverted if required.
         */
        QLineF segmentAt(int pos, bool reverted = false) const;

        /**
         * @return The index of a new resizer at the position.
         * @param pos The position of the new resizer its index we want to obtain.
         * @pre True.
         * @post The index of a new resizer at the position pos has been returned.
         */
        int newResizerIndex(const QPointF &pos) const;

        /**
         * @param resizer The resizer we want to store in the resizers list.
         * @param index The index of the resizer we want to store.
         * @pre index >= -1.
         * @post The given resizer has been stored in the resizers list at
         *       the given index.
         */
        void storeResizer(ConnectableResizer *resizer, int index = -1);

        /**
         * @pre True.
         * @post The connection path endpoint markers have been loaded.
         */
        void loadMarkers();

        /**
         * @return An endpoint marker of the connection path.
         * @pre True.
         * @post An endpoint marker of the connection path has been returned.
         */
        QGraphicsPolygonItem *makeMarker();

        /**
         * @pre True.
         * @post The connection path endpoint markers position and
         *       orientation have been updated.
         */
        void updateMarkersPolygon();

        /**
         * @return The position of the comment badge at the connection.
         * @pre True.
         * @post The position of the comment badge at the connection has been
         *       returned.
         */
        QPointF commentBadgePos() override;

        /**
         * @return The closest point of the connection path to the position.
         * @param mappedPoint The position we want to obtain its closest
         *        connection path point.
         * @pre True.
         * @post The closest point of the connection path to mappedPoint has
         *       been returned.
         */
        QPointF closestConnectionMappedPoint(const QPointF &mappedPoint) const override;
};

}

#endif // DIAGRAMCONNECTION_H
