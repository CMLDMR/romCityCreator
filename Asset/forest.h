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
};

} // namespace Plant
} // namespace Assets

#endif // ASSETS_PLANT_FOREST_H
