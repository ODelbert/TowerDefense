//
//  BattleField.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/15.
//
//

#include "BattleField.h"
#include "CommonDef.h"
#include "Base/WaveManager.h"
#include "Enemy/EnemyFactory.h"
#include "Tower/TowerFactory.h"
#include "PListReader.h"
#include "Base/EventHandler.h"
#include "Animation/AnimationManager.h"

BattleField::BattleField()
: m_eventHandler(nullptr)
{

}

bool BattleField::init()
{
    auto touchlistener = EventListenerTouchOneByOne::create();
    touchlistener->onTouchBegan = CC_CALLBACK_2(BattleField::onTouchBegan, this);
    touchlistener->onTouchEnded = CC_CALLBACK_2(BattleField::onTouchEnded, this);
    touchlistener->onTouchMoved = CC_CALLBACK_2(BattleField::onTouchMoved, this);
    touchlistener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);
    m_eventHandler = EventHandler::create(this);
    m_eventHandler->retain();
    return true;
}

bool BattleField::onTouchBegan(Touch* touch, Event* event)
{
    log("touch at pos [%f %f]", touch->getStartLocation().x, touch->getStartLocation().y);
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

void BattleField::addEnemy(Enemy* enemy)
{
    // TODO:: GameManager adds
    m_mapSprite->addChild(enemy);
}

void BattleField::removeEnemy(Enemy* enemy)
{
    // TODO:: GameManager removes
    m_mapSprite->removeChild(enemy, false);
}

void BattleField::addTower(Tower* tower)
{
    // TODO:: GameManager adds
    m_mapSprite->addChild(tower);
}

void BattleField::removeTower(Tower* tower)
{
    // TODO:: GameManager removes
    m_mapSprite->removeChild(tower, false);
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

const std::vector<Enemy*> BattleField::getEnemies()
{
    return m_enemies;
}

const std::vector<Tower*> BattleField::getTowers()
{
    return m_towers;
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


void BattleField::bulidTower(int slotId, TowerId id)
{
    Animation* ani = AnimationManager::getInstance()->getAnimation(-1);

    auto actions = Sequence::create(Animate::create(ani), CC_CALLBACK_0)
}

void BattleField::addTower(int slotId, TowerID id)
{
    TowerSlot* slot = NULL;
    for (int i = 0; i < m_towerSlots.size(); ++i) {
        if (m_towerSlots[i]->getSlotId() == slotId) {
            slot = m_towerSlots[i];
            break;
        }
    }

    if (!slot) return;

    autot tower = TowerFactory::create(id);
    if (tower) {
        slot->addChild(tower);
    }
}

void BattleField::upgradeTechnology(int slotId, towerId id, int tid)
{
    log("BattleField::upgradeTechnology slotId %d towrId id %d tid %d", slotId, id, tid);
    TowerSlot* slot = NULL;
    for (int i = 0; i < m_towerSlots.size(); ++i) {
        if (m_towerSlots[i]->getSlotId() == slotId) {
            slot = m_towerSlots[i];
            break;
        }
    }

    if (!slot) return;
    auto tower = slot->getTower();
    if (tower) {
        tower->upgradeTechnology(tid);
    }
}

