/**
 * @file jsonfile.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of JsonFile class.
 * @date Monday, July 20, 2026
 */
#include "jsonfile.h"

#include <QByteArray>
#include <QDebug>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>

JsonFile::JsonFile(const QString &fileName)
    : QFile(fileName)
{}

bool JsonFile::load() {
    if (!open(QIODevice::ReadOnly)) {
        qCritical() << "Error opening JSON file";
        return false;
    }

    bool success = parseToJsonObject(readAll(), contents);

    close();

    return success;
}

QVariantHash JsonFile::hashForKey(const QString &key) const {
    if (!contents.contains(key)) {
        qCritical() << "Non-existent key in JSON object: " << key;
        return {};
    }

    const QJsonValue &value = contents[key];
    if (!value.isObject()) {
        qCritical() << "Value for key " << key << " is not a JSON object";
        return {};
    }

    return value.toObject().toVariantHash();
}

QVariantHash JsonFile::textToHash(const QString &text) {
    QJsonObject jsonObject;

    return parseToJsonObject(text.toUtf8(), jsonObject)
        ? jsonObject.toVariantHash()
        : QVariantHash{};
}

QString JsonFile::hashToText(const QVariantHash &hash) {
    QJsonDocument document(QJsonObject::fromVariantHash(hash));

    return QString::fromUtf8(document.toJson(QJsonDocument::Indented));
}

bool JsonFile::parseToJsonObject(const QByteArray &json, QJsonObject &jsonObject) {
    bool success = false;

    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(json, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qCritical() << "Error parsing JSON file: " << parseError.errorString();
    } else if (!document.isObject()) {
        qCritical() << "JSON root is not an object";
    } else {
        success = true;
    }

    jsonObject = document.object();
    return success;
}
