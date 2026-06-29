/**
 * @file diagramtypegroup.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of DiagramTypeGroup class.
 * @date Monday, July 20, 2026
 */
#include "diagramtypegroup.h"

#include <QVariant>

namespace DiagramEditor::Gui {

void DiagramTypeGroup::loadFromHash(const QVariantHash &hash) {
    storedDiagramTypes = hash["diagrams"].toStringList();
}

QStringList DiagramTypeGroup::diagramTypes() const {
    return storedDiagramTypes;
}

}
