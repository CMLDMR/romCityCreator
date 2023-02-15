#ifndef ECOSYSTEM_POPULATION_H
#define ECOSYSTEM_POPULATION_H

#include "Asset/area.h"
#include "Asset/asset.h"

#include <tuple>
#include <mutex>
#include <memory>

#include <QList>
#include <QPointF>



namespace Ecosystem {

class Population : public LandScape::Area
{
public:
    Population();

    QList<std::tuple<QPointF,Assets::Asset>> &getPopulation(){ return mPopulation;}
private:
    QList<std::tuple<QPointF,Assets::Asset>> mPopulation;

};


class Populator{


    inline static Populator* mPtr;
    inline static std::once_flag flag1;

    static void initSingleton(){
        mPtr = new Populator();
    }

    Populator(){}

public:

    inline static Populator *instance(){
        std::call_once(flag1, &initSingleton);
        return mPtr;
    }

    template<typename T>
    Population& Generate(const Assets::AssetTypeList<T> &_assetList, Population &_mPopulation){

        if( _mPopulation.getPopulation().size() ) return _mPopulation;

        _mPopulation.getPopulation().clear();
        for( int j = 0 ; j < _mPopulation.AreaHeight() ; j++ ){

            for( int i = 0 ; i < _mPopulation.AreaWidth() ; i++ ){
                auto _xPos = i;
                auto _yPos = j;

                if( _mPopulation.polygonArea().containsPoint(QPointF(_xPos,_yPos),Qt::FillRule::OddEvenFill ) ){
                    auto modY = LandScape::randomGenerator(-10,10);
                    auto modX = LandScape::randomGenerator(-10,10);
                    if( i%20 == 0 && j%20 == 0 ){
                        auto _random = LandScape::randomGenerator(0,100);
                        auto asset = _assetList.list()[_random%_assetList.list().size()];
                        _mPopulation.getPopulation().push_back(std::make_tuple(QPointF(i+modX,j+modY),asset));
                    }
                }
            }
        }

        return _mPopulation;
    }


};



} // namespace Ecosystem

#endif // ECOSYSTEM_POPULATION_H
