#ifndef ASSETS_TERAIN_MOUNTAIN_H
#define ASSETS_TERAIN_MOUNTAIN_H

#include "Asset/area.h"
#include "asset.h"
#include <mongocore/listitem.h>

namespace Assets {
namespace Terrain {

class Mountain : public Assets::Asset, public LandScape::Area
{
public:
    Mountain();
    Mountain( const Mountain &other);

};



class MountainManager : public MongoCore::ListItem<Mountain>
{
public:
    explicit MountainManager(MongoCore::DB* _mDB);

    // ListItem interface
public:
    virtual void onList(const std::vector<Mountain> &mlist) override;
};






} // namespace Terain
} // namespace Assets

#endif // ASSETS_TERAIN_MOUNTAIN_H
