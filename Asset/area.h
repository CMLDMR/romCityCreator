#ifndef LANDSCAPE_AREA_H
#define LANDSCAPE_AREA_H

#include <QList>
#include <QPointF>
#include <QPolygonF>
#include <random>

namespace LandScape {

[[maybe_unused]]
static int randomGenerator( const int &min, const int &max ){

    // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(min, max);
    int mean = uniform_dist(e1);
    return mean;

}

class Area
{
public:
    Area();

    void setArea(const QList<QPointF> &newArea);
    QList<QPointF> getArea() const;
    QPolygonF polygonArea() const;

    QPointF getPosition() const;

    int AreaWidth() const;
    int AreaHeight() const;


    int getYPos() const;
    void setYPos(int newYPos);

    int getXPos() const;
    void setXPos(int newXPos);

private:
    QList<QPointF> mArea;
    QPolygonF mPolygonArea;

    int xPos;
    int yPos;
};




//TODO Item Distrubution class

} // namespace LandScape

#endif // LANDSCAPE_AREA_H
