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
    return QRectF(-40,-60,this->AreaWidth()+40+20,this->AreaHeight()+60);
}

void Widget::ForestItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawText(0,0,"Forest Area");
    painter->drawText(-40,-40,"Rendering Area");

    painter->setPen(QPen(Qt::GlobalColor::red));
    painter->drawRect(this->boundingRect());
    painter->setPen(QPen(Qt::GlobalColor::green));
    painter->drawRect(QRectF(0,0,this->AreaWidth(),this->AreaHeight()));

    painter->setPen(QPen(Qt::GlobalColor::black));
    painter->drawPolygon(polygonArea());

    Assets::Tree::Tree *tree = new Assets::Tree::Tree(Assets::Tree::TreeType::akasya);
    QPixmap treePixmap(tree->assetPath().c_str());
    this->populateEcosystem();

    for( const auto &point : this->plantPoints() ){
        painter->drawRect(point.x(),point.y(),3,3);
        painter->drawPixmap(point.x()-tree->assetWidth()/2,point.y()-tree->assetHeight(),treePixmap);
    }

}
