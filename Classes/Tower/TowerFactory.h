#ifndef TOWERFACTORY_H
#define TOWERFACTORY_H

#include "CommonDef.h"
#include "Tower/Tower.h"

class TowerFactory
{
public:
    static Tower* create(TowerID id);
};

#endif // TOWERFACTORY_H
