//
//  NormalEnemy.h
//  TowerDefense
//
//  Created by jowu on 15/11/30.
//
//

#ifndef __TowerDefense__NormalEnemy__
#define __TowerDefense__NormalEnemy__

#include <stdio.h>
#include "Enemy.h"

class GnollReaver : public Enemy
{
public:
    CREATE_FUNC(GnollReaver);
    virtual bool init();
};



#endif /* defined(__TowerDefense__NormalEnemy__) */
