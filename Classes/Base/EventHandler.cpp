//
//  EventHandler.cpp
//  TowerDefense
//
//  Created by jowu on 16/2/28.
//
//

#include "EventHandler.h"

void EventHandler::onEvent(TDEvent* event)
{
    switch (event->getType()) {
        case EventActionType_Wave:
        {
            WaveEvent* waveEvent = static_cast<WaveEvent*>(event);
            auto enmey = EnemyFactory::create(static_cast<EnemyID>(waveEvent->getEnemyId()));
            enmey->sendToBattle(WaveManager::getInstance()->getPath(waveEvent->getPathIndex(), waveEvent->getSubPathIndex()));
            m_mapSprite->addChild(enmey);
        }
            break;
            
        default:
            break;
    }
}

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
    listener->on
}