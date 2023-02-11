#ifndef ASSETS_TREE_H
#define ASSETS_TREE_H

#include "plant.h"

namespace Assets {

namespace Plant{
class Forest;
}

namespace Tree {

enum class TreeType{
    akasya,
    pine
};

class Tree : public Assets::Plant::Plant
{
public:
    Tree(const TreeType &_treeType );


private:
    TreeType mTreeType;

    friend class Assets::Plant::Forest;

    void setTreeTypePath(const TreeType &_type);

};

}

} // namespace Assets

#endif // ASSETS_TREE_H
