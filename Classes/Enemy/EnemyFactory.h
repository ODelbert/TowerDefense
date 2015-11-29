//
//  EnemyFactory.h
//  TowerDefense
//
//  Created by jowu on 15/11/30.
//
//

#ifndef __TowerDefense__EnemyFactory__
#define __TowerDefense__EnemyFactory__

#include "cocos2d.h"
#include "Enemy.h"

class EnemyFactory
{
public:
    static Enemy* create(EnemyID id);
};

#endif /* defined(__TowerDefense__EnemyFactory__) */
