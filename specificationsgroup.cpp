/**
 * @file specificationsgroup.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of SpecificationsGroup class.
 * @date Monday, July 20, 2026
 */
#include "specificationsgroup.h"

#include "diagramcomponent.h"
#include "diagramspecification.h"
#include "listspecification.h"
#include "longtextspecification.h"
#include "selectablespecification.h"
#include "shorttextspecification.h"
#include "specificationsform.h"

#include <QDebug>

namespace DiagramEditor::Specification {

SpecificationsGroup::SpecificationsGroup(DiagramComponent *parent)
    : diagramComponent(parent)
{}

SpecificationsGroup::~SpecificationsGroup() {
    for (auto it = specifications.begin(); it != specifications.end(); ++it) {
        delete *it;
    }
}

void SpecificationsGroup::loadFromHash(const QVariantHash &hash) {
    clear();

    for (auto it = hash.cbegin(); it != hash.cend(); ++it) {
        QVariantHash specificationData = it.value().toHash();

        int order = specificationData["order"].toInt();
        if (specifications.size() <= order) {
            specificationsIds.resize(order + 1);
            specifications.resize(order + 1);
        }

        specificationsIds[order] = it.key();

        DiagramSpecification *specification = specificationFromTypeName(specificationData["type"].toString());
        specification->loadFromHash(specificationData["textData"].toHash());
        specifications[order] = specification;
    }
}

QVariantHash SpecificationsGroup::toHash() const {
    QVariantHash hash;

    for (int i = 0; i < specifications.size(); i++) {
        QVariantHash specificationData;

        specificationData["order"] = i;
        specificationData["type"] = typeNameFromSpecification(specifications[i]);
        specificationData["textData"] = specifications[i]->toHash();

        hash[specificationsIds[i]] = specificationData;
    }

    return hash;
}

SpecificationsForm *SpecificationsGroup::form() const {
    SpecificationsForm *form = new SpecificationsForm();

    for (auto it = specifications.begin(); it != specifications.end(); ++it) {
        form->appendField((*it)->name(), (*it)->form());
    }

    return form;
}

void SpecificationsGroup::applyFormResults(const SpecificationsForm *formResults, int formIndex) {
    for (auto it = specifications.begin(); it != specifications.end(); ++it) {
        (*it)->applyFormResults(formResults->fieldResults(formIndex, (*it)->name()));
    }
}

void SpecificationsGroup::clear() {
    specificationsIds.clear();

    for (auto it = specifications.begin(); it != specifications.end(); ++it) {
        delete *it;
    }
    specifications.clear();
}

DiagramSpecification *SpecificationsGroup::specificationFromTypeName(const QString &typeName) {
    if (typeName == "longText") {
        return new LongTextSpecification();
    } else if (typeName == "choice") {
        return new SelectableSpecification();
    } else if (typeName == "list") {
        return new ListSpecification();
    } else if (typeName != "shortText") {
        qCritical() << "Unrecognized specification type: " << typeName;
    }
    return new ShortTextSpecification();
}

QString SpecificationsGroup::typeNameFromSpecification(const DiagramSpecification *specification) {
    if (dynamic_cast<const LongTextSpecification*>(specification)) {
        return "longText";
    } else if (dynamic_cast<const SelectableSpecification*>(specification)) {
        return "choice";
    } else if (dynamic_cast<const ListSpecification*>(specification)) {
        return "list";
    } else {
        return "shortText";
    }
}

}
