#include "ecosystem.h"

namespace Ecosystem {

Ecosystem::Ecosystem()
{

}

void Ecosystem::append(const Population &population)
{
    this->mEcosystem.push_back(population);
}

} // namespace Ecosystem
