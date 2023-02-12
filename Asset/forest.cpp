#include "forest.h"
#include <QDebug>
#include <QPixmap>
#include "Asset/tree.h"

namespace Assets {
namespace Plant {

Forest::Forest()
{

}

void Forest::populateForest()
{
    Ecosystem::Populator::instance()->Generate<Assets::Tree::Tree>(Assets::Tree::TreeTypeList::instance(),*this);
}


} // namespace Plant
} // namespace Assets
