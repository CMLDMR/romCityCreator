#include "tree.h"



namespace Assets {

Tree::Tree::Tree()
    :Assets::Plant::Plant(Assets::AssetType::plant)
{

}

Tree::Tree &Tree::Tree::operator=(const Tree &other)
{
    return *this;
}










} // namespace Assets
