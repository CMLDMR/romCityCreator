#include "plant.h"

namespace Assets {

namespace Plant{

Plant::Plant(const AssetType &_type)
    :Assets::Asset(_type,"Plant")
{

}

Plant::Plant(const Plant &other)
    :Assets::Asset(other.assetType(),"Plant")
{
    this->setDocumentView(other.view());
}




PlantManager::PlantManager(DB *_mDB)
    :MongoCore::ListItem<Plant>(_mDB)
{

}

}


} // namespace Assets


void Assets::Plant::PlantManager::onList(const std::vector<Plant> &mlist)
{



}
