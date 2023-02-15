#ifndef GEOMETRY_CONCAVEHULL_H
#define GEOMETRY_CONCAVEHULL_H

#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>
#include <vector>
#include <memory>
#include <mutex>

#include <QPointF>

#include <QPointF>
#include <QList>



namespace Geometry {

class ConcaveHull
{

    inline static ConcaveHull* mPtr;
    inline static std::once_flag flag1;

    static void initSingleton(){
        mPtr = new ConcaveHull();
    }

public:
    ConcaveHull();

    inline static ConcaveHull *instance(){
        std::call_once(flag1, &initSingleton);
        return mPtr;
    }

    QList<QPointF> concavehull(const QList<QPointF>& coords, double chi_factor=0.1);
};

} // namespace Geometry

#endif // GEOMETRY_CONCAVEHULL_H
