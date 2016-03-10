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
#include "Sprite/TowerSlot.h"

bool Stage1::init()
{
    BattleField::init();
    loadLevel(1, 1);
    addTowerSlots();
    return true;
}

void Stage1::addTowerSlots()
{
    TowerSlot* slot = TowerSlot::create();
    slot->setPosition(400, 300);
    addChild(slot);
    m_towerSlots.push_back(slot);
}