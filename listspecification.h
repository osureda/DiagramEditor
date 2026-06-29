/**
 * @file listspecification.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of ListSpecification class.
 * @date Monday, July 20, 2026
 */
#ifndef LISTSPECIFICATION_H
#define LISTSPECIFICATION_H

#include "diagramspecification.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

/**
 * @class ListSpecification
 * @brief  diagram specification whose text is displayed as a list..
 */
class ListSpecification : public DiagramSpecification
{
    Q_OBJECT

    public:
        /// The size of the specification form buttons.
        static const int FORM_BUTTONS_SIZE = 25;

        /**
         * @param parent The container of the specification.
         * @pre True.
         * @post The specification is contained by parent.
         */
        explicit ListSpecification(QGraphicsItem *parent = nullptr);

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
        QString bullet; ///< The bullet marker used for each list item
        QStringList list; ///< The specification text list

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

        /**
         * @param formLayout The specification form layout.
         * @pre True.
         * @post The specification form buttons have been added to formLayout.
         */
        void formButtons(QVBoxLayout *formLayout) const;
};

#endif // LISTSPECIFICATION_H
