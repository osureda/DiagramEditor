/**
 * @file diagramtypegroup.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of DiagramTypeGroup class.
 * @date Monday, July 20, 2026
 */
#ifndef DIAGRAMTYPEGROUP_H
#define DIAGRAMTYPEGROUP_H

#include "jsonserializable.h"

#include <QStringList>

QT_BEGIN_NAMESPACE
class QVariant;
QT_END_NAMESPACE

/**
 * @class DiagramTypeGroup
 * @brief Represents a group of diagram types.
 */
class DiagramTypeGroup : public JsonSerializable
{
    public:
        /**
         * @param hash The hash containing the data to load.
         * @pre True.
         * @post The diagram type group data has been loaded using the data from
         *       the given hash.
         */
        void loadFromHash(const QVariantHash &hash) override;

        /**
         * @return The IDs of the diagram types in the group.
         * @pre True.
         * @post The IDs of the diagram types in the group have been returned.
         */
        QStringList diagramTypes() const;

    private:
        QStringList storedDiagramTypes; ///< IDs of the diagram types in the group
};

#endif // DIAGRAMTYPEGROUP_H
