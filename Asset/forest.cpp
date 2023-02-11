#include "forest.h"
#include <QDebug>
#include <QPixmap>

namespace Assets {
namespace Plant {

Forest::Forest()
{

    mAssetPathList.push_back("://bin/asset/tree/tree1.png");
    mAssetPathList.push_back("://bin/asset/tree/tree2.png");
    mAssetPathList.push_back("://bin/asset/tree/tree3.png");
    mAssetPathList.push_back("://bin/asset/tree/tree4.png");
    mAssetPathList.push_back("://bin/asset/tree/tree5.png");
    mAssetPathList.push_back("://bin/asset/tree/tree6.png");
    mAssetPathList.push_back("://bin/asset/tree/tree7.png");
    mAssetPathList.push_back("://bin/asset/tree/tree8.png");
    mAssetPathList.push_back("://bin/asset/tree/tree9.png");

}

void Forest::populateEcosystem()
{
    qDebug() << "Populating...";
    if( mPlantList.size() ) return;
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
                auto modY = LandScape::randomGenerator(-20,20);
                auto modX = LandScape::randomGenerator(-20,20);
                if( i%25 == 0 && j%25 == 0 ){

                    treeCount++;
                    auto _random = LandScape::randomGenerator(0,100);

                    auto selectedPath = mAssetPathList[_random%mAssetPathList.size()];
                    QPixmap pixmap(selectedPath);

                    mPlantList.push_back(std::make_tuple(QPointF(i+modX,j+modY),pixmap.width(),pixmap.height(),selectedPath.toStdString()));


                }
            }else{
                outsideAreaCount++;
            }
            totalAreaCount++;
        }
    }


//    for( const auto &point : this->polygonArea() ){
//        auto _random = LandScape::randomGenerator(0,255);
//        if( _random%2 == 0 ){
//            mPlantList.push_back(std::make_tuple(point,100,93,"://bin/asset/tree/tree1.png"));
//        }else{
//            mPlantList.push_back(std::make_tuple(point,120,100,"://bin/asset/tree/tree2.png"));
//        }
//    }


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
