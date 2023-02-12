#ifndef ECOSYSTEM_ECOSYSTEM_H
#define ECOSYSTEM_ECOSYSTEM_H

#include "Ecosystem/population.h"

namespace Ecosystem {

class Ecosystem
{
public:
    Ecosystem();

private:
    QList<Population> mEcosystem;
};

} // namespace Ecosystem

#endif // ECOSYSTEM_ECOSYSTEM_H
