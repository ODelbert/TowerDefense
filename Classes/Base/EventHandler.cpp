//
//  EventHandler.cpp
//  TowerDefense
//
//  Created by jowu on 16/2/28.
//
//

#include "EventHandler.h"
#include "Enemy/EnemyFactory.h"
#include "Tower/TowerFactory.h"
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
    auto listener = TDEventListener::create(CC_CALLBACK_1(EventHandler::onEvent, this));
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

    return true;
}

EventHandler::EventHandler(BattleField* map)
    : m_map(map)
{}

void EventHandler::onEvent(TDEvent* event)
{
    switch (event->getEventType()) {
        case TDEventType_Wave:
            onWaveEvent(static_cast<WaveEvent*>(event));
            break;
        case TDEventType_Tower:
            onTowerEvent(static_cast<TowerEvent*>(event));
        default:
            break;
    }
}

void EventHandler::onWaveEvent(WaveEvent* waveEvent)
{
    auto enmey = EnemyFactory::create(static_cast<EnemyID>(waveEvent->getEnemyId()));
    enmey->sendToBattle(WaveManager::getInstance()->getPath(waveEvent->getPathIndex(), waveEvent->getSubPathIndex()));
    m_map->addEnemy(enmey);
}

void EventHandler::onTowerEvent(TowerEvent* event)
{
    if (!m_map) return;
    switch (event->getCommand()) {
    case TowerEvent::Command::Build:
    {
        m_map->bulidTower(event->getSlotId(), event->getTowerId());
    }
    break;
    case TowerEvent::Command::UpgradeTower:
    {
        m_map->addTower(event->getSlotId(), event->getTowerId());
    }
    break;
    case TowerEvent::Command::UpgradeTechnology:
    break;
    default:
    break;
    }
}

void EventHandler::onBulletEvent(BulletEvent* event)
{
}
