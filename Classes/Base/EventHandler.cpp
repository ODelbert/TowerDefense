//
//  EventHandler.cpp
//  TowerDefense
//
//  Created by jowu on 16/2/28.
//
//

#include "EventHandler.h"
#include "Enemy/EnemyFactory.h"
#include "Maps/BattleField.h"
#include "Base/WaveManager.h"

EventHandler* EventHandler::create(BattleField *map)
{
    EventHandler* ret = new EventHandler(map);
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool EventHandler::init()
{
    auto listener = TDEventListener::create();
    listener->onWaveEvent = CC_CALLBACK_1(EventHandler::onWaveEvent, this);
    listener->onTowerEvent = CC_CALLBACK_1(EventHandler::onTowerEvent, this);
    listener->onBulletEvent = CC_CALLBACK_1(EventHandler::onBulletEvent, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

    return true;
}

EventHandler::EventHandler(BattleField* map)
    : m_map(map)
{}

void EventHandler::onWaveEvent(WaveEvent* waveEvent)
{
    auto enmey = EnemyFactory::create(static_cast<EnemyID>(waveEvent->getEnemyId()));
    enmey->sendToBattle(WaveManager::getInstance()->getPath(waveEvent->getPathIndex(), waveEvent->getSubPathIndex()));
    m_map->addEnemy(enmey);
}


void EventHandler::onTowerEvent(TowerEvent* event)
{
}

void EventHandler::onBulletEvent(BulletEvent* event)
{
}