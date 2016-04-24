//  GameManager.h
//  TowerDefense
//
//  Created by jowu on 15/11/22.
//
//
#ifndef __TowerDefense__GameManager__
#define __TowerDefense__GameManager__

#include "cocos2d.h"
#include "Singleton.h"
#include "Event.h"
#include "CommonDef.h"

USING_NS_CC;

class Technology;
class DamageSystem;
class TDEvent;
class Enemy;
class Tower;
class Bullet;

class GameManager : public Ref, public Singleton<GameManager>
{
public:
    GameManager();

//    void addTower(Tower* tower);
//    void removeTower(Tower* tower);
    inline std::vector<Enemy*> getEnemies() const { return m_enemies; }
    inline std::vector<Tower*> getTowers() const { return m_towers; }
    void addEnemy(Enemy* enemy);
    void removeEnemy(Enemy* enmey);
    void removeEnemy(int wid);
    void dispatchEvent(TDEvent* event);
    void addEventListenerWithFixedPriority(EventListener* listener, int priority);
    void addEventListenerWithSceneGraphPriority(EventListener* listener, Node* node);
    CC_SYNTHESIZE(int, m_gold, Gold)

    uint getUpgradeFund(TowerID id, int tid = -1);
    uint getTechnologyFund(TowerID id, int tid, int level);
    bool enoughGold(int gold);

private:
    std::vector<Enemy*> m_enemies;
    std::vector<Tower*> m_towers;
    std::vector<Bullet*> m_bullets;
};

#define GM GameManager::getInstance()


#endif /* defined(__TowerDefense__GameManager__) */
