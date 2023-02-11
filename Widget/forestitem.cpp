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

    return QRectF(-100,-100,this->AreaWidth()+200,this->AreaHeight()+200);
}

void Widget::ForestItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Assets::Tree::Tree *tree;

    tree    = new Assets::Tree::Tree(Assets::Tree::TreeType::pine);



    painter->drawText(0,0,"Forest Area");
    painter->drawText(-40,-35,"Rendering Area");

    painter->setPen(QPen(Qt::GlobalColor::red));
    painter->drawRect(this->boundingRect());
    painter->setPen(QPen(Qt::GlobalColor::green));
    painter->drawRect(QRectF(0,0,this->AreaWidth(),this->AreaHeight()));

    painter->setPen(QPen(Qt::GlobalColor::black));
    painter->drawPolygon(polygonArea());

    QPixmap treePixmap(tree->assetPath().c_str());
    this->populateEcosystem();


//    for( const auto &point : this->plantPoints() ){
//        painter->drawRect(point.x(),point.y(),3,3);

//        painter->drawPixmap(point.x()-tree->assetWidth()/2,point.y()-tree->assetHeight(),treePixmap);
//    }

    for( const auto &[point,width,height,path] : this->plantList() ){
        painter->drawRect(point.x(),point.y(),3,3);

        painter->drawPixmap(point.x()-width/2,point.y()-height,QPixmap(path.c_str()));
    }

}
