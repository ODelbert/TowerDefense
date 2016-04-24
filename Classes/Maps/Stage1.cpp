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


    // test action
    auto sp = Sprite::createWithSpriteFrameName("ico_sell_0002.png");
    sp->runAction(RepeatForever::create( Animate::create(AnimationCache::getInstance()->getAnimation(AID_ENEMY_ARACHNOMANCER_SPIDER_WALKINGDOWN))));
    addChild(sp);
    sp->setPosition(100, 100);


    auto obj = EnemyFactory::create(EnemyID_Redcap);
    obj->setPosition(400, 300);
    m_mapSprite->addChild(obj);
    obj->runAction(RepeatForever::create(Sequence::create(MoveTo::create(4.0, Vec2(400, 400)), MoveTo::create(4.0, Vec2(100, 100)), nullptr)));
    obj->walkingDown();

    return true;
}

void Stage1::addTowerSlots()
{
    // Test!!
    addTowerSlot(0, Vec2(400, 300));
    addTowerSlot(1, Vec2(600, 300));

    WaveFlag* wf = WaveFlag::create(WaveFlag::Normal, 10, true);
    wf->setPosition(100, 400);
    addChild(wf);

    // Test speed
#if 0
    for (int i = 0; i < SpeedType_VeryFast; ++i) {
        auto monster = EnemyFactory::create(EnemyID_Redcap);
        monster->setSpeed(static_cast<SpeedType>(i));
        m_mapSprite->addChild(monster);

        monster->sendToBattle(WaveManager::getInstance()->getPath(0, 1));
    }
#endif


// test Life bar
    m_bar = LifeBar::create();
    m_mapSprite->addChild(m_bar);
    m_bar->setPosition(500, 500);
    m_bar->schedule([&](float dt){
        m_bar->setPercentage(m_bar->getPercentage() - 1.0);
    }, 0.5, 100, 0, "bar_test");

}

void Stage1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_F2:
    {
        restart();
    }
        break;
    case EventKeyboard::KeyCode::KEY_F3:
    {
        auto monster = EnemyFactory::create(EnemyID_Redcap);
        m_mapSprite->addChild(monster);
        monster->sendToBattle(WaveManager::getInstance()->getPath(0, 1));

    }
        break;

    case EventKeyboard::KeyCode::KEY_SPACE:
    {
        static bool isPause = true;
        if (isPause)
            pause();
        else
            resume();

    }
        break;
    case EventKeyboard::KeyCode::KEY_ESCAPE:
    {
        // gameOver();
    }
        break;
    case EventKeyboard::KeyCode::KEY_F4:
    {

    }
        break;
}
