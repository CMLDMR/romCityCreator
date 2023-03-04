#include "forestitem.h"
#include <QPainter>
#include <QTextItem>
#include "Asset/tree.h"

#include <QRgb>

namespace Widget {

ForestItem::ForestItem()
{

}

void ForestItem::Build()
{
    this->startBuilding();
}

} // namespace Widget


QRectF Widget::ForestItem::boundingRect() const
{
    return QRectF(0,0,this->AreaWidth()+50,this->AreaHeight()+50);

}

void Widget::ForestItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if( this->forestImage() ){
        painter->drawImage(0,0,*this->forestImage());
    }
}

void Widget::ForestItem::updated()
{
//    this->update();
}
