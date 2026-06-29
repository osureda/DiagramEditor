#ifndef FIXEDSPECIFICATION_H
#define FIXEDSPECIFICATION_H

#include "diagramspecification.h"

#include <QList>
#include <QString>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

class FixedSpecification : public DiagramSpecification
{
public:
    FixedSpecification(QGraphicsItem *parent = nullptr);
    QWidget *form() const;
    void applyFormResults(const QWidget *formResults);

private:
    QString text;

    void loadTextFromVariant(const QVariant &variant) override;
    QVariant variantFromText() const override;

#endif // FIXEDSPECIFICATION_H
