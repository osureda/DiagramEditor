/**
 * @file mainwindow.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of MainWindow class.
 * @date Monday, July 20, 2026
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "diagramtype.h"

#include <QMainWindow>
#include <QObject>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QPointF;
class QWidget;

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace DiagramEditor::Diagram {
class Diagram;
}

namespace DiagramEditor::Gui {

class Wizard;

/**
 * @class MainWindow
 * @brief The main window of the diagram editor application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        /// The size of the diagram canvas.
        static const int CANVAS_SIZE = 2000;

        /// The size of the diagram item icons.
        static const int ITEM_ICON_SIZE = 25;

        /// The length of a diagram item move step.
        static const int ITEM_MOVE_STEP = 10;

        /**
         * @param diagramGroups The data of the diagram type groups to choose.
         * @param diagramTypes The data of the diagram types to choose.
         * @param diagramItems The data of all the diagram items.
         * @param parent The container of the window.
         * @pre True.
         * @post The window is contained by parent and contains a wizard to choose
         *       a group of diagram items from diagramItems associated to a diagram
         *       type group from diagramGroups and to a diagram type from
         *       diagramTypes.
         */
        MainWindow(const QVariantHash &diagramGroups,
                   const QVariantHash &diagramTypes,
                   const QVariantHash &diagramItems,
                   QWidget *parent = nullptr);

        /**
         * @pre True.
         * @post The window has been destroyed.
         */
        ~MainWindow() override;

    private slots:
        /**
         * @pre The initialization wizard has been accepted.
         * @post The edition tools are available to create a diagram based on the
         *       configuration selected in the initialization wizard.
         */
        void wizardAccepted();

        /**
         * @param pos The position of the item to draw.
         * @pre The initialization wizard has been accepted and wizardAccepted()
         *      has been called.
         * @post The selected diagram item in the diagram item selector has been
         *       drawn on the canvas at the position pos.
         */
        void drawItem(const QPointF &pos);

        /**
         * @param modeButton The checked button in the edition tools button group.
         * @pre True.
         * @post The edition mode is the mode associated with modeButton.
         */
        void setEditionMode(const QAbstractButton *modeButton);

        /**
         * @param form The specifications form to show.
         * @pre True.
         * @post The given specifications form has been displayed.
         */
        void showSpecificationsForm(QWidget *form);

        /**
         * @pre True.
         * @post The specifications form results have been applied.
         */
        void saveSpecificationsForm();

        /**
         * @pre True.
         * @post The JSON file content has been copied to clipboard.
         */
        void copyJsonToClipboard() const;

        /**
         * @pre True.
         * @post The JSON file content is the clipboard content.
         */
        void pasteJsonFromClipboard();

        /**
         * @pre True.
         * @post The JSON file content has been loaded from the diagram.
         */
        void loadJsonFromScene();

        /**
         * @pre The JSON file content represents a diagram.
         * @post The diagram has been loaded from the JSON file content.
         */
        void saveJsonToScene();

        /**
         * @pre True.
         * @post The selected diagram items have been moved one step up.
         */
        void keyUpPressed();

        /**
         * @pre True.
         * @post The selected diagram items have been moved one step down.
         */
        void keyDownPressed();

        /**
         * @pre True.
         * @post The selected diagram items have been moved one step to the left.
         */
        void keyLeftPressed();

        /**
         * @pre True.
         * @post The selected diagram items have been moved one step to the right.
         */
        void keyRightPressed();

        /**
         * @pre The JSON file content represents a diagram.
         * @post If the specifications tab is active, the specifications form
         *       results have been applied;
         *       otherwise, the diagram has been loaded from the JSON file content.
         */
        void keyEnterPressed();

    private:
        Ui::MainWindow *ui; ///< Window's user interface

        Wizard *wizard; ///< The initialization wizard
        DiagramEditor::Diagram::Diagram *diagram; ///< The edited diagram

        QVariantHash allDiagramItems; ///< The data of all the diagram items

        /**
         * @param requiredDiagramItemsTabs The diagram items of each diagram item
         *        selector tab that we want to display.
         * @pre requiredDiagramItemsTabs.size() > 0.
         * @post For each key-value pair in requiredDiagramItemsTabs, a tab named
         *       after the key and containing the diagram items to choose defined
         *       by the value data has been added to the diagram item selector.
         */
        void displayDiagramItems(const DiagramType::DiagramItemsIds &requiredDiagramItemsTabs);

        /**
         * @pre True.
         * @post The edition tools related to window actions have been configured.
         */
        void connectWindowActions();

        /**
         * @pre True.
         * @post The edition tools related to keyboard actions have been
         *       configured.
         */
        void connectKeyboardActions();

        /**
         * @pre True.
         * @post The specifications tab is empty.
         */
        void clearSpecificationsForm();

        /**
         * @param moveStep The step to move the selected items.
         * @pre True.
         * @post The selected items have been moved by the given step.
         */
        void moveDiagramItems(const QPointF &moveStep);
};

}

#endif // MAINWINDOW_H
