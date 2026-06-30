/**
 * @file diagramelement.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of DiagramElement class.
 * @date Monday, July 20, 2026
 */
#ifndef DIAGRAMELEMENT_H
#define DIAGRAMELEMENT_H

#include "diagramcomponent.h"
#include "elementspecifications.h"
#include "geometryutils.h"
#include "diagramresizer.h"

#include <QColor>
#include <QGraphicsPolygonItem>
#include <QObject>
#include <QPointF>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

namespace DiagramEditor::Specification {
class ElementSpecifications;
class SpecificationsForm;
}

namespace DiagramEditor::Diagram {

class DiagramItem;
using DiagramEditor::Specification::ElementSpecifications;
using DiagramEditor::Specification::SpecificationsForm;
namespace GeometryUtils = DiagramEditor::GeometryUtils;

/**
 * @class DiagramElement
 * @brief A diagram component represented as a polygon.
 */
class DiagramElement : public DiagramComponent, public QGraphicsPolygonItem
{
    Q_OBJECT

    public:
        /// The color of the outline of the element polygon.
        static const QColor OUTLINE_COLOR;

        /// The width of the outline of the element polygon.
        static const int OUTLINE_WIDTH = 2;

        /**
         * @param parent The diagram item to which the element belongs.
         * @pre True.
         * @post The element belongs to diagram item parent.
         */
        explicit DiagramElement(DiagramItem *parent);

        /**
         * @pre True.
         * @post The element has been deleted.
         */
        ~DiagramElement() override;

        /**
         * @param hash The hash containing the data to load.
         * @pre True.
         * @post The element has been loaded using the data from the given hash.
         */
        void loadFromHash(const QVariantHash &hash) override;

        /**
         * @return The hash containing the elements's data.
         * @pre True.
         * @post The hash containing the elements's data has been returned.
         */
        QVariantHash toHash() const override;

        /**
         * @return The specifications form of the element.
         * @pre True.
         * @post The specifications form of the element has been returned.
         */
        SpecificationsForm *specificationsForm() const override;

        /**
         * @param formResults The specifications form containing the results to
         *        apply.
         * @param formIndex The index of the component form in formResults.
         * @pre True.
         * @post The results in the specifications form with index formIndex in
         *       formResults have been applied to the element.
         */
        void setSpecifications(const SpecificationsForm *formResults, int formIndex) override;

        /**
         * @param shadowed Whether we want to shadow the element or not.
         * @pre True.
         * @post If shadowed is true, the element is shadowed;
         *       otherwise, it's not shadowed.
         */
        void setShadow(bool shadowed) override;

        /**
         * @param visible Whether we want to set the element resizer visible.
         * @pre True.
         * @post If visible is true, the element resizer is visible;
         *       otherwise, the element resizer is not visible.
         */
        void setResizersVisibility(bool visible) override;

        /**
         * @return true if the element can be resized to the position;
         *         false otherwise.
         * @param pos The position we want to know if the element can be resized to.
         * @pre specifications != nullptr.
         * @post If the function returns true, the element can be resized to the
         *       position pos;
         *       otherwise, the element can't be resized to the position pos.
         */
        bool canResizeTo(const QPointF &pos) const override;

        /**
         * @pre specifications != nullptr.
         * @post The element has been resized to its resizer position.
         */
        void resize() override;

    private slots:
        /**
         * @pre The element specifications group size has been changed.
         * @post If the element specifications group size is greater than the element
         *       size, the element has been resized to it.
         */
        void specificationsSizeChanged();

    private:
        GeometryUtils::PolygonShape externalShape; ///< The shape type of the element polygon
        QColor brushColor; ///< The default fill color of the element polygon
        GeometryUtils::Stroke stroke; ///< The stroke type of the element polygon outline
        QPointF size; ///< The size of the element polygon

        QGraphicsPolygonItem *internalElement; ///< The internal polygon of the element
        GeometryUtils::PolygonShape internalShape; ///< The shape type of the internal polygon of the element
        qreal innerShapePadding; ///< The distance between the element polygon and the internal polygon of the element

        DiagramResizer *resizer; ///< The resizer of the element
        ElementSpecifications *specifications; ///< The specifications of the element

        /**
         * @param colorName The name of the fill color we want to apply to the
         *        element polygon.
         * @pre True.
         * @post The fill color of the element polygon is named colorName.
         */
        void loadBrushColor(const QString &colorName);

        /**
         * @pre True.
         * @post The polygon of the element has been loaded.
         */
        void loadExternalShape();

        /**
         * @pre True.
         * @post The internal polygon of the element has been loaded.
         */
        void loadInternalShape();

        /**
         * @pre True.
         * @post The element's resizer has been loaded.
         */
        void addResizer();

        /**
         * @return The active element comment badge position.
         * @pre True.
         * @post The active element comment badge position has been returned.
         */
        QPointF commentBadgePos() override;

        /**
         * @return The closest point of the element outline to the position.
         * @param mappedPoint The position we want to obtain its closest element
         *        outline point.
         * @pre True.
         * @post The closest point of the element outline to mappedPoint has
         *       been returned.
         */
        QPointF closestConnectionMappedPoint(const QPointF &mappedPoint) const override;
};

}

#endif // DIAGRAMELEMENT_H
