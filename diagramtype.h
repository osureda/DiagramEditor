/**
 * @file diagramtype.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of DiagramType class.
 * @date Monday, July 20, 2026
 */
#ifndef DIAGRAMTYPE_H
#define DIAGRAMTYPE_H

#include "jsonserializable.h"

#include <QHash>
#include <QString>
#include <QStringList>

QT_BEGIN_NAMESPACE
class QVariant;
QT_END_NAMESPACE

/**
 * @class DiagramType
 * @brief Represents a diagram type and the identifiers of its associated items.
 */
class DiagramType : public JsonSerializable
{
    public:
        /**
         * @typedef DiagramItemsIds
         * @brief Hash that stores the associated item IDs for each diagram item
         *        type.
         */
        typedef QHash<QString, QStringList> DiagramItemsIds;

        /**
         * @param hash The hash containing the data to load.
         * @pre True.
         * @post The diagram type data has been loaded using the data from the
         *       given hash.
         */
        void loadFromHash(const QVariantHash &hash) override;

        /**
         * @return The IDs of the items associated with the diagram type.
         * @pre True.
         * @post The IDs of the items associated with the diagram type have been
         *       returned.
         */
        DiagramItemsIds diagramItems() const;

    private:
        DiagramItemsIds storedDiagramItems; ///< IDs of the items associated with the diagram type
};

#endif // DIAGRAMTYPE_H
