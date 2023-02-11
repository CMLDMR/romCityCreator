#include "asset.h"
#include <QPixmap>


namespace Assets {

Asset::Asset()
{

}

std::string Asset::assetPath() const
{
    return mAssetPath;
}

void Asset::setAssetPath(const std::string &newAssetPath)
{
    mAssetPath = newAssetPath;
    QPixmap pixmap(newAssetPath.c_str());
    this->setAssetWidth(pixmap.width());
    this->setAssetHeight(pixmap.height());
}

int Asset::assetWidth() const
{
    return mAssetWidth;
}

void Asset::setAssetWidth(int newAssetWidth)
{
    mAssetWidth = newAssetWidth;
}

int Asset::assetHeight() const
{
    return mAssetHeight;
}

void Asset::setAssetHeight(int newAssetHeight)
{
    mAssetHeight = newAssetHeight;
}

} // namespace Assets
