/**
 * @file longtextspecification.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of LongTextSpecification class.
 * @date Monday, July 20, 2026
 */
#ifndef LONGTEXTSPECIFICATION_H
#define LONGTEXTSPECIFICATION_H

#include "diagramspecification.h"

#include <QVariant>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
class QWidget;
QT_END_NAMESPACE

namespace DiagramEditor::Specification {

/**
 * @class LongTextSpecification
 * @brief A diagram specification with a long text.
 */
class LongTextSpecification : public DiagramSpecification
{
    public:
        /**
         * @param parent The container of the specification.
         * @pre True.
         * @post The specification is contained by parent.
         */
        explicit LongTextSpecification(QGraphicsItem *parent = nullptr);

        /**
         * @return The form to modify the specification text.
         * @pre True.
         * @post The form to modify the specification text has been returned.
         */
        QWidget *form() const override;

    private:
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

}

#endif // LONGTEXTSPECIFICATION_H
