/**
 * @file diagramspecification.cpp
 * @author Sureda-Cuevas:Óscar:u1988988
 * @brief Implementation of DiagramSpecification class.
 * @date Monday, July 20, 2026
 */
#include "diagramspecification.h"

#include "jsonserializable.h"

#include <QColor>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPen>
#include <QWidget>

namespace DiagramEditor::Specification {

DiagramSpecification::DiagramSpecification(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
    , storedTranslation(0, 0)
{
    setZValue(50);
}

void DiagramSpecification::loadFromHash(const QVariantHash &hash) {
    storedName = hash["name"].toString();

    loadColor(hash["color"].toString());

    loadTextFromVariant(hash["value"]);

    clearStyleDecorations();
    textStyles = hash["styles"].toStringList();
    applyTextStyles();

    fixed = hash["fixed"].toBool();
}

QVariantHash DiagramSpecification::toHash() const {
    QVariantHash hash;

    hash["name"] = storedName;
    hash["color"] = defaultTextColor().name();
    hash["styles"] = textStyles;
    hash["value"] = variantFromText();
    hash["fixed"] = fixed;

    return hash;
}

QPointF DiagramSpecification::movingTranslation() const {
    return storedTranslation;
}

QString DiagramSpecification::name() const {
    return storedName;
}

QWidget *DiagramSpecification::form() const {
    return new QWidget();
}

void DiagramSpecification::applyFormResults(const QWidget *fromResults) {
    updateTextFromForm(fromResults);

    clearStyleDecorations();
    applyTextStyles();
}

QVariant DiagramSpecification::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionChange && isSelected()) {
        storedTranslation += value.toPointF() - pos();
    }

    return QGraphicsTextItem::itemChange(change, value);
}

void DiagramSpecification::loadColor(const QString &colorName) {
    const QColor color(colorName);
    if (color.isValid()) {
        setDefaultTextColor(color);
    }
}

void DiagramSpecification::applyTextStyles() {
    QFont font;

    for (QString &style : textStyles) {
        if (style == "B") {
            font.setBold(true);
        } else if (style == "I") {
            font.setItalic(true);
        } else if (style == "U") {
            font.setUnderline(true);
        } else if (style == "DU") {
            applyDashedUnderline();
        }
    }

    setFont(font);
}

void DiagramSpecification::applyDashedUnderline() {
    QGraphicsPathItem *underlined = new QGraphicsPathItem(this);

    QPen pen(defaultTextColor(), 1);
    pen.setStyle(Qt::DashLine);
    underlined->setPen(pen);

    QPainterPath path(boundingRect().bottomLeft());
    path.lineTo(boundingRect().bottomRight());
    underlined->setPath(path);

    styleDecorationItems.append(underlined);
}

void DiagramSpecification::clearStyleDecorations() {
    for (auto it = styleDecorationItems.begin(); it != styleDecorationItems.end(); ++it) {
        delete *it;
    }
    styleDecorationItems.clear();
}

void DiagramSpecification::updateTextFromForm(const QWidget *) {}

}
