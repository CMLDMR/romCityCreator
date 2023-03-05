#ifndef QT_MOUNTAINMODEL_H
#define QT_MOUNTAINMODEL_H

#include <QStandardItemModel>
#include <mongocore/db.h>

#include "Asset/mountain.h"

namespace Qt {

class MountainModel : public QStandardItemModel, public Assets::Terrain::MountainManager
{
public:
    explicit MountainModel(MongoCore::DB* _mDb , QObject *parent = nullptr);

    // PlantManager interface
public:
    virtual void onList( const std::vector<Assets::Terrain::Mountain> &mlist ) override;

    void updateMountainModel();
};

} // namespace Qt

#endif // QT_MOUNTAINMODEL_H
