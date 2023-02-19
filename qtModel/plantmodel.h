#ifndef QT_PLANTMODEL_H
#define QT_PLANTMODEL_H

#include <QStandardItemModel>
#include "Asset/plant.h"
#include <mongocore/db.h>

namespace Qt {

class PlantModel : public QStandardItemModel, public Assets::Plant::PlantManager
{
    Q_OBJECT
public:
    explicit PlantModel( MongoCore::DB* _mDb , QObject *parent = nullptr );


Q_SIGNALS:



    // PlantManager interface
public:
    virtual void onList( const std::vector<Assets::Plant::Plant> &mlist ) override;

    void updatePlantModel();
};

} // namespace Qt

#endif // QT_PLANTMODEL_H
