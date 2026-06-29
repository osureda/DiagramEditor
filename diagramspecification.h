/**
 * @file diagramspecification.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of DiagramSpecification class.
 * @date Monday, July 20, 2026
 */
#ifndef DIAGRAMSPECIFICATION_H
#define DIAGRAMSPECIFICATION_H

#include "jsonserializable.h"

#include <QGraphicsTextItem>
#include <QList>
#include <QObject>
#include <QPointF>
#include <QString>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
class QWidget;
QT_END_NAMESPACE

namespace DiagramEditor::Specification {

/**
 * @class DiagramSpecification
 * @brief A diagram component specification.
 */
class DiagramSpecification : public QGraphicsTextItem, public DiagramEditor::Serialization::JsonSerializable
{
    Q_OBJECT

    public:
        /**
         * @param parent The container of the specification.
         * @pre True.
         * @post The specification is contained by parent.
         */
        explicit DiagramSpecification(QGraphicsItem *parent = nullptr);

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
         * @return The translation applied to the specification while moving it.
         * @pre True.
         * @post The translation applied to the specification while moving it has
         *       been returned.
         */
        QPointF movingTranslation() const;

        /**
         * @return The name of the specification.
         * @pre True.
         * @post The name of the specification has been returned.
         */
        QString name() const;

        /**
         * @return The form to modify the specification text.
         * @pre True.
         * @post The form to modify the specification text has been returned.
         */
        virtual QWidget *form() const;

        /**
         * @param formResults The form containing the results to apply.
         * @pre True.
         * @post The results in the form formResults have been applied.
         */
        void applyFormResults(const QWidget *formResults);

    protected:
        QString storedName; ///< The name of the specification
        bool fixed; ///< Whether the specification text can be edited

        /**
         * @param change The type of change that has to be applied to the
         *        specification.
         * @param value The value of the change that has to be applied to the
         *        specification.
         * @pre True.
         * @post The given change with the given value has been applied to the
         *       specification.
         */
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    private:
        /**
         * @invariant styleDecorationItems[0..styleDecorationItems.size() - 1] is
         *            contained by the specification.
         */
        QPointF storedTranslation; ///< The translation applied to the specification

        QStringList textStyles; ///< The styles of the specification text
        QList<QGraphicsItem*> styleDecorationItems; ///< Style decoration items of the specification

        /**
         * @param colorName The name of the color to load.
         * @pre True.
         * @post The specification has a color named colorName.
         */
        void loadColor(const QString &colorName);

        /**
         * @pre True.
         * @post The styles of the specification text have been applied.
         */
        void applyTextStyles();

        /**
         * @pre True.
         * @post The specification text is underlined with a dashed line.
         */
        void applyDashedUnderline();

        /**
         * @pre True.
         * @post The styles of the specification text have been cleared.
         */
        void clearStyleDecorations();

        /**
         * @param variant The variant containing the specification text data.
         * @pre True.
         * @post The specification text has been loaded from variant.
         */
        virtual void loadTextFromVariant(const QVariant &variant) = 0;

        /**
         * @return The variant containing the specification text data.
         * @pre True.
         * @post The variant containing the specification text data has been
         *       returned.
         */
        virtual QVariant variantFromText() const = 0;

        /**
         * @param fromResults The form containing the results to apply.
         * @pre True.
         * @post The specification text has been updated from the form results
         *       formResults.
         */
        virtual void updateTextFromForm(const QWidget *fromResults);
};

}

#endif // DIAGRAMSPECIFICATION_H
