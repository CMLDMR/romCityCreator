#include "tree.h"

namespace Assets {

Tree::Tree::Tree(const TreeType &_treeType)
    :Assets::Plant::Plant(Assets::Plant::PlantType::tree),
      mTreeType(_treeType)
{

    setTreeTypePath(mTreeType);


}

void Tree::Tree::setTreeTypePath(const TreeType &_type)
{

    switch (_type) {
    case TreeType::akasya:
        setAssetPath("://bin/asset/tree/tree1.png");
        break;
    default:
        break;
    }

}

} // namespace Assets
