#ifndef ASSETS_PLANT_FOREST_H
#define ASSETS_PLANT_FOREST_H

#include "Ecosystem/population.h"

namespace Assets {
namespace Plant {

class Forest : public Ecosystem::Population
{
public:
    Forest();

    void populateForest();

    void populateRandomArea( const int maxWidth = 500 , const int maxHeight = 500 );
};

} // namespace Plant
} // namespace Assets

#endif // ASSETS_PLANT_FOREST_H
