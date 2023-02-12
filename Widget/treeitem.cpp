#include "treeitem.h"
#include <QPainter>

namespace Widget {
namespace GraphicsItem {

TreeItem::TreeItem()
{

}

} // namespace GraphicsItem
} // namespace Widget


QRectF Widget::GraphicsItem::TreeItem::boundingRect() const
{
    return QRectF(0,0,this->assetWidth(),this->assetHeight());
}

void Widget::GraphicsItem::TreeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap(this->assetPath().c_str());

    painter->drawPixmap(0,0,this->assetWidth(),this->assetHeight(),pixmap);
}
