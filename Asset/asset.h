#ifndef ASSETS_ASSET_H
#define ASSETS_ASSET_H

#include <string>

namespace Assets {

class Asset
{
public:
    Asset();

    std::string assetPath() const;

    void setAssetPath(const std::string &newAssetPath);

    int assetWidth() const;
    void setAssetWidth(int newAssetWidth);

    int assetHeight() const;
    void setAssetHeight(int newAssetHeight);

private:
    std::string mAssetPath;
    int mAssetWidth;
    int mAssetHeight;
};

} // namespace Assets

#endif // ASSETS_ASSET_H
