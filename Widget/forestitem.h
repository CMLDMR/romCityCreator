#ifndef WIDGET_FORESTITEM_H
#define WIDGET_FORESTITEM_H

#include "Asset/forest.h"
#include <QGraphicsItem>

namespace Widget {

class ForestItem : public QGraphicsItem, public Assets::Plant::Forest
{
public:
    ForestItem();



    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

} // namespace Widget

#endif // WIDGET_FORESTITEM_H