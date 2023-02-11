#ifndef ASSETS_PLANT_FOREST_H
#define ASSETS_PLANT_FOREST_H
#include "Asset/area.h"
#include <tuple>

namespace Assets {
namespace Plant {

class Forest : public LandScape::Area
{
public:
    Forest();

    void populateEcosystem();

    QList<QPointF> plantPoints() const;

    QList<std::tuple<QPointF, int, int, std::string> > plantList() const;

private:
    QList<QPointF> mPlantPoints;

    QList<std::tuple<QPointF,int,int,std::string>> mPlantList;

};

} // namespace Plant
} // namespace Assets

#endif // ASSETS_PLANT_FOREST_H
