#ifndef ASSETS_TREE_H
#define ASSETS_TREE_H

#include "plant.h"


namespace Assets {

namespace Plant{
class Forest;
}

namespace Tree {

namespace Key{

}


namespace Properties{


}


class Tree : public Assets::Plant::Plant
{
public:
    Tree( );
    Tree &operator=( const Tree &other);


};





}

} // namespace Assets

#endif // ASSETS_TREE_H
