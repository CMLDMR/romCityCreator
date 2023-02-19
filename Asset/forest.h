#ifndef ASSETS_PLANT_FOREST_H
#define ASSETS_PLANT_FOREST_H

#include "Ecosystem/population.h"
#include "Asset/plant.h"

namespace Assets {
namespace Plant {

class Forest : public Ecosystem::Population, public Assets::Plant::PlantManager
{
public:
    Forest();

    void populateForest();

    void populateRandomArea( const int maxWidth = 500 , const int maxHeight = 500 );


//    Assets::Plant::PlantManager* mPlantManager;
};

} // namespace Plant
} // namespace Assets

#endif // ASSETS_PLANT_FOREST_H
