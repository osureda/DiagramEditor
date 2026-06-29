/**
 * @file connectableresizer.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of ConnectableResizer class.
 * @date Monday, July 20, 2026
 */
#ifndef CONNECTABLERESIZER_H
#define CONNECTABLERESIZER_H

#include "diagramresizer.h"
#include "jsonserializable.h"

#include <QObject>
#include <QStringList>
#include <QVariant>

class DiagramComponent;

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

/**
 * @class ConnectableResizer
 * @brief A diagram resizer that can be connected to a diagram component.
 */
class ConnectableResizer : public DiagramResizer, public JsonSerializable
{
    Q_OBJECT

    public:
        /**
         * @param parent The component to which the resizer resizes.
         * @pre True.
         * @post The resizer can resize the component parent.
         */
        explicit ConnectableResizer(DiagramComponent *parent);

        /**
         * @param hash The hash containing the data to load.
         * @pre True.
         * @post The resizer has been loaded using the data from the given hash.
         */
        void loadFromHash(const QVariantHash &hash) override;

        /**
         * @return The hash containing the resizer's data.
         * @pre True.
         * @post The hash containing the resizer's data has been returned.
         */
        QVariantHash toHash() const override;

        /**
         * @pre True.
         * @post The resizer has been connected to its corresponding connected
         *       component.
         */
        void connectResizer();

    protected:
        /**
         * @param event The mouse event we want to handle.
         * @pre The resizer is in a diagram scene.
         * @post The resizer has handled the given mouse move event.
         */
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

        /**
         * @param event The mouse event we want to handle.
         * @pre True.
         * @post The resizer has handled the given mouse release event.
         */
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

        /**
         * @param change The type of change that has to be applied to the resizer.
         * @param value The value of the change that has to be applied to the
         *        resizer.
         * @pre parentComponent != nullptr.
         * @post The given change with the given value has been applied to the
         *       resizer.
         */
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    protected slots:
        /**
         * @pre True.
         * @post If the resizer is connected, the connection position has been applied;
         *       otherwise, the position parentMappedPos has been applied.
         */
        void updateParentPosition() override;

    private:
        QStringList connectableTypes; ///< The types of components to which the resizer can be connected
        bool fixed; ///< Whether the resizer can't be disconnected from its connected component

        int connectedItemId; ///< The ID of the diagram item to which the resizer is connected
        int connectedComponentId; ///< The ID of the diagram component to which the resizer is connected
        DiagramComponent *connectedComponent; ///< The diagram component to which the resizer is connected

        DiagramComponent *shadowedComponent; ///< The component that is shadowed by the resizer

        /**
         * @param component The component to which we want to connect the resizer.
         * @pre True.
         * @post The resizer has been connected to the given component.
         */
        void connectTo(DiagramComponent *component);

        /**
         * @param component The component from which we want to disconnect the
         *        resizer.
         * @pre True.
         * @post The resizer has been disconnected from the given component.
         */
        void disconnectFrom(DiagramComponent *component);
};

#endif // CONNECTABLERESIZER_H
