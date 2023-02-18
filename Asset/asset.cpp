#include "asset.h"


namespace Assets {

Asset::Asset(const AssetType &type,const std::string &collection)
    :MongoCore::Item(collection)
{
    this->append(AssetPropertiesKey::type,bsoncxx::types::b_int32{static_cast<std::int32_t>(type)});
}

std::string Asset::assetPath() const
{
    return mAssetPath;
}

int Asset::assetWidth() const
{
    auto val = this->element(AssetPropertiesKey::width);
    if( val ){
        return val.value().view().get_int32().value;
    }
    return 0;
}

void Asset::setAssetWidth(int newAssetWidth)
{
    this->append(AssetPropertiesKey::width,bsoncxx::types::b_int32{newAssetWidth});
}

int Asset::assetHeight() const
{
    auto val = this->element(AssetPropertiesKey::height);
    if( val ){
        return val.value().view().get_int32().value;
    }
    return 0;
}

void Asset::setAssetHeight(int newAssetHeight)
{
    this->append(AssetPropertiesKey::height,bsoncxx::types::b_int32{newAssetHeight});
}

AssetType Asset::assetType() const
{
    auto val = this->element(AssetPropertiesKey::type);
    if( val ){
        return static_cast<AssetType>(val.value().view().get_int32().value);
    }
    return AssetType::null;
}

std::string Asset::assetTypeName() const
{
    switch (this->assetType()) {
    case AssetType::mountain:
        return "mountain";
        break;
    case AssetType::plant:
        return "plant";
        break;
    case AssetType::null:
        return "null";
        break;
    case AssetType::rock:
        return "rock";
        break;
    default:
        return "null";
        break;
    }
}

void Asset::setAssetName(const std::string &assetName)
{
    this->append(AssetPropertiesKey::name,assetName);
}

std::string Asset::AssetName() const
{
    auto val = this->element(AssetPropertiesKey::name);
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

void Asset::setFileOid(const bsoncxx::types::bson_value::value &value)
{
    this->append(AssetPropertiesKey::fileOid,value);
}

std::string Asset::fileOid() const
{
    auto val = this->element(AssetPropertiesKey::fileOid);
    if( val ){
        return val.value().view().get_oid().value.to_string();
    }
    return "";
}



} // namespace Assets
