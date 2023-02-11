#ifndef ASSETS_PLANT_H
#define ASSETS_PLANT_H

#include "asset.h"

namespace Assets {

namespace Plant{

enum class PlantType{
    tree = 0
};

class Plant : public Assets::Asset
{

public:
    Plant(const PlantType &_type);


private:
    PlantType mType;
};



}

} // namespace Assets

#endif // ASSETS_PLANT_H
