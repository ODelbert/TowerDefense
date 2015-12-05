//
//  EnemyFactory.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/30.
//
//

#include "EnemyFactory.h"
#include "CommonEnemy.h"
#include "TalentedEnemy.h"
#include "FlyingEnemy.h"
#include "RunningEnemy.h"

Enemy* EnemyFactory::create(EnemyID id)
{
    switch (id) {
        case EnemyID_Gnoll_Reaver:
            return GnollReaver::create();
            break;
        case EnemyID_Gnoll_Burner:
            return GnollBurner::create();
        default:
            break;
    }

	return NULL;
}