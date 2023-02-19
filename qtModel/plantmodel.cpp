#include "plantmodel.h"

#include <QStringList>

namespace Qt {

PlantModel::PlantModel(DB *_mDb, QObject *parent)
    : QStandardItemModel{parent},
      Assets::Plant::PlantManager(_mDb)
{

    this->setLimit(1000);

    this->setHorizontalHeaderLabels(QStringList() << "Preview"<<"Name"<<"Width"<<"Height"<<"Type");
//    this->updatePlantModel();
}

} // namespace Qt




void Qt::PlantModel::onList(const std::vector<Assets::Plant::Plant> &mlist)
{
    this->removeRows(0,this->rowCount());

    for( const auto &item : mlist ){


        auto icon = this->downloadFile(item.fileOid());

        auto iconItem = new QStandardItem();
        iconItem->setIcon(QIcon(icon.c_str()));
        this->insertRow(0,iconItem);

        auto _item = new PlantStandartItem(item);
        this->setItem(0,1,_item);


        this->setItem(0,2,new QStandardItem(QString::number(_item->assetWidth())));
        this->setItem(0,3,new QStandardItem(QString::number(_item->assetHeight())));
        this->setItem(0,4,new QStandardItem(_item->assetTypeName().c_str()));
    }


}

void Qt::PlantModel::updatePlantModel()
{
    this->UpdateList(Assets::Plant::Plant(Assets::AssetType::plant));

}
