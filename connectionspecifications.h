/**
 * @file connectionspecifications.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of ConnectionSpecifications class.
 * @date Monday, July 20, 2026
 */
#ifndef CONNECTIONSPECIFICATIONS_H
#define CONNECTIONSPECIFICATIONS_H

#include "specificationsgroup.h"

#include <QPair>
#include <QPointF>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QVector>

namespace DiagramEditor::Diagram {
class DiagramConnection;
}

namespace DiagramEditor::Specification {

class SpecificationsForm;
using DiagramEditor::Diagram::DiagramConnection;

/**
 * @class ConnectionSpecifications
 * @brief The specifications of a diagram connection.
 */
class ConnectionSpecifications : public QObject, public SpecificationsGroup
{
    Q_OBJECT

    public:
        /// The margins of the endpoint specifications.
        static const int HORIZONTAL_SPACING = 3;

        /// The default vertical distance between the specifications and the connection.
        static const int VERTICAL_SPACING = 2;

        /**
         * @enum HorizontalPos
         * @brief The types of specification horizontal positions.
         */
        enum class HorizontalPos {
            Center,     ///< A centered horizontal position.
            Begin,      ///< A left endpoint horizontal position.
            End         ///< A right endpoint horizontal position.
        };

        /**
         * @enum VerticalPos
         * @brief The types of specification vertical positions.
         */
        enum class VerticalPos {
            Above,  ///< A vertical position above the connection.
            Below   ///< A vertical position below the connection.
        };

        /**
         * @param parent The diagram connection to which the specifications belong.
         * @pre True.
         * @post The specifications group belongs to parent.
         */
        explicit ConnectionSpecifications(DiagramConnection *parent);

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

    public slots:
        /**
         * @pre True.
         * @post The specification positions have been updated.
         */
        void updateSpecificationsPos();

    private:
        /**
         * @typedef SpecificationPos
         * @brief Pair that stores a group specification position.
         */
        typedef QPair<HorizontalPos, VerticalPos> SpecificationPos;

        /**
         * @invariant specificationsPositions.size() >= specifications.size().
         */
        QVector<SpecificationPos> specificationsPositions; ///< The positions of the specifications

        /**
         * @pre True.
         * @post The specifications group is empty.
         */
        void clear() override;

        /**
         * @return The horizontal position of the specification with the index.
         * @param specificationIndex The index of the specification whose
         *        horizontal position we want to obtain.
         * @pre 0 <= specificationIndex < specificationsPositions.size().
         * @post The horizontal position of the specification with index
         *       specificationIndex has been returned.
         */
        QPointF horizontalPosPoint(int specificationIndex) const;

        /**
         * @return The horizontal position type with the name.
         * @param string The name of the horizontal position type we want to obtain.
         * @pre True.
         * @post The horizontal position type named string has been returned.
         */
        static HorizontalPos horizontalPosFromString(const QString &string);

        /**
         * @return The vertical position type with the name.
         * @param string The name of the vertical position type we want to obtain.
         * @pre True.
         * @post The vertical position type named string has been returned.
         */
        static VerticalPos verticalPosFromString(const QString &string);

        /**
         * @return The horizontal position type name.
         * @param horizontalPos The horizontal position type whose name we want to
         *        obtain.
         * @pre True.
         * @post The name of the horizontal position type horizontalPos has been
         *       returned.
         */
        static QString stringFromHorizontalPos(const HorizontalPos &horizontalPos);

        /**
         * @return The vertical position type name.
         * @param verticalPos The vertical position type whose name we want to
         *        obtain.
         * @pre True.
         * @post The name of the vertical position type verticalPos has been
         *       returned.
         */
        static QString stringFromVerticalPos(const VerticalPos &verticalPos);
};

}

#endif // CONNECTIONSPECIFICATIONS_H
