/**
 * @file selectablespecification.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of SelectableSpecification class.
 * @date Monday, July 20, 2026
 */
#ifndef SELECTABLESPECIFICATION_H
#define SELECTABLESPECIFICATION_H

#include "diagramspecification.h"

#include <QStringList>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
class QWidget;
QT_END_NAMESPACE

/**
 * @class SelectableSpecification
 * @brief A diagram specification whose text can be chosen from selectable choices.
 */
class SelectableSpecification : public DiagramSpecification
{
    public:
        /**
         * @param parent The container of the specification.
         * @pre True.
         * @post The specification is contained by parent.
         */
        explicit SelectableSpecification(QGraphicsItem *parent = nullptr);

        /**
         * @param hash The hash containing the data to load.
         * @pre True.
         * @post The specification data has been loaded using the data from the
         *       given hash.
         */
        void loadFromHash(const QVariantHash &hash) override;

        /**
         * @return The data associated with the specification.
         * @pre True.
         * @post The data associated with the specification has been returned.
         */
        QVariantHash toHash() const override;

        /**
         * @return The form to modify the specification text.
         * @pre True.
         * @post The form to modify the specification text has been returned.
         */
        QWidget *form() const override;

    private:
        QStringList choices; ///< The choices for the specification text

        /**
         * @param variant The variant containing the specification text data.
         * @pre True.
         * @post The specification text has been loaded from variant.
         */
        void loadTextFromVariant(const QVariant &variant) override;

        /**
         * @return The variant containing the specification text data.
         * @pre True.
         * @post The variant containing the specification text data has been
         *       returned.
         */
        QVariant variantFromText() const override;

        /**
         * @param fromResults The form containing the results to apply.
         * @pre True.
         * @post The specification text has been updated from the form results
         *       formResults.
         */
        void updateTextFromForm(const QWidget *fromResults) override;
};

#endif // SELECTABLESPECIFICATION_H
