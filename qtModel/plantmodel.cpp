#include "plantmodel.h"
#include "plantstandartitem.h"

#include <QStringList>

namespace Qt {

PlantModel::PlantModel(DB *_mDb, QObject *parent)
    : QStandardItemModel{parent},
      Assets::Plant::PlantManager(_mDb)
{

    this->setHorizontalHeaderLabels(QStringList() << "Preview"<<"Width"<<"Height"<<"Type");
    this->updatePlantModel();
}

} // namespace Qt




void Qt::PlantModel::onList(const std::vector<Assets::Plant::Plant> &mlist)
{
    this->removeRows(0,this->rowCount());

    for( const auto &item : mlist ){
        qDebug() << item.AssetName().c_str();
        auto _item = new PlantStandartItem(item);
        auto icon = this->downloadFile(_item->fileOid());
        _item->setIcon(QIcon(icon.c_str()));
        this->insertRow(0,_item);
        this->setItem(0,1,new QStandardItem(QString::number(_item->assetWidth())));
        this->setItem(0,2,new QStandardItem(QString::number(_item->assetHeight())));
        this->setItem(0,3,new QStandardItem(_item->assetTypeName().c_str()));
    }


}

void Qt::PlantModel::updatePlantModel()
{
    this->UpdateList(Assets::Plant::Plant(Assets::AssetType::plant));

}
