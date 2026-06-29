/**
 * @file diagramitem.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of DiagramItem class.
 * @date Monday, July 20, 2026
 */
#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include "jsonserializable.h"

#include <QGraphicsItemGroup>
#include <QList>
#include <QPointF>
#include <QObject>
#include <QString>
#include <QVariant>

class Diagram;
class DiagramComponent;
class SpecificationsForm;

QT_BEGIN_NAMESPACE
class QGraphicsItem;
QT_END_NAMESPACE

/**
 * @class DiagramItem
 * @brief A diagram item that contains and manages diagram components.
 */
class DiagramItem : public QObject, public QGraphicsItemGroup, public JsonSerializable
{
    Q_OBJECT

    public:
        /**
         * @struct Component
         * @brief The data of a diagram component.
         */
        struct Component {
            int id;                     ///< The diagram component id
            QString type;               ///< The diagram component type
            QGraphicsItem *graphics;    ///< The graphical item of the diagram component
            DiagramComponent *object;   ///< The diagram component
        };

        /**
         * @param scene The container scene of the item.
         * @pre True.
         * @post The item is contained by scene.
         */
        explicit DiagramItem(Diagram *scene);

        /**
         * @return The id of the item.
         * @pre True.
         * @post The id of the item has been returned.
         */
        int itemId() const;

        /**
         * @return The distance from the item's position to its center.
         * @pre True.
         * @post The distance from the item's position to its center has been
         *       returned.
         */
        QPointF centerOffset() const;

        /**
         * @return The z-value of the item.
         * @pre True.
         * @post The z-value of the item has been returned.
         */
        int definedZValue() const;

        /**
         * @param hash The hash containing the data to load.
         * @pre True.
         * @post The item has been loaded using the data from the given hash.
         */
        void loadFromHash(const QVariantHash &hash) override;

        /**
         * @return The hash containing the item's data.
         * @pre True.
         * @post The hash containing the item's data has been returned.
         */
        QVariantHash toHash() const override;

        /**
         * @pre True.
         * @post The components of the item are connected to their corresponding
         *       components.
         */
        void connectComponents();

        /**
         * @param isLoaded Whether the item has been loaded.
         * @pre True.
         * @post If isLoaded, the item has been loaded;
         *       otherwise, the item has not been loaded.
         */
        void setLoaded(bool isLoaded);

        /**
         * @return The specifications form of the item.
         * @pre True.
         * @post The specifications form of the item has been returned.
         */
        SpecificationsForm *specificationsForm() const;

        /**
         * @param formResults The specifications form containing the results to
         *        apply.
         * @pre True.
         * @post The results in the specifications form formResults have been
         *       applied to the item.
         */
        void setSpecifications(const SpecificationsForm *formResults);

        /**
         * @param shadowed Whether we want to shadow the item or not.
         * @pre True.
         * @post If shadowed is true, the item is shadowed;
         *       otherwise, it's not shadowed.
         */
        void setShadow(bool shadowed);

        /**
         * @return true if the item has a resizer at the scene position;
         *         false otherwise.
         * @param scenePos The scene position of the resizer we want to edit.
         * @param enabled Whether we want to enable the resizer.
         * @pre True.
         * @post If the function returns true, the item resizer at scene position
         *       scenePos is active whether enabled is true;
         *       otherwise, there's no item resizer at scene position scenePos.
         */
        bool setResizerEnabled(const QPointF &scenePos, bool enabled);

        /**
         * @pre True.
         * @post If the item is loaded, its geometry has been updated.
         */
        void updateGeometry();

        /**
         * @return The id of an item's component.
         * @param component The item's component whose id we want to obtain.
         * @pre True.
         * @post The id of the given item's component has been returned.
         */
        int componentId(const DiagramComponent *component) const;

        /**
         * @return An item's component by its id.
         * @param id The id of the item's component we want to obtain.
         * @pre True.
         * @post The item's component with the given id has been returned.
         */
        DiagramComponent *componentById(int id) const;

        /**
         * @return The item component at the scene position.
         * @param scenePos The scene position whose item component we want to
         *        obtain.
         * @pre True.
         * @post The item's component at the scene position scenePos has been
         *       returned.
         */
        DiagramComponent *componentAt(const QPointF &scenePos) const;

        /**
         * @return true if the diagram component type matches with one of the types;
         *         false otherwise.
         * @param component The component whose type is checked.
         * @param types The list of types to compare with the component type.
         * @pre True.
         * @post If the function returns true, the given diagram component type
         *       matches one of the given types.
         */
        static bool componentTypeMatches(const DiagramComponent *component, const QStringList &types);

    protected:
        /**
         * @param change The type of change that has to be applied to the item.
         * @param value The value of the change that has to be applied to the item.
         * @pre True.
         * @post The given change with the given value has been applied to the
         *       item.
         */
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    private:
        /**
         * @invariant id >= 0
         * @invariant components[i].graphics == components[i].object->graphicsItem()
         */
        int id; ///< The id of the item
        QString comment; ///< The comment given to the item

        bool loaded; ///< Whether the item has been loaded
        QList<Component> components; ///< The item diagram components data

        /**
         * @param componentData The data of the diagram component we want to add to
         *        the item.
         * @pre True.
         * @post A diagram component loaded from componentData has been added to
         *       the item.
         */
        void addComponent(const QVariantHash &componentData);

        /**
         * @return A diagram component of the type.
         * @param type The type of the diagram component we want to obtain.
         * @pre True.
         * @post A diagram component of the given type has been returned.
         */
        DiagramComponent *makeDiagramComponent(const QString &type);

        /**
         * @pre True.
         * @post The item is empty.
         */
        void clear();

        /**
         * @param visible Whether we want to set the item resizers visible.
         * @pre True.
         * @post If visible is true, the item resizers are visible;
         *       otherwise, the item resizers are not visible.
         */
        void setResizersVisibility(bool visible);

        /**
         * @return The specifications form that allows to give a comment to the
         *         item.
         * @pre True.
         * @post The specifications form that allows to give a comment to the
         *       item has been returned.
         */
        SpecificationsForm *commentForm() const;

        /**
         * @param formResults The specifications form containing the results to
         *        edit the item's comment.
         * @pre True.
         * @post The results in the specifications form formResults have been
         *       applied to the item's comment.
         */
        void setComment(const SpecificationsForm *formResults);

        /**
         * @param visible Whether we want to set the item comment badge visible.
         * @pre True.
         * @post If visible is true, the item comment badge is visible;
         *       otherwise, the item comment badge is not visible.
         */
        void setCommentBadgeVisibility(bool visible);
};

#endif // DIAGRAMITEM_H
