/**
 * @file diagramcomponent.h
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Declaration of DiagramComponent class.
 * @date Monday, July 20, 2026
 */
#ifndef DIAGRAMCOMPONENT_H
#define DIAGRAMCOMPONENT_H

#include "jsonserializable.h"

#include <QColor>
#include <QObject>
#include <QPointF>

QT_BEGIN_NAMESPACE
class QGraphicsEllipseItem;
class QGraphicsItem;
QT_END_NAMESPACE

namespace DiagramEditor::Specification {
class SpecificationsForm;
}

namespace DiagramEditor::Diagram {

class DiagramItem;
using DiagramEditor::Specification::SpecificationsForm;

/**
 * @class DiagramComponent
 * @brief A diagram component contained by a diagram item.
 */
class DiagramComponent : public QObject, public DiagramEditor::Serialization::JsonSerializable
{
    Q_OBJECT

    public:
        /// The radius of the comment badge.
        static const int COMMENT_BADGE_RADIUS = 5;

        /// The color of the comment badge.
        static const QColor COMMENT_BADGE_COLOR;

        /**
         * @pre True.
         * @post The component doesn't have an active comment badge.
         */
        DiagramComponent();

        /**
         * @return The graphics item of the component.
         * @pre True.
         * @post The graphics item of the component has been returned.
         */
        QGraphicsItem *graphicsItem();

        /**
         * @return The z-value that has to be assigned to the component.
         * @pre True.
         * @post The z-value that has to be assigned to the component has
         *       been returned.
         */
        virtual int definedZValue() const;

        /**
         * @pre True.
         * @post The component is connected to its corresponding components.
         */
        virtual void connectComponent();

        /**
         * @return The specifications form of the component.
         * @pre True.
         * @post The specifications form of the component has been returned.
         */
        virtual SpecificationsForm *specificationsForm() const;

        /**
         * @param formResults The specifications form containing the results to
         *        apply.
         * @param formIndex The index of the component form in formResults.
         * @pre True.
         * @post The results in the specifications form with index formIndex in
         *       formResults have been applied to the component.
         */
        virtual void setSpecifications(const SpecificationsForm *formResults, int formIndex);

        /**
         * @param shadowed Whether we want to shadow the component or not.
         * @pre True.
         * @post If shadowed is true, the component is shadowed;
         *       otherwise, it's not shadowed.
         */
        virtual void setShadow(bool shadowed);

        /**
         * @param visible Whether we want to set the component resizers visible.
         * @pre True.
         * @post If visible is true, the component resizers are visible;
         *       otherwise, the component resizers are not visible.
         */
        virtual void setResizersVisibility(bool visible);

        /**
         * @return true if the component has a resizer at the scene position;
         *         false otherwise.
         * @param scenePos The scene position of the resizer we want to enable.
         * @pre True.
         * @post If the function returns true, the component resizer at scene
         *       position scenePos is active;
         *       otherwise, there's no component resizer at scene position
         *       scenePos.
         */
        virtual bool addResizer(const QPointF &scenePos);

        /**
         * @return true if the component has a resizer at the scene position;
         *         false otherwise.
         * @param scenePos The scene position of the resizer we want to disable.
         * @pre True.
         * @post If the function returns true, the component resizer at scene
         *       position scenePos is inactive;
         *       otherwise, there's no component resizer at scene position
         *       scenePos.
         */
        virtual bool removeResizer(const QPointF &scenePos);

        /**
         * @return true if the component can be resized to the position;
         *         false otherwise.
         * @param pos The position we want to know if the component can be resized
         *        to.
         * @pre True.
         * @post If the function returns true, the component can be resized to the
         *       position pos;
         *       otherwise, the component can't be resized to the position pos.
         */
        virtual bool canResizeTo(const QPointF &pos) const;

        /**
         * @pre True.
         * @post The component has been resized to its resizer positions.
         */
        virtual void resize();

        /**
         * @return The closest point of the component to the position where an item
         *         can be connected.
         * @param point The position we want to obtain its closest component
         *        connection point.
         * @param itemMapped true if point is mapped to the component;
         *        false if point is mapped to the scene.
         * @pre True.
         * @post The closest connection position of the component to the given point,
         *       mapped to the component if itemMapped is true or to the scene
         *       otherwise.
         */
        QPointF closestConnectionPoint(const QPointF &point, bool itemMapped = false);

        /**
         * @return The component id.
         * @pre True.
         * @post The component id has been returned.
         */
        int componentId() const;

        /**
         * @return The component diagram item id.
         * @pre True.
         * @post The component diagram item id has been returned.
         */
        int groupId() const;

        /**
         * @param visible Whether we want to set the component comment badge
         *        visible.
         * @pre True.
         * @post If visible is true, the component comment badge is visible;
         *       otherwise, the component comment badge is not visible.
         */
        void setCommentBadgeVisibility(bool visible);

    signals:
        /**
         * @pre The component's position has changed.
         * @post The signal has been emited.
         */
        void positionChanged();

        /**
         * @pre The component has been resized.
         * @post The signal has been emited.
         */
        void componentResized();

    protected:
        /**
         * @invariant componentGroup != nullptr.
         */
        DiagramItem *componentGroup; ///< The diagram item that contains the component
        QGraphicsEllipseItem *commentBadge; ///< The component comment badge

        /**
         * @pre True.
         * @post The component comment badge position has been updated.
         */
        void updateCommentBadgePos();

    private:
        /**
         * @return A new comment badge of the component.
         * @pre commentBadge == nullptr.
         * @post A new comment badge of the component has been returned.
         */
        QGraphicsEllipseItem *makeCommentBadge();

        /**
         * @return The active component comment badge position.
         * @pre True.
         * @post The active component comment badge position has been returned.
         */
        virtual QPointF commentBadgePos();

        /**
         * @return The closest point of the component to the position where an item can
         *         be connected.
         * @param mappedPoint The position we want to obtain its closest component
         *        connection point.
         * @pre True.
         * @post The closest connection position of the component to mappedPoint has
         *       been returned.
         */
        virtual QPointF closestConnectionMappedPoint(const QPointF &mappedPoint) const;
};

}

#endif // DIAGRAMCOMPONENT_H
