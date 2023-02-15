#include "area.h"

namespace LandScape {

Area::Area()
{

}

void Area::setArea(const QList<QPointF> &newArea)
{

    int minx = INT32_MAX;
    for( const auto &item : newArea ){
        minx = minx > item.x() ? item.x() : minx;
    }
    int miny = INT32_MAX;
    for( const auto &item : newArea ){
        miny = miny > item.y() ? item.y() : miny;
    }

    this->mArea.clear();
    for( const auto &point : newArea ){
        this->mArea.push_back(QPointF(point.x()-minx,point.y()-miny));
    }
    this->mPolygonArea.append(this->mArea);
}

QList<QPointF> Area::getArea() const
{
    return this->mArea;
}

QPolygonF Area::polygonArea() const
{
    return mPolygonArea;
}

QPointF Area::getPosition() const
{
    return QPointF(xPos,yPos);
}

int Area::AreaWidth() const
{
    int minx = INT32_MAX;
    int maxx = 0;
    for( const auto &item : this->mArea ){
        minx = minx > item.x() ? item.x() : minx;
        maxx = maxx < item.x() ? item.x() : maxx;
    }

    return maxx-minx;
}

int Area::AreaHeight() const
{
    int miny = INT32_MAX;
    int maxy = 0;
    for( const auto &item : this->mArea ){
        miny = miny > item.y() ? item.y() : miny;
        maxy = maxy < item.y() ? item.y() : maxy;
    }

    return maxy-miny;
}

int Area::getYPos() const
{
    return yPos;
}

void Area::setYPos(int newYPos)
{
    yPos = newYPos;
}

int Area::getXPos() const
{
    return xPos;
}

void Area::setXPos(int newXPos)
{
    xPos = newXPos;
}


} // namespace LandScape
