#include "tree.h"

namespace Assets {

Tree::Tree::Tree()
    :Assets::Plant::Plant(Assets::AssetType::tree)
{



}

Tree::Tree &Tree::Tree::operator=(const Tree &other)
{
    this->setAssetPath(other.assetPath()); return *this;
}

Tree::Tree::Tree(const std::string &path)
    :Assets::Plant::Plant(Assets::AssetType::tree)
{
    this->setAssetPath(path);
}

void Tree::TreeTypeList::initSingleton()
{
    mPtr = new TreeTypeList();
}

Tree::TreeTypeList::TreeTypeList()
{

    this->append(Tree("://bin/asset/tree/tree1.png"));
    this->append(Tree("://bin/asset/tree/tree2.png"));
    this->append(Tree("://bin/asset/tree/tree3.png"));
    this->append(Tree("://bin/asset/tree/tree4.png"));
    this->append(Tree("://bin/asset/tree/tree5.png"));
    this->append(Tree("://bin/asset/tree/tree6.png"));
    this->append(Tree("://bin/asset/tree/tree7.png"));
    this->append(Tree("://bin/asset/tree/tree8.png"));
    this->append(Tree("://bin/asset/tree/tree9.png"));

}



} // namespace Assets
