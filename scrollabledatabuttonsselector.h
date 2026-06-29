/**
 * @file scrollabledatabuttonsselector.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of ScrollableDataButtonsSelector class.
 * @date Monday, July 20, 2026
 */
#ifndef SCROLLABLEDATABUTTONSSELECTOR_H
#define SCROLLABLEDATABUTTONSSELECTOR_H

#include <QObject>
#include <QScrollArea>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QButtonGroup;
class QGridLayout;
class QWidget;
QT_END_NAMESPACE

namespace DiagramEditor::Gui {

/**
 * @class ScrollableDataButtonsSelector
 * @brief A scrollable widget for selecting a data button.
 */
class ScrollableDataButtonsSelector : public QScrollArea
{
    Q_OBJECT

    public:
        /// The spacing between buttons whose icon is above the text.
        static const int UPPER_ICONS_SPACING = 20;

        /**
         * @param parent The container of the selector.
         * @pre True.
         * @post The selector has one column of buttons with no icons and is
         *       contained by parent.
         */
        explicit ScrollableDataButtonsSelector(QWidget *parent = nullptr);

        /**
         * @param nColumns The number of button columns of the selector.
         * @param iconsSize The size of the button icons.
         * @param upperIcons Whether the buttons have the icons above the text.
         * @param parent The container of the selector.
         * @pre True.
         * @post The selector is contained by parent and has nColumns columns of
         *       buttons with icons of size iconsSize and above the text if
         *       upperIcons is true.
         */
        ScrollableDataButtonsSelector(int nColumns, int iconsSize, bool upperIcons, QWidget *parent = nullptr);

        /**
         * @param buttonsData The data of the buttons we want to add.
         * @pre True.
         * @post Buttons with the data from buttonsData have been added to the
         *       selector.
         */
        void addButtons(const QVariantHash &buttonsData);

        /**
         * @return The data of the selected button.
         * @pre True.
         * @post The data of the selected button has been returned.
         */
        QVariantHash selectedButtonData() const;

        /**
         * @pre True.
         * @post The selector contains no buttons.
         */
        void clear();

    signals:
        /**
         * @param selectedButtonData The data of the selected button.
         * @pre The selected button has changed.
         * @post The signal has been emited with the selected button data.
         */
        void selectionChanged(const QVariantHash &selectedButtonData);

    private slots:
        /**
         * @param buttonId The ID of the toggled button.
         * @param checked Whether the button is checked.
         * @pre True.
         * @post If checked is true, the button with ID buttonId has been selected.
         */
        void buttonToggled(int buttonId, bool checked);

    private:
        /**
         * @invariant nColumns >= 0.
         * @invariant buttons->buttons.size() == nButtons.
         * @invariant iconsSize >= 0.
         */
        QGridLayout *layout; ///< The layout of the selector
        int nColumns; ///< The number of button columns of the selector

        QButtonGroup *buttons; ///< The buttons of the selector
        int nButtons; ///< The number of buttons in the selector

        int iconsSize; ///< The size of the button icons
        bool upperIcons; ///< Whether the button icons are above the text

        /**
         * @param buttonData The data of the button we want to add.
         * @pre True.
         * @post A button with the data from buttonData has been added to the
         *       selector.
         */
        void addButton(const QVariantHash &buttonData);
};

}

#endif // SCROLLABLEDATABUTTONSSELECTOR_H
