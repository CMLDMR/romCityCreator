#include "forest.h"
#include <QDebug>
#include <QPixmap>
#include "Asset/tree.h"
#include "Geometry/concavehull.h"
#include <QRandomGenerator>
#include <QtMath>
#include <QtAlgorithms>

#include <algorithm>
#include<functional>


//TODO: Düzgün Bir Yere QPOintF operator taşınacak

static bool compare( const QPointF &a , const QPointF &b){
    return a.y() < b.y();
}

namespace Assets {
namespace Plant {

Forest::Forest()
{

}

void Forest::populateForest()
{
    Ecosystem::Populator::instance()->Generate<Assets::Tree::Tree>(Assets::Tree::TreeTypeList::instance(),*this);
}

//TODO: Padding Forest Eklenecek
void Forest::populateRandomArea(const int maxWidth, const int maxHeight)
{


    QList<QPointF> list;
    QList<QPointF> list2;

    QList<QPolygonF> squareList;

    int modd = QRandomGenerator::global()->generate()%200;


    const int w = 30;
    const int h = 30;
    const int offset = 200;

    //TODO: Düşük Polygon Sayısı ile Metre Kare Başına Ağaç Hesaplanacak
    for( int i = 0 ; i < 10/*qSqrt(maxHeight*maxWidth)/4*/ ; i++ ){

        if( i % 10 == 0 ){
            modd = QRandomGenerator::global()->generate()%offset;
        }


        auto x = QRandomGenerator::global()->generate()%(maxWidth-offset)+modd;
        auto y = QRandomGenerator::global()->generate()%(maxHeight-offset)+modd;
        list2.push_back({static_cast<qreal>(x),static_cast<qreal>(y)});

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


    std::sort(list2.begin(), list2.end(),compare);

//    for( const auto &point : list2 ){
//        auto asset = _assetList.list().last();
//        this->getPopulation().push_back(std::make_tuple(QPointF(point.x(),point.y()),asset));
//    }


    for( const auto &point : list2 ){
        auto _random = LandScape::randomGenerator(0,10000);
        auto asset = _assetList.list()[_random%(_assetList.list().size())];
        this->getPopulation().push_back(std::make_tuple(QPointF(point.x(),point.y()),asset));
    }
    return;

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
