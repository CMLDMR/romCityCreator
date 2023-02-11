#ifndef WIDGET_MOUNTAINITEM_H
#define WIDGET_MOUNTAINITEM_H

#include "Asset/mountain.h"
#include <QGraphicsItem>

namespace Widget {

class MountainItem : public QGraphicsItem, public Assets::Terrain::Mountain
{
public:
    MountainItem();

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

} // namespace Widget

#endif // WIDGET_MOUNTAINITEM_H
