/**
 * @file diagram.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of Diagram class.
 * @date Monday, July 20, 2026
 */
#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "jsonserializable.h"

#include <QGraphicsScene>
#include <QObject>
#include <QList>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QPointF;
class QWidget;
QT_END_NAMESPACE

namespace DiagramEditor::Specification {
class SpecificationsForm;
}

namespace DiagramEditor::Diagram {

class DiagramComponent;
class DiagramItem;

/**
 * @class Diagram
 * @brief A diagram that contains and manages diagram items.
 */
class Diagram : public QGraphicsScene, public DiagramEditor::Serialization::JsonSerializable
{
    Q_OBJECT

    public:
        /**
         * @enum EditionMode
         * @brief The possible edition modes.
         */
        enum class EditionMode {
            AddItemMode,        ///< A mouse press draws an item.
            SelectionMode,      ///< Rubber band selection is enabled.
            AddResizerMode,     ///< A mouse press adds a resizer to an item.
            RemoveResizerMode   ///< A mouse press removes a resizer from an item.
        };

        /**
         * @param sceneSize The size of the diagram canvas.
         * @param parent The container of the diagram.
         * @pre sceneSize > 0.
         * @post The diagram is contained by parent and its canvas is of size
         *       sceneSize.
         */
        explicit Diagram(int sceneSize = 1000, QObject *parent = nullptr);

        /**
         * @param hash The hash containing the data to load.
         * @pre True.
         * @post The diagram has been loaded using the data from the given hash.
         */
        void loadFromHash(const QVariantHash &hash) override;

        /**
         * @return The hash containing the diagram's data.
         * @pre True.
         * @post The hash containing the diagram's data has been returned.
         */
        QVariantHash toHash() const override;

        /**
         * @param mode The edition mode we want to set.
         * @pre True.
         * @post The diagram has the given edition mode.
         */
        void setEditionMode(const EditionMode &mode);

        /**
         * @param dragging Whether a diagram resizer is being dragged.
         * @pre True.
         * @post If dragging is true, the diagram is prepared to a resizer drag;
         *       otherwise, the diagram is not prepared to a resizer drag.
         */
        void setDraggingResizer(bool dragging);

        /**
         * @param formResults The specifications form containing the results to
         *        apply.
         * @pre True.
         * @post The results in the specifications form formResults have been
         *       applied to the single selected diagram item.
         */
        void setSpecifications(const QWidget *formResults);

        /**
         * @return The diagram item at the position.
         * @param pos The position whose diagram item we want to obtain.
         * @pre True.
         * @post The diagram item at the position pos.
         */
        DiagramItem *diagramItemAt(const QPointF &pos) const;

        /**
         * @return The id of a new diagram item.
         * @pre True.
         * @post The id of a new diagram item has been returned.
         */
        int newDiagramItemId() const;

        /**
         * @return The diagram component at the position that is not the component.
         * @param pos The position whose diagram item we want to obtain.
         * @param exception The component that we don't want to obtain.
         * @pre True.
         * @post The diagram component at the position pos that is not exception.
         */
        DiagramComponent *diagramComponentAt(const QPointF &pos, DiagramComponent *exception = nullptr) const;

        /**
         * @return The diagram component with the component id from the diagram
         *         item with the item id.
         * @param itemId The id of the diagram item of the diagram component we
         *        want to obtain.
         * @param componentId The id of the diagram component we want to obtain.
         * @pre True.
         * @post The diagram component with the id componentId in the diagram item
         *       with the id itemId has been returned.
         */
        DiagramComponent *componentByIds(int itemId, int componentId) const;

    signals:
        /**
         * @param pos The position of the requested diagram item.
         * @pre The diagram edition mode allows to add an item.
         * @post The signal has been emited with the position of the requested
         *       item.
         */
        void itemRequested(const QPointF &pos);

        /**
         * @param specificationsForm The specifications form of the single selected
         *        diagram item.
         * @pre The selected items have changed.
         * @post The signal has been emited with the specifications form of the
         *       single selected diagram item.
         */
        void selectedItemChanged(QWidget *specificationsForm);

    public slots:
        /**
         * @pre itemSelected is the currently selected item.
         * @post The item after itemSelected is the single selected diagram item.
         */
        void selectNextItem();

        /**
         * @param moveStep The move step we want to apply to the selected items.
         * @pre True.
         * @post The selected items have been moved by moveStep.
         */
        void moveSelectedItems(const QPointF &moveStep);

        /**
         * @pre True.
         * @post The selected items have been deleted.
         */
        void deleteSelectedItems();

    protected:
        /**
         * @param event The mouse event we want to handle.
         * @pre True.
         * @post The diagram has handled the given mouse move event.
         */
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

        /**
         * @param event The mouse event we want to handle.
         * @pre True.
         * @post The diagram has handled the given mouse press event.
         */
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    private slots:
        /**
         * @pre The single selected diagram item has changed.
         * @post The data of the single selected diagram item has been updated.
         */
        void updateSelectedItem();

    private:
        /**
         * @invariant -1 < selectedSingleItemIndex < diagramItems().size().
         */
        EditionMode editionMode; ///< The currently diagram edition mode
        bool draggingResizer; ///< Whether a diagram resizer is being dragged

        DiagramItem *shadowedItem; ///< The currently shadowed item
        int selectedSingleItemIndex; ///< The currently single selected diagram item index

        /**
         * @return The diagram items in the diagram.
         * @pre True.
         * @post The diagram items in the diagram have been returned.
         */
        QList<DiagramItem*> diagramItems() const;

        /**
         * @return The selected diagram items in the diagram.
         * @pre True.
         * @post The selected diagram items in the diagram have been returned.
         */
        QList<DiagramItem*> selectedDiagramItems() const;

        /**
         * @return The single selected diagram item in the diagram.
         * @pre True.
         * @post The single selected diagram item in the diagram have been
         *       returned.
         */
        DiagramItem *selectedSingleItem() const;

        /**
         * @return The specifications form to show when there's no single selected
         *         diagram item.
         * @pre True.
         * @post The specifications form to show when there's no single selected
         *       diagram item has been returned.
         */
        static QWidget *emptySpecificationsForm();
};

}

#endif // DIAGRAM_H
