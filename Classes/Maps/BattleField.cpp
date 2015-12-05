//
//  BattleField.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/15.
//
//

#include "BattleField.h"
#include "CommonDef.h"
#include "Controller/WaveManager.h"
#include "Enemy/EnemyFactory.h"

static bool s_flag = false;
BattleField::BattleField()
{
    auto touchlistener = EventListenerTouchOneByOne::create();
    touchlistener->onTouchBegan = CC_CALLBACK_2(BattleField::onTouchBegan, this);
    touchlistener->onTouchEnded = CC_CALLBACK_2(BattleField::onTouchEnded, this);
    touchlistener->onTouchMoved = CC_CALLBACK_2(BattleField::onTouchMoved, this);
    touchlistener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener,this);

    auto waveListener = EventListenerCustom::create("WaveEvent", [=](EventCustom* event){
        typedef struct _WaveEventData {
            int id;
            int path;
            int subPath;
        } WaveEventData;
        
        WaveEventData* info = static_cast<WaveEventData*>(event->getUserData());
        
        auto enmey = EnemyFactory::create(static_cast<EnemyID>(info->id));
        enmey->sendToBattle(WaveManager::getInstance()->getPath(info->path, info->subPath));
        m_mapSprite->addChild(enmey);
    });
    
    _eventDispatcher->addEventListenerWithFixedPriority(waveListener, 1);
}

bool BattleField::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("touch at pos [%f %f]", touch->getStartLocation().x, touch->getStartLocation().y);
    return true;
}

void BattleField::onTouchEnded(Touch* touch, Event* event)
{
}

void BattleField::onTouchMoved(Touch* touch, Event* event)
{
    Vec2 offset = touch->getLocation() - touch->getPreviousLocation();
    Vec2 newPos;
    if (m_mapSprite->getPosition().x + offset.x > 0.5 * MAP_WIDTH) {
        newPos.x = 0.5 * MAP_WIDTH;
    }
    else if (m_mapSprite->getPosition().x + offset.x < TD_WIDTH - 0.5 * MAP_WIDTH) {
        newPos.x = TD_WIDTH - 0.5 * MAP_WIDTH;
    }
    else {
        newPos.x = m_mapSprite->getPosition().x + offset.x;
    }
    
    if (m_mapSprite->getPosition().y + offset.y > 0.5 * MAP_HEIGHT) {
        newPos.y = 0.5 * MAP_HEIGHT;
    }
    else if (m_mapSprite->getPosition().y + offset.y < TD_HEIGHT - 0.5 * MAP_HEIGHT) {
        newPos.y = TD_HEIGHT - 0.5 * MAP_HEIGHT;
    }
    else {
        newPos.y = m_mapSprite->getPosition().y + offset.y;
    }
    
    m_mapSprite->setPosition(newPos);
}

void BattleField::loadLevel(int stage, int difficult)
{
    WaveManager::getInstance()->initialize(stage, difficult);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(String::createWithFormat("sprite_level%d_2-hd.plist", stage)->getCString());
    m_mapSprite = Sprite::createWithSpriteFrameName(String::createWithFormat("Stage_%d.png", stage)->getCString());
    
    if (m_mapSprite) {
        m_mapSprite->setPosition(TD_WIDTH / 2, TD_HEIGHT / 2);
        addChild(m_mapSprite);
    }
    
    schedule(schedule_selector(BattleField::start), 0.0f, 1, 1.0f);
}

void BattleField::start(float dt)
{
    WaveManager::getInstance()->start();
}

void BattleField::updateEnemies()
{
    
}

void BattleField::updateTowers()
{
    
}

void BattleField::UpdateAllies()
{
}


