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
    slot->setSlotId(0);
    addChild(slot);
    m_towerSlots.push_back(slot);
    
    
    TowerSlot* slot1 = TowerSlot::create();
    slot1->setPosition(800, 300);
    slot1->setSlotId(1);
    addChild(slot1);
    m_towerSlots.push_back(slot1);



    TowerSlot* slot3 = TowerSlot::create();
    slot3->setPosition(800, 300);
    slot3->setSlotId(2);
    addChild(slot3);
    m_towerSlots.push_back(slot3);
}
