#include "mountainitem.h"
#include <QPainter>
#include <QPixmap>


namespace Widget {

MountainItem::MountainItem()
{

}

} // namespace Widget


QRectF Widget::MountainItem::boundingRect() const
{
    return QRectF(0,0,500,255);
}

void Widget::MountainItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawPixmap(0,0,QPixmap(":/mountain/bin/asset/mountain/mountain0002.png"));
}
