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
#include "Sprite/WaveFalg.h"
#include "Sprite/RangeCircle.h"
#include "Enemy/EnemyFactory.h"

bool Stage1::init()
{
    BattleField::init();
    loadLevel(1, 1);
    addTowerSlots();

    auto sp = Sprite::createWithSpriteFrameName("ico_sell_0002.png");
    sp->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(AID_ENEMY_ARACHNOMANCER_ATTACK))));
    addChild(sp);
    sp->setPosition(100, 100);

    auto obj = EnemyFactory::create(EnemyID_Redcap);
    obj->setPosition(400, 300);
    addChild(obj);
    obj->runAction(MoveTo::create(1.0, Vec2(400, 400)));

    return true;
}

void Stage1::addTowerSlots()
{
    // Test!!
    addTowerSlot(0, Vec2(400, 300));
//    addTowerSlot(1, Vec2(600, 300));
//    
//    WaveFlag* wf = WaveFlag::create(WaveFlag::Normal, 10);
//    wf->setPosition(100, 400);
//    addChild(wf);

    // Test speed
#if 0
    for (int i = 0; i < SpeedType_VeryFast; ++i) {
        auto monster = EnemyFactory::create(EnemyID_Redcap);
        monster->setSpeed(static_cast<SpeedType>(i));
        m_mapSprite->addChild(monster);

        monster->sendToBattle(WaveManager::getInstance()->getPath(0, 1));
    }
#endif
}
