/**
 * @file jsonserializable.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of JsonSerializable class.
 * @date Monday, July 20, 2026
 */
#include "jsonserializable.h"

#include <QString>

JsonSerializable::~JsonSerializable() {}

void JsonSerializable::loadFromHash(const QVariantHash &) {}

QVariantHash JsonSerializable::toHash() const {
    return {};
}

QVariantHash JsonSerializable::filteredHashByKeys(const QVariantHash &hash, const QStringList &keys) {
    QVariantHash filteredHash;

    for (const QString &key : keys) {
        filteredHash[key] = hash[key];
    }

    return filteredHash;
}
