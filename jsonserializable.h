/**
 * @file jsonserializable.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of JsonSerializable class.
 * @date Monday, July 20, 2026
 */
#ifndef JSONSERIALIZABLE_H
#define JSONSERIALIZABLE_H

#include <QStringList>
#include <QVariant>

/**
 * @class JsonSerializable
 * @brief Base class for objects that can be loaded from and converted to a
 *        QVariantHash.
 */
class JsonSerializable
{
    public:
        /**
         * @param path The path of the JSON file.
         * @pre True.
         * @post The object has been destroyed.
         */
        virtual ~JsonSerializable();

        /**
         * @param hash The hash containing the data to load.
         * @pre True.
         * @post The object has been loaded using the data from the given hash.
         */
        virtual void loadFromHash(const QVariantHash &hash);

        /**
         * @return The hash containing the object's data.
         * @pre True.
         * @post The hash containing the object's data has been returned.
         */
        virtual QVariantHash toHash() const;

        /**
         * @return The hash containing the values of the keys.
         * @param hash The hash containing all the values.
         * @param keys The keys we want to keep.
         * @pre True.
         * @post The hash containing the values from the given hash for the given
         *       keys has been returned.
         */
        static QVariantHash filteredHashByKeys(const QVariantHash &hash, const QStringList &keys);
};

#endif // JSONSERIALIZABLE_H
