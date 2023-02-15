#include "forest.h"
#include <QDebug>
#include <QPixmap>
#include "Asset/tree.h"
#include "Geometry/concavehull.h"
#include <QRandomGenerator>

namespace Assets {
namespace Plant {

Forest::Forest()
{

}

void Forest::populateForest()
{
    Ecosystem::Populator::instance()->Generate<Assets::Tree::Tree>(Assets::Tree::TreeTypeList::instance(),*this);
}

void Forest::populateRandomArea(const int maxWidth, const int maxHeight)
{


    QList<QPointF> list;

    QList<QPolygonF> squareList;


    const int w = 60;
    const int h = 60;

    for( int i = 0 ; i < 20 ; i++ ){

        auto x = QRandomGenerator::global()->generate()%maxWidth;
        auto y = QRandomGenerator::global()->generate()%maxHeight;

        if( squareList.isEmpty() ){
            QPolygonF poly;
            poly.append(QPointF(x-w/2,y-h/2));//topleft
            poly.append(QPointF(x-w/2,y+h/2));//bottomleft
            poly.append(QPointF(x+w/2,y+h/2));//bottomright

            poly.append(QPointF(x+w/2,y-h/2));//topright
            poly.append(QPointF(x-w/2,y-h/2));//topleft



            squareList.append(poly);
            list.push_back(QPointF(x,y));

        }else{

            bool appendable = true;

            for( const auto &item : squareList ){
                if( item.containsPoint(QPointF(x,y),Qt::FillRule::WindingFill ) ){
                    appendable = false;
                    break;
                }
            }

            QPolygonF poly;
            poly.append(QPointF(x-w/2,y-h/2));//topleft
            poly.append(QPointF(x-w/2,y+h/2));//bottomleft
            poly.append(QPointF(x+w/2,y+h/2));//bottomright

            poly.append(QPointF(x+w/2,y-h/2));//topright
            poly.append(QPointF(x-w/2,y-h/2));//topleft

            squareList.append(poly);

            if( appendable ){
                list.push_back(QPointF(x,y));
            }

        }

    }

    auto __list = Geometry::ConcaveHull::instance()->concavehull(list,0.5);
    this->setArea(__list);

//    qDebug() << __list;




    auto _assetList = Assets::Tree::TreeTypeList::instance();

    if( this->getPopulation().size() ) return;

    this->getPopulation().clear();
    for( int j = 0 ; j < this->AreaHeight() ; j++ ){

        for( int i = 0 ; i < this->AreaWidth() ; i++ ){
            auto _xPos = i;
            auto _yPos = j;

            if( this->polygonArea().containsPoint(QPointF(_xPos,_yPos),Qt::FillRule::OddEvenFill ) ){
                auto modY = LandScape::randomGenerator(-20,20);
                auto modX = LandScape::randomGenerator(-20,20);
                if( i%40 == 0 && j%40 == 0 ){
                    auto _random = LandScape::randomGenerator(0,100);
                    auto asset = _assetList.list()[_random%_assetList.list().size()];
                    this->getPopulation().push_back(std::make_tuple(QPointF(i+modX,j+modY),asset));
                }
            }
        }
    }
}



} // namespace Plant
} // namespace Assets
