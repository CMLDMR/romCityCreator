#ifndef QT_PLANTSTANDARTITEM_H
#define QT_PLANTSTANDARTITEM_H

#include <QStandardItem>
#include "Asset/plant.h"

namespace Qt {

class PlantStandartItem : public QStandardItem, public Assets::Plant::Plant
{
public:
    PlantStandartItem(const Assets::Plant::Plant &item);
};

} // namespace Qt

#endif // QT_PLANTSTANDARTITEM_H
