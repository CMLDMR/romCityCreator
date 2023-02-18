#ifndef ASSETS_PLANT_H
#define ASSETS_PLANT_H

#include "asset.h"
#include <mongocore/listitem.h>

namespace Assets {

namespace Plant{



class Plant : public Assets::Asset
{

public:
    Plant(const AssetType &_type = AssetType::null);
    Plant( const Plant &other);


};




class PlantManager : public MongoCore::ListItem<Plant>
{
public:
    explicit PlantManager(MongoCore::DB* _mDB);

    // ListItem interface
public:
    virtual void onList(const std::vector<Plant> &mlist) override;
};

}

} // namespace Assets

#endif // ASSETS_PLANT_H
