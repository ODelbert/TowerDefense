//
//  TalentEnemy.h
//  TowerDefense
//
//  Created by jowu on 15/11/30.
//
//

#ifndef __TowerDefense__TalentEnemy__
#define __TowerDefense__TalentEnemy__

#include <stdio.h>
#include "Enemy.h"


class RedCap : public Enemy
{
public:
    CREATE_FUNC(RedCap);
    virtual bool init();
};

class GnollBurner : public Enemy
{
public:
    CREATE_FUNC(GnollBurner);
    virtual bool init();
};

#endif /* defined(__TowerDefense__TalentEnemy__) */
