#include "plantstandartitem.h"

namespace Qt {

PlantStandartItem::PlantStandartItem(const Assets::Plant::Plant &item)
    : Assets::Plant::Plant(item.assetType())
{
    this->setDocumentView(item.view());
    this->setText(this->AssetName().c_str());
}

} // namespace Qt
