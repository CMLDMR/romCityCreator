#ifndef WIDGET_GRAPHICSITEM_TREEITEM_H
#define WIDGET_GRAPHICSITEM_TREEITEM_H

#include "Asset/tree.h"
#include <QGraphicsItem>

namespace Widget {
namespace GraphicsItem {

class TreeItem : public QGraphicsItem, public Assets::Tree::Tree
{
public:
    TreeItem();

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

} // namespace GraphicsItem
} // namespace Widget

#endif // WIDGET_GRAPHICSITEM_TREEITEM_H
