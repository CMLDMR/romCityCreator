#ifndef ASSETS_ASSET_H
#define ASSETS_ASSET_H

#include <string>
#include <tuple>
#include <memory>
#include <mutex>

#include <QDebug>
#include <QList>
#include <QVector>

#include <mongocore/item.h>


namespace Assets {


enum class AssetType{
    null = 0,
    rock,
    mountain,
    plant
};


namespace AssetPropertiesKey{
inline const std::string type{"type"};
inline const std::string name{"assetname"};
inline const std::string width{"width"};
inline const std::string height{"height"};
inline const std::string fileOid{"fileOid"};

}



class Asset : public MongoCore::Item
{
public:
    Asset(const AssetType &type, const std::string &collection);

    std::string assetPath() const;

    int assetWidth() const;
    void setAssetWidth(int newAssetWidth);

    int assetHeight() const;
    void setAssetHeight(int newAssetHeight);

    AssetType assetType() const;
    std::string assetTypeName() const;

    void setAssetName( const std::string &assetName ) ;
    std::string AssetName() const;

    void setFileOid( const bsoncxx::types::bson_value::value &value );
    std::string fileOid() const;



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
