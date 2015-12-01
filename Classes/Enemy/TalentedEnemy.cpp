//
//  TalentEnemy.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/30.
//
//

#include "TalentedEnemy.h"
#include "Configuration/GameData.h"

bool RedCap::init()
{
    Enemy::initWithEnemyId(EnemyID_Redcap);
    return true;
}