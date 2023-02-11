#include "forest.h"
#include <QDebug>

namespace Assets {
namespace Plant {

Forest::Forest()
{

}

void Forest::populateEcosystem()
{
    qDebug() << "Populating...";
    if( mPlantPoints.size() ) return;
    std::uint64_t treeCount{0};
    std::uint64_t areaCount{0};
    std::uint64_t outsideAreaCount{0};
    std::uint64_t totalAreaCount{0};


    mPlantList.clear();
    for( int j = 0 ; j < this->AreaHeight() ; j++ ){

        for( int i = 0 ; i < this->AreaWidth() ; i++ ){
            auto _xPos = i;
            auto _yPos = j;

            if( polygonArea().containsPoint(QPointF(_xPos,_yPos),Qt::FillRule::OddEvenFill ) ){
                areaCount++;
                auto modY = LandScape::randomGenerator(-10,10);
                auto modX = LandScape::randomGenerator(-10,10);
                if( i%30 == 0 && j%30 == 0 ){
                    mPlantPoints.push_back(QPointF(i+modX,j+modY));
                    treeCount++;
                    auto _random = LandScape::randomGenerator(0,255);
                    if( _random%2 == 0 ){
                        mPlantList.push_back(std::make_tuple(QPointF(i+modX,j+modY),49,94,"://bin/asset/tree/tree1.png"));
                    }else{
                        mPlantList.push_back(std::make_tuple(QPointF(i+modX,j+modY),50,58,"://bin/asset/tree/tree2.png"));
                    }
                }
            }else{
                outsideAreaCount++;
            }
            totalAreaCount++;
        }
    }

}

QList<QPointF> Forest::plantPoints() const
{
    return mPlantPoints;
}

QList<std::tuple<QPointF, int, int, std::string> > Forest::plantList() const
{
    return mPlantList;
}

} // namespace Plant
} // namespace Assets
