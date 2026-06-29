/**
 * @file diagramitem.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of DiagramItem class.
 * @date Monday, July 20, 2026
 */
#include "diagramitem.h"

#include "diagram.h"
#include "diagramcomponent.h"
#include "diagramconnection.h"
#include "diagramelement.h"
#include "specificationsform.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QTextEdit>
#include <QWidget>

namespace DiagramEditor::Diagram {

DiagramItem::DiagramItem(Diagram *scene)
    : id(scene->newDiagramItemId())
    , loaded(false)
{
    scene->addItem(this);

    setAcceptedMouseButtons(Qt::LeftButton);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

int DiagramItem::itemId() const {
    return id;
}

QPointF DiagramItem::centerOffset() const {
    if (components.isEmpty()) {
        return QPointF(0, 0);
    }

    const QGraphicsItem *centerItem = components.first().graphics;
    return centerItem->mapToParent(centerItem->boundingRect().center());
}

int DiagramItem::definedZValue() const {
    int totalZValue = 0;

    for (const Component &component : components) {
        totalZValue += component.object->definedZValue();
    }

    return totalZValue / components.size();
}

void DiagramItem::loadFromHash(const QVariantHash &hash) {
    clear();

    if (hash.contains("id")) {
        id = hash["id"].toInt();
    }

    if (hash.contains("x")) {
        setX(hash["x"].toReal());
    }
    if (hash.contains("y")) {
        setY(hash["y"].toReal());
    }

    comment = hash["comment"].toString();

    const QVariantList componentsData = hash["components"].toList();
    if (!componentsData.isEmpty()) {
        for (const QVariant &componentData : componentsData) {
            addComponent(componentData.toHash());
        }

        setZValue(definedZValue());
    }
}

QVariantHash DiagramItem::toHash() const {
    QVariantList componentsData;
    for (const Component &component : components) {
        componentsData.append(QVariantHash{
            {"id", component.id},
            {"type", component.type},
            {"x", component.graphics->x()}, {"y", component.graphics->y()},
            {"features", component.object->toHash()}
        });
    }

    return {
        {"id", itemId()},
        {"x", pos().x()}, {"y", pos().y()},
        {"comment", comment},
        {"components", componentsData}
    };
}

void DiagramItem::connectComponents() {
    for (Component &component : components) {
        component.object->connectComponent();
    }
}

void DiagramItem::setLoaded(bool isLoaded) {
    loaded = isLoaded;
}

SpecificationsForm *DiagramItem::specificationsForm() const {
    SpecificationsForm *form = new SpecificationsForm();

    for (const Component &component : components) {
        form->appendForm(component.object->specificationsForm());
    }

    form->appendForm(commentForm());

    return form;
}

void DiagramItem::setSpecifications(const SpecificationsForm *formResults) {
    for (int i = 0; i < components.size() && i < formResults->formCount() - 1; i++) {
        components[i].object->setSpecifications(formResults, i);
    }

    setComment(formResults);
}

void DiagramItem::setShadow(bool shadowed) {
    for (Component &component : components) {
        component.object->setShadow(shadowed);
    }
}

bool DiagramItem::setResizerEnabled(const QPointF &scenePos, bool enabled) {
    bool resizerEnabled = false;
    int i = 0;

    while (!resizerEnabled && i < components.size()) {
        if ((enabled && components[i].object->addResizer(scenePos)) ||
            (!enabled && components[i].object->removeResizer(scenePos))) {
            resizerEnabled = true;
        } else {
            i++;
        }
    }

    return resizerEnabled;
}

void DiagramItem::updateGeometry() {
    if (loaded) {
        QGraphicsRectItem *auxItem = new QGraphicsRectItem();
        auxItem->setVisible(false);
        addToGroup(auxItem);

        removeFromGroup(auxItem);
        delete auxItem;
    }
}

int DiagramItem::componentId(const DiagramComponent *component) const {
    for (int i = 0; i < components.size(); i++) {
        if (components[i].object == component) {
            return i;
        }
    }

    return -1;
}

DiagramComponent *DiagramItem::componentById(int id) const {
    for (const Component &component : components) {
        if (component.id == id) {
            return component.object;
        }
    }

    return nullptr;
}

DiagramComponent *DiagramItem::componentAt(const QPointF &scenePos) const {
    for (const Component &component : components) {
        if (component.graphics->contains(component.graphics->mapFromScene(scenePos))) {
            return component.object;
        }
    }

    return nullptr;
}

bool DiagramItem::componentTypeMatches(const DiagramComponent *component, const QStringList &types) {
    return dynamic_cast<const DiagramElement*>(component) && types.contains("element") ||
           dynamic_cast<const DiagramConnection*>(component) && types.contains("connection");
}

QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemSelectedHasChanged) {
        setResizersVisibility(value.toBool());
    }

    if (change == QGraphicsItem::ItemPositionHasChanged) {
        for (Component &component : components) {
            component.object->positionChanged();
        }
    }

    return QGraphicsItemGroup::itemChange(change, value);
}

void DiagramItem::addComponent(const QVariantHash &componentData) {
    Component newComponent;
    newComponent.id = componentData["id"].toInt();
    newComponent.type = componentData["type"].toString();
    newComponent.object = makeDiagramComponent(componentData["type"].toString());
    newComponent.object->loadFromHash(componentData["features"].toHash());

    newComponent.graphics = newComponent.object->graphicsItem();
    newComponent.graphics->setParentItem(this);
    newComponent.graphics->setZValue(newComponent.object->definedZValue());

    if (componentData.contains("x")) {
        newComponent.graphics->setX(componentData["x"].toReal());
    }
    if (componentData.contains("y")) {
        newComponent.graphics->setY(componentData["y"].toReal());
    }

    addToGroup(newComponent.graphics);
    components.append(newComponent);
}

DiagramComponent *DiagramItem::makeDiagramComponent(const QString &type) {
    if (type == "connection") {
        return new DiagramConnection(this);
    }
    if (type != "element") {
        qCritical() << "Unrecognized diagram component type: " << type;
    }
    return new DiagramElement(this);
}

void DiagramItem::clear() {
    QList<QGraphicsItem*> items = childItems();
    for (auto it = items.begin(); it != items.end(); ++it) {
        removeFromGroup(*it);
        delete *it;
    }

    comment = "";
    components.clear();

    loaded = false;
}

void DiagramItem::setResizersVisibility(bool visible) {
    for (Component &component : components) {
        component.object->setResizersVisibility(visible);
    }
}

SpecificationsForm *DiagramItem::commentForm() const {
    SpecificationsForm *commentForm = new SpecificationsForm();

    QTextEdit *textEditor = new QTextEdit();
    textEditor->setPlainText(comment);
    commentForm->appendField("Comment", textEditor);

    return commentForm;
}

void DiagramItem::setComment(const SpecificationsForm *formResults) {
    QWidget *commentResults = formResults->fieldResults(formResults->formCount() - 1, "Comment");

    const QTextEdit *textEditor = qobject_cast<const QTextEdit*>(commentResults);
    if (textEditor) {
        const QString newComment = textEditor->toPlainText();

        if (comment != newComment) {
            if (comment == "") {
                setCommentBadgeVisibility(true);
            } else if (newComment == "") {
                setCommentBadgeVisibility(false);
            }
            comment = newComment;
        }
    }
}

void DiagramItem::setCommentBadgeVisibility(bool visible) {
    if (!components.isEmpty()) {
        components.first().object->setCommentBadgeVisibility(visible);
    }
}

}
