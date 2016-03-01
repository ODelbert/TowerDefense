//
//  Level1.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/16.
//
//

#include "Stage1.h"
#include "CommonDef.h"
#include "Base/WaveManager.h"

bool Stage1::init()
{
    BattleField::init();
    loadLevel(1, 1);
    return true;
}