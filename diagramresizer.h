/**
 * @file diagramresizer.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of DiagramResizer class.
 * @date Monday, July 20, 2026
 */
#ifndef DIAGRAMRESIZER_H
#define DIAGRAMRESIZER_H

#include <QColor>
#include <QGraphicsRectItem>
#include <QList>
#include <QObject>
#include <QPointF>
#include <QVariant>

class DiagramComponent;

QT_BEGIN_NAMESPACE
class QGraphicsItem;
QT_END_NAMESPACE

/**
 * @class DiagramResizer
 * @brief An item to resize a diagram component.
 */
class DiagramResizer : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

    public:
        /// The color of the resizer.
        static const QColor COLOR;

        /// The size of the resizer.
        static const int SIZE = 10;

        /**
         * @param parent The component to which the resizer resizes.
         * @pre True.
         * @post The resizer can resize the component parent.
         */
        explicit DiagramResizer(DiagramComponent *parent);

        /**
         * @return The center position of the cresizer.
         * @pre True.
         * @post The center position of the cresizer has been returned.
         */
        QPointF sceneCenterPos() const;

        /**
         * @param position The center position where we want to move the resizer.
         * @pre True.
         * @post The given position is the center position of the resizer.
         */
        void setSceneCenterPos(const QPointF &position);

    protected:
        /**
         * @invariant parentItem == parentComponent->graphicsItem().
         */
        DiagramComponent *parentComponent; ///< The component to wich the resizer can resize
        QGraphicsItem *parentItem; ///< The graphics item to wich the resizer can resize

        QPointF parentMappedPos; ///< The position of the reizer mapped to parentItem

        /**
         * @param event The mouse event we want to handle.
         * @pre The resizer is in a diagram scene.
         * @post The resizer has handled the given mouse press event.
         */
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

        /**
         * @param event The mouse event we want to handle.
         * @pre True.
         * @post The resizer has handled the given mouse move event.
         */
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

        /**
         * @param event The mouse event we want to handle.
         * @pre The resizer is in a diagram scene.
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
         * @post The position parentMappedPos has been applied.
         */
        virtual void updateParentPosition();
};

#endif // DIAGRAMRESIZER_H
