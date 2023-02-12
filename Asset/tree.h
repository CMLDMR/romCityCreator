#ifndef ASSETS_TREE_H
#define ASSETS_TREE_H

#include "plant.h"


namespace Assets {

namespace Plant{
class Forest;
}

namespace Tree {


class Tree : public Assets::Plant::Plant
{
public:
    Tree( );

    Tree &operator=( const Tree &other);

    Tree( const std::string &path );
};


class TreeTypeList : public Assets::AssetTypeList<Assets::Tree::Tree>{

    inline static TreeTypeList* mPtr;
    inline static std::once_flag flag1;

    static void initSingleton();
    TreeTypeList();
public:


    inline static TreeTypeList &instance(){
        std::call_once(flag1, &initSingleton);
        return *mPtr;
    }



};


}

} // namespace Assets

#endif // ASSETS_TREE_H
