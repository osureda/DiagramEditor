/**
 * @file specificationsgroup.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of SpecificationsGroup class.
 * @date Monday, July 20, 2026
 */
#ifndef SPECIFICATIONSGROUP_H
#define SPECIFICATIONSGROUP_H

#include "jsonserializable.h"

#include <QString>
#include <QVariant>
#include <QVector>

class DiagramComponent;
class DiagramSpecification;
class SpecificationsForm;

/**
 * @class SpecificationsGroup
 * @brief A group of diagram specifications belonging to a diagram component.
 */
class SpecificationsGroup : public JsonSerializable
{
    public:
        /**
         * @param parent The diagram component to which the specifications belong.
         * @pre True.
         * @post The specifications group belongs to parent.
         */
        explicit SpecificationsGroup(DiagramComponent *parent);

        /**
         * @pre True.
         * @post The specifications have been deleted.
         */
        ~SpecificationsGroup() override;

        /**
         * @param hash The hash containing the data to load.
         * @pre True.
         * @post The specifications group has been loaded using the data from the
         *       given hash.
         */
        virtual void loadFromHash(const QVariantHash &hash);

        /**
         * @return The hash containing the specifications data.
         * @pre True.
         * @post The hash containing the specifications data has been returned.
         */
        virtual QVariantHash toHash() const;

        /**
         * @return The form to modify the specifications.
         * @pre True.
         * @post The form to modify the specifications has been returned.
         */
        SpecificationsForm *form() const;

        /**
         * @param formResults The specifications form containing the results to
         *        apply.
         * @param formIndex The index of the component form in formResults.
         * @pre True.
         * @post The results in the specifications form with index formIndex in
         *       formResults have been applied to the specifications.
         */
        virtual void applyFormResults(const SpecificationsForm *formResults, int formIndex);

    protected:
        /**
         * @invariant specificationsIds.size() >= specifications.size().
         * @invariant specifications[i] != nullptr.
         */
        DiagramComponent *diagramComponent; ///< The diagram component to which the specifications belong

        QVector<QString> specificationsIds; ///< The IDs of the specifications
        QVector<DiagramSpecification*> specifications; ///< The group specifications

        /**
         * @pre True.
         * @post The specifications group is empty.
         */
        virtual void clear();

        /**
         * @return A specification of the type.
         * @param typeName The name of the type of the specification we want to
         *        obtain.
         * @pre True.
         * @post A specification of type named typeName has been returned.
         */
        static DiagramSpecification *specificationFromTypeName(const QString &typeName);

        /**
         * @return The type name of the specification.
         * @param specification The specification whose type name we want to
         *        obtain.
         * @pre True.
         * @post The type name of the given specification has been returned.
         */
        static QString typeNameFromSpecification(const DiagramSpecification *specification);
};

#endif // SPECIFICATIONSGROUP_H
