#include "mountain.h"

#include <QDebug>

namespace Assets {
namespace Terrain {

Mountain::Mountain()
    :Assets::Asset(AssetType::mountain,"Mountain")
{
    qDebug() << "Mountain";


}

Mountain::Mountain(const Mountain &other)
    :Assets::Asset(other.assetType(),"Mountain")
{
    this->setDocumentView(other.view());

}

MountainManager::MountainManager(DB *_mDB)
    :MongoCore::ListItem<Mountain>(_mDB)
{

}

void MountainManager::onList(const std::vector<Mountain> &mlist)
{

}

} // namespace Terain
} // namespace Assets
