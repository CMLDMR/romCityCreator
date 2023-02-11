#ifndef ASSETS_PLANT_FOREST_H
#define ASSETS_PLANT_FOREST_H
#include "Asset/area.h"

namespace Assets {
namespace Plant {

class Forest : public LandScape::Area
{
public:
    Forest();

    void populateEcosystem();

    QList<QPointF> plantPoints() const;

private:
    QList<QPointF> mPlantPoints;

};

} // namespace Plant
} // namespace Assets

#endif // ASSETS_PLANT_FOREST_H
