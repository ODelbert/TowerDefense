//
//  GameManager.h
//  TowerDefense
//
//  Created by jowu on 15/11/22.
//
//



#include "GameManager.h"
#include "Enemy/Enemy.h"
#include "Tower/Tower.h"
#include "Tower/Bullet.h"

GameManager::GameManager()
: m_gold(0)
{
    
}

void GameManager::addEnemy(Enemy* enemy)
{
    m_enemies.push_back(enemy);
}

void GameManager::removeEnemy(Enemy* enmey)
{
    std::vector<Enemy*>::iterator iter = m_enemies.begin();
    while (iter != m_enemies.end()) {
        if (*iter = enmey) {
            m_enemies.erase(iter);
            --iter;
            return;
        }

        ++iter;
    }
}

void GameManager::dispatchEvent(TDEvent* event)
{
    Director::getInstance()->getEventDispatcher()->dispatchEvent(event);
}

void GameManager::addEventListenerWithFixedPriority(EventListener* listener, int priority)
{
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, priority);
}

void GameManager::addEventListenerWithSceneGraphPriority(EventListener* listener, Node* node)
{
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

bool GameManager::enoughGold(int gold)
{
    return true;
}

uint GameManager::getUpgradeFund(TowerID id, int tid)
{
    return 0;
}

uint GameManager::getTechnologyFund(TowerID id, int tid, int level)
{
    return 0;
}

