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
#include "Base/GameManager.h"

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
    Enemy* enemy = EnemyFactory::create(static_cast<EnemyID>(waveEvent->getEnemyId()));
    
    if (enemy) {
        if (enemy->getId() == EnemyID_Gnoll_Burner) {
            bool comeHere = 0;
        }
        
        GM->addEnemy(enemy);
        enemy->setTag(waveEvent->getIndex());
        enemy->sendToBattle(WaveManager::getInstance()->getPath(waveEvent->getPathIndex(), waveEvent->getSubPathIndex()));
        m_map->addEnemy(enemy);
    }
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
    case TowerEvent::Command::Sell:
    {
        m_map->removeTower(event->getSlotId());
    }
    break;
    default:
        // never goes here
        assert("invalid tower event type!!!");
    break;
    }
}

void EventHandler::onBulletEvent(BulletEvent* event)
{
    switch (event->getCommand()) {
        case BulletEvent::Command::Lanuch:
        m_map->emitBullet(event->getSlotId());
        break;
    case BulletEvent::Command::Strike:
        m_map->bulletStrike(event->getSlotId(), event->getDestination());
        break;
    default:
        // never goes here
        assert("invalid bullet event type!!!");
        break;
    }
}

void EventHandler::onEnemyEvent(EnemyEvent* event)
{
    switch (event->getCommand()) {
    case EnemyEvent::Command::Appear:
        break;
    case EnemyEvent::Command::Disppear:
        break;
    case EnemyEvent::Command::Death:
    {
        // m_map->removeChild();
    }
        break;
    case EnemyEvent::Command::Demonstrate:
        break;
    default:
        // never goes here
        assert("invalid enemy event type!!!");
        break;
    }
}
