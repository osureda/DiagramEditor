/**
 * @file diagramtype.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of DiagramType class.
 * @date Monday, July 20, 2026
 */
#include "diagramtype.h"

#include <QVariant>

void DiagramType::loadFromHash(const QVariantHash &hash) {
    const QVariantHash itemsData = hash["items"].toHash();

    for (auto it = itemsData.cbegin(); it != itemsData.cend(); ++it) {
        storedDiagramItems[it.key()] = it.value().toStringList();
    }
}

DiagramType::DiagramItemsIds DiagramType::diagramItems() const {
    return storedDiagramItems;
}
