#ifndef ASSETS_PLANT_FOREST_H
#define ASSETS_PLANT_FOREST_H

#include "Ecosystem/population.h"
#include "Asset/plant.h"

class QThread;
class QImage;


namespace Assets {
namespace Plant {

class Forest : public Ecosystem::Population, public Assets::Plant::PlantManager
{
public:
    Forest();

    void populateForest();

    void populateRandomArea( const int maxWidth = 500 , const int maxHeight = 500 );

    const std::vector<float> &noiseData() const;

    void startBuilding();

    virtual void updated() {}

    QImage *forestImage() const;

private:
    std::vector<float> mNoiseData;

    void generateNoise();

    QThread* mThread;

    void forestBuilder();
    QImage *mForestImage = nullptr;


};

} // namespace Plant
} // namespace Assets

#endif // ASSETS_PLANT_FOREST_H
