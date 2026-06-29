/**
 * @file elementspecifications.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of ElementSpecifications class.
 * @date Monday, July 20, 2026
 */
#ifndef ELEMENTSPECIFICATIONS_H
#define ELEMENTSPECIFICATIONS_H

#include "specificationsgroup.h"

#include <QColor>
#include <QList>
#include <QObject>
#include <QPointF>
#include <QString>
#include <QVariant>
#include <QVector>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
QT_END_NAMESPACE

namespace DiagramEditor::Diagram {
class DiagramElement;
}

namespace DiagramEditor::Specification {

class SpecificationsForm;
using DiagramEditor::Diagram::DiagramElement;

/**
 * @class ElementSpecifications
 * @brief The specifications of a diagram element.
 */
class ElementSpecifications : public QObject, public SpecificationsGroup
{
    Q_OBJECT

    public:
        /// The internal margin of the diagram element.
        static const int MARGINS = 1;

        /// The color of a specification separator.
        static const QColor SEPARATOR_PATH_COLOR;

        /// The width of a specification separator.
        static const int SEPARATOR_PATH_WIDTH = 2;

        /**
         * @enum SpecificationPos
         * @brief The types of specification positions.
         */
        enum class SpecificationPos {
            TopLeft,            ///< A top left position.
            Center,             ///< A centered position.
            Vertical,           ///< A top center position below the previous vertial specifications.
            VerticalSeparated   ///< A top center position with a separator below the previous vertial specifications.
        };


        /**
         * @param parent The diagram element to which the specifications belong.
         * @pre True.
         * @post The specifications group belongs to parent.
         */
        explicit ElementSpecifications(DiagramElement *parent);

        /**
         * @param hash The hash containing the data to load.
         * @pre The specifications diagram component belongs to a scene.
         * @post The specifications group has been loaded using the data from the
         *       given hash.
         */
        void loadFromHash(const QVariantHash &hash) override;

        /**
         * @return The hash containing the specifications data.
         * @pre True.
         * @post The hash containing the specifications data has been returned.
         */
        QVariantHash toHash() const override;

        /**
         * @param formResults The specifications form containing the results to
         *        apply.
         * @param formIndex The index of the component form in formResults.
         * @pre True.
         * @post The results in the specifications form with index formIndex in
         *       formResults have been applied to the specifications.
         */
        void applyFormResults(const SpecificationsForm *formResults, int formIndex) override;

        /**
         * @pre True.
         * @post The specification positions have been updated.
         */
        void updateSpecificationsPos();

        /**
         * @return The size of the specifications group.
         * @pre True.
         * @post The size of the specifications group has been returned.
         */
        QPointF size() const;

    signals:
        /**
         * @param sizeChange The difference between the old and the new size.
         * @pre The specifications group size has changed.
         * @post The signal has been emited with the difference between the old
         *       and the new size.
         */
        void sizeChanged(const QPointF &sizeChange);

    private:
        /**
         * @invariant specificationsPositions.size() >= specifications.size().
         */
        QVector<SpecificationPos> specificationsPositions; ///< The positions of the specifications

        QList<QGraphicsItem*> specificationsDecorations; ///< The specifications group decoration items
        qreal verticalSpecificationsBottom; ///< The bottom of the vertical specifications set

        /**
         * @return The position of the specification with the index.
         * @param specificationIndex The index of the specification whose
         *        position we want to obtain.
         * @pre 0 <= specificationIndex < specificationsPositions.size().
         * @post The position of the specification with index specificationIndex has
         *       been returned.
         */
        QPointF specificationPosPoint(int specificationIndex) const;

        /**
         * @pre True.
         * @post The specifications group is empty.
         */
        void clear() override;

        /**
         * @pre True.
         * @post A vertical specification separator has been added to the vertical
         *       specifiactions bottom.
         */
        void addVerticalSeparator();

        /**
         * @pre True.
         * @post The specification group decorations have been deleted.
         */
        void clearDecorations();

        /**
         * @return The position type with the name.
         * @param string The name of the position type we want to obtain.
         * @pre True.
         * @post The position type named string has been returned.
         */
        static SpecificationPos posFromString(const QString &string);

        /**
         * @return The position type name.
         * @param pos The position type whose name we want to obtain.
         * @pre True.
         * @post The name of the position type pos has been returned.
         */
        static QString stringFromPos(const SpecificationPos &pos);
};

}

#endif // ELEMENTSPECIFICATIONS_H
