#ifndef ASSETS_ASSET_H
#define ASSETS_ASSET_H

#include <string>
#include <tuple>
#include <memory>
#include <mutex>

#include <QDebug>
#include <QList>
#include <QVector>


namespace Assets {

enum class AssetType{
    soil = 0,
    rock,
    mountain,

    plant = 1000,
    tree
};




class Asset
{
public:
    Asset(const AssetType &type);

    std::string assetPath() const;

    void setAssetPath(const std::string &newAssetPath);

    int assetWidth() const;
    void setAssetWidth(int newAssetWidth);

    int assetHeight() const;
    void setAssetHeight(int newAssetHeight);

    AssetType assetType() const;

private:
    std::string mAssetPath;
    int mAssetWidth;
    int mAssetHeight;

    AssetType mAssetType;
};





template<typename T>
class AssetTypeList{
public:
    AssetTypeList& append(const T &item ){
        mList.append(item);
        return *this;
    }

    inline const QVector<T> &list() const {
        return mList;
    }

private:
    QVector<T> mList;


};

} // namespace Assets

#endif // ASSETS_ASSET_H
