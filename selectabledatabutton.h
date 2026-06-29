/**
 * @file selectabledatabutton.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of SelectableDataButton class.
 * @date Monday, July 20, 2026
 */
#ifndef SELECTABLEDATABUTTON_H
#define SELECTABLEDATABUTTON_H

#include "jsonserializable.h"

#include <QIcon>
#include <QObject>
#include <QPair>
#include <QPushButton>
#include <QString>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

namespace DiagramEditor::Gui {

/**
 * @class SelectableDataButton
 * @brief A checkable button with associated data.
 */
class SelectableDataButton : public QPushButton, public DiagramEditor::Serialization::JsonSerializable
{
    Q_OBJECT

    public:
        /// The size of the space between the icon and the text.
        static const int ICON_TEXT_SPACING = 2;

        /// The style of the button content.
        static const QString STYLE_SHEET;

        /**
         * @param iconSize The size of the button icon.
         * @param parent The container of the button.
         * @pre iconSize >= 0.
         * @post The button is empty, is contained by parent and its icon has a
         *       size of iconSize.
         */
        explicit SelectableDataButton(int iconSize = 0, QWidget *parent = nullptr);

        /**
         * @param hash The hash containing the data to load.
         * @pre True.
         * @post The button data has been loaded using the data from the given
         *       hash.
         */
        void loadFromHash(const QVariantHash &hash) override;

        /**
         * @return The data associated with the button.
         * @pre True.
         * @post The data associated with the button has been returned.
         */
        QVariantHash data() const;

        /**
         * @return The button with the icon to the left of the text.
         * @pre True.
         * @post The button with the icon to the left of the text has been
         *       returned.
         */
        SelectableDataButton *leftIconButton() const;

        /**
         * @return A widget with the icon above the text button and the text
         *         button.
         * @pre True.
         * @post A widget with the icon above the text button and the text
         *       button has been returned.
         */
        QPair<QWidget*, SelectableDataButton*> upperIconButton() const;

    private:
        /**
         * @invariant storedIconSize >= 0.
         */
        int storedIconSize; ///< The size of the icon
        QIcon storedIcon; ///< The icon of the button
        QString storedText; ///< The text of the button
        bool spacingApplied; ///< Whether spacing has been applied between the icon and the text.
        QVariantHash storedData; ///< The data associated with the button.

        /**
         * @param variant The variant containing the data of the icon.
         * @pre True.
         * @post The icon has been loaded using the data from the given variant.
         */
        void loadLeftIconFromVariant(const QVariant &variant);

        /**
         * @param nameVariant The variant containing the data of the name.
         * @param descriptionVariant The variant containing the data of the
         *        description.
         * @pre True.
         * @post The button's name has been loaded using the data from nameVariant
         *       and the button's description has been loaded using the data from
         *       descriptionVariant.
         */
        void loadTextFromVariants(const QVariant &nameVariant, const QVariant &descriptionVariant);

        /**
         * @pre True.
         * @post Spacing has been applied between the icon and the text.
         */
        void applyIconTextSpacing();

        /**
         * @return The button with text only.
         * @pre True.
         * @post The button with text only has been returned.
         */
        SelectableDataButton *textButton() const;
};

}

#endif // SELECTABLEDATABUTTON_H
