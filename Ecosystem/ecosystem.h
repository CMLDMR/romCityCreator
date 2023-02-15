#ifndef ECOSYSTEM_ECOSYSTEM_H
#define ECOSYSTEM_ECOSYSTEM_H

#include "Ecosystem/population.h"

//TODO: Bütün Populasyonlar Eklenebilecek

namespace Ecosystem {

class Ecosystem
{
public:
    Ecosystem();

    void append( const Population &population );

    const QList<Population> &getPopulations() const{
        return mEcosystem;
    }

private:
    QList<Population> mEcosystem;
};

} // namespace Ecosystem

#endif // ECOSYSTEM_ECOSYSTEM_H
