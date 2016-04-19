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
#include "Sprite/TowerSlot.h"
#include "Sprite/BuildBar.h"
#include "Base/GameManager.h"
#include "Tower/Bullet.h"

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
    GM->addEventListenerWithSceneGraphPriority(touchlistener, this);
    
    auto keyboardEventListener = EventListenerKeyboard::create();
    keyboardEventListener->onKeyPressed = CC_CALLBACK_2(BattleField::onKeyPressed, this);
    GM->addEventListenerWithSceneGraphPriority(keyboardEventListener, this);
    
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

void BattleField::removeEnemy(int waveIdx)
{
    // TODO:: GameManager removes
    missTarget(waveIdx);
    auto child = getChildByTag(waveIdx);
    Enemy* enemy = static_cast<Enemy*>(child);
    if (!enemy) return;
    GM->removeEnemy(enemy);
    enemy->removeFromParent();
}

void BattleField::loadLevel(int stage, int difficult)
{
    schedule(schedule_selector(BattleField::update), 1);
    WaveManager::getInstance()->initialize(stage, difficult);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(String::createWithFormat("sprite_level%d_2-hd.plist", stage)->getCString());
    m_mapSprite = Sprite::createWithSpriteFrameName(String::createWithFormat("Stage_%d.png", stage)->getCString());
    
    if (m_mapSprite) {
        m_mapSprite->setPosition(TD_WIDTH / 2, TD_HEIGHT / 2);
        addChild(m_mapSprite);
    }
    
    WaveManager::getInstance()->start();
    // schedule(schedule_selector(BattleField::start), 0.0f, 1, 1.0f);
}

void BattleField::start(float dt)
{
    // WaveManager::getInstance()->start();
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

void BattleField::bulidTower(int slotId, TowerID id)
{
    TowerSlot* slot = NULL;
    for (int i = 0; i < m_towerSlots.size(); ++i) {
        if (m_towerSlots[i]->getSlotId() == slotId) {
            slot = m_towerSlots[i];
            break;
        }
    }
    
    if (!slot) return;
    BuildBar* bar = BuildBar::create();
    bar->setPosition(slot->getPosition());
    bar->build(slotId, id);
    m_mapSprite->addChild(bar);
}

void BattleField::addTowerSlot(int slotId, Vec2 pos)
{
    TowerSlot* slot = TowerSlot::create(slotId);
    if (slot) {
        m_towerSlots.push_back(slot);
        m_mapSprite->addChild(slot);
        slot->setPosition(pos);
    }
}

void BattleField::removeTowerSlot(int slotId)
{
//    std::vector<TowerSlot*>::iterator iter = m_towerSlots.begin();
//    for (; iter < m_towerSlots.end(); ++iter) {
//        if (slotId == iter->getSlotId()) {
//            // TODO:: GM remove tower
//            m_towerSlots.erase(iter);
//            m_mapSprite->removeChild(*iter, false);
//            --iter;
//            return;
//        }
//    }
}

void BattleField::addTower(int slotId, TowerID id)
{
    log("BattleField::addTower slotId %d towerId %d", slotId, id);
    TowerSlot* slot = NULL;
    for (int i = 0; i < m_towerSlots.size(); ++i) {
        if (m_towerSlots[i]->getSlotId() == slotId) {
            slot = m_towerSlots[i];
            break;
        }
    }

    if (!slot) return;
    auto tower = TowerFactory::create(id);
    assert(tower != NULL);
    if (tower) {
        slot->addTower(tower);
    }
}

void BattleField::removeTower(int slotId)
{
    log("BattleField::removeTower slotId %d towerId %d", slotId);
    TowerSlot* slot = NULL;
    for (int i = 0; i < m_towerSlots.size(); ++i) {
        if (m_towerSlots[i]->getSlotId() == slotId) {
            slot = m_towerSlots[i];
            break;
        }
    }

    if (!slot) return;
    slot->removeTower();
}

void BattleField::upgradeTechnology(int slotId, TowerID id, int tid)
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

void BattleField::missTarget(int waveIdx)
{
    for (int i = 0; i < m_towerSlots.size(); ++i) {
        Tower* tower = m_towerSlots[i]->getTower();
        if (!tower) {
            Enemy* target = tower->getTarget();
            if (target->getTag() == waveIdx) {
                tower->setTarget(nullptr);
            }
        }
    }
}

void BattleField::emitBullet(int slotId)
{
    for (int i = 0; i < m_towerSlots.size(); ++i) {
        if (m_towerSlots[i]->getSlotId() == slotId) {
            Tower* tower = m_towerSlots[i]->getTower();
            if (!tower) {
                continue;;
            }

            Enemy* enemy = tower->getTarget();
            if (!enemy) {
                continue;
            }

            // TODO:: caculate the future position of enemies
            Vec2 destination = enemy->getPosition();
            switch (tower->getId()) {
            case TowerID_Archer_Lv1:
            case TowerID_Archer_Lv2:
            case TowerID_Archer_Lv3:
            {
                // TODO:: shooter position
                Vec2 shooterPos = m_towerSlots[i]->getPosition();
                auto ball = BallBullet::create();
                ball->setPosition(shooterPos);
                ball->setDestination(destination);
                ball->launch(slotId);
                addChild(ball);
            }
                break;
            case TowerID_Barrack_Lv1:
            case TowerID_Barrack_Lv2:
            case TowerID_Barrack_Lv3:
                break;
            case TowerID_Mage_Lv1:
            case TowerID_Mage_Lv2:
            case TowerID_Mage_Lv3:
                break;
            case TowerID_Artillery_Lv1:
            case TowerID_Artillery_Lv2:
            case TowerID_Artillery_Lv3:
                break;
            }

            break;
        }
    }
}

void BattleField::bulletStrike(int slotId, Vec2 destination)
{
    for (int i = 0; i < m_towerSlots.size(); ++i) {
        if (m_towerSlots[i]->getSlotId() == slotId) {
            Tower* tower = m_towerSlots[i]->getTower();
            if (!tower) {
                return;
            }

            const std::vector<Enemy*> enemies = GM->getEnemies();
            for (int i = 0; i < enemies.size(); ++i) {
                if (enemies[i]->getPosition().distance(destination) < 50  /* tower->getRange() */) {
                    enemies[i]->getHurt(RAND_INT(tower->getDamageMin(), tower->getDamageMax()));
                    return;
                }
            }
        }
    }
}

void BattleField::update(float dt)
{
    // PListReader::getInstance()->saveImages();
}

void BattleField::restart()
{
    start(0);
}

void BattleField::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_F2:
    {
        restart();
    }
        break;
    case EventKeyboard::KeyCode::KEY_SPACE:
    {
        pause();
    }
        break;
    }
}
