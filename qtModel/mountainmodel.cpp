#include "mountainmodel.h"
#include <QStandardItem>

namespace Qt {

MountainModel::MountainModel(DB *_mDb, QObject *parent)
    : QStandardItemModel{parent},
      Assets::Terrain::MountainManager(_mDb)
{

    this->setLimit(1000);

    this->setHorizontalHeaderLabels(QStringList() << "Preview"<<"Name"<<"Width"<<"Height"<<"Type");

}

void MountainModel::onList(const std::vector<Assets::Terrain::Mountain> &mlist)
{
    this->removeRows(0,this->rowCount());

    for( const auto &item : mlist ){


        auto icon = this->downloadFile(item.fileOid());

        auto iconItem = new QStandardItem();
        iconItem->setIcon(QIcon(icon.c_str()));
        this->insertRow(0,iconItem);

        auto _item = new QStandardItem(item.assetTypeName().c_str());
        this->setItem(0,1,_item);


        this->setItem(0,2,new QStandardItem(QString::number(item.assetWidth())));
        this->setItem(0,3,new QStandardItem(QString::number(item.assetHeight())));
        this->setItem(0,4,new QStandardItem(item.assetTypeName().c_str()));
    }
}

void MountainModel::updateMountainModel()
{
    this->UpdateList(Assets::Terrain::Mountain());
}

} // namespace Qt
