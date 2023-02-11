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

    painter->drawText(0,0,"Forest Area");
    painter->drawText(-totalWidth/2,-totalHeight+20,"Rendering Area");

    painter->setPen(QPen(Qt::GlobalColor::red));
    painter->drawRect(this->boundingRect());
    painter->setPen(QPen(Qt::GlobalColor::green));
    painter->drawRect(QRectF(0,0,this->AreaWidth(),this->AreaHeight()));

    painter->setPen(QPen(Qt::GlobalColor::black));
    painter->drawPolygon(polygonArea());

    this->populateEcosystem();

//    totalWidth = 0;
//    totalHeight = 0;

    for( const auto &[point,width,height,path] : this->plantList() ){
        painter->drawRect(point.x(),point.y(),3,3);
        qDebug() << path.c_str();
        painter->drawPixmap(point.x()-width/2,point.y()-height,QPixmap(path.c_str()));
        totalWidth = totalWidth < width ? width : totalWidth;
        totalHeight = totalHeight < height ? height : totalHeight;
    }

//    this->update();
}
