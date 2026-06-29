/**
 * @file jsonfile.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of JsonFile class.
 * @date Monday, July 20, 2026
 */
#ifndef JSONFILE_H
#define JSONFILE_H

#include <QFile>
#include <QJsonObject>
#include <QString>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QByteArray;
QT_END_NAMESPACE

/**
 * @class JsonFile
 * @brief Helper class for loading a JSON file and performing JSON conversions.
 */
class JsonFile : public QFile
{
    public:
        /**
         * @param path The path of the JSON file.
         * @pre True.
         * @post The JSON file has the given path.
         */
        explicit JsonFile(const QString &path);

        /**
         * @return true if the file was opened and loaded correctly;
         *         false otherwise.
         * @pre True.
         * @post If the function returns true, the JSON file has been opened and
         *       its contents have been loaded as a root JSON object.
         */
        bool load();

        /**
         * @return The hash associated with the key in the JSON root object.
         * @param key The key whose hash we want to retrieve.
         * @pre load() has returned true.

         *       been returned.
         */
        QVariantHash hashForKey(const QString &key) const;

        /**
         * @return The generated hash from the JSON text.
         * @param text The JSON text we want to transform.
         * @pre True.
         * @post The hash that can be generated from the given JSON text has been
         *       returned.
         */
        static QVariantHash textToHash(const QString &text);

        /**
         * @return The JSON text that represents the hash.
         * @param hash The hash we want to transform.
         * @pre True.
         * @post The text that represents the given hash has been returned.
         */
        static QString hashToText(const QVariantHash &hash);

    private:
        QJsonObject contents; ///< Root object of the JSON file

        /**
         * @return true if the JSON was parsed correctly to a JSON object;
         *         false otherwise.
         * @param json The JSON we want to parse.
         * @param jsonObject The JSON object where we want to store the parsed JSON.
         * @pre True.
         * @post If the function returns true, the given JSON has been parsed
         *       correctly to a JSON object stored in jsonObject.
         */
        static bool parseToJsonObject(const QByteArray &json, QJsonObject &jsonObject);
};

#endif // JSONFILE_H
