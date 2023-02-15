#include "forestitem.h"
#include <QPainter>
#include <QTextItem>
#include "Asset/tree.h"

namespace Widget {

ForestItem::ForestItem()
{

}

} // namespace Widget


QRectF Widget::ForestItem::boundingRect() const
{
    return QRectF(-totalWidth/2,-totalHeight,this->AreaWidth()+totalWidth,this->AreaHeight()+totalHeight);
}

void Widget::ForestItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for( const auto &[point,asset] : this->getPopulation() ){
        painter->drawPixmap(point.x()-asset.assetWidth()/2,point.y()-asset.assetHeight(),QPixmap(asset.assetPath().c_str()));
        totalWidth = totalWidth < asset.assetWidth() ? asset.assetWidth() : totalWidth;
        totalHeight = totalHeight < asset.assetHeight() ? asset.assetHeight() : totalHeight;
    }
}
