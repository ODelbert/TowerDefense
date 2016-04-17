//
//  BattleField.h
//  TowerDefense
//
//  Created by jowu on 15/11/15.
//
//

#ifndef __TowerDefense__BattleField__
#define __TowerDefense__BattleField__

#include "cocos2d.h"
#include "Enemy/Enemy.h"
#include "Tower/Tower.h"

USING_NS_CC;

class TowerSlot;
class EventHandler;
class BattleField : public Layer
{
public:
    virtual bool init();
    virtual void addTowerSlots() {}
    virtual void addOrnament() {}
    void loadLevel(int stage, int difficult);
    void start(float dt);

    const std::vector<Enemy*> getEnemies();
    const std::vector<Tower*> getTowers();

    void addTowerSlot(int slotId, Vec2 pos);
    void removeTowerSlot(int slotId);

    void addEnemy(Enemy* enemy);
    void removeEnemy(Enemy* enemy);
    
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    //  Tower actions
    void bulidTower(int slotId, TowerID id);
    void addTower(int slotId, TowerID id);
    void removeTower(int slotId);
    void upgradeTechnology(int slotId, TowerID id, int tid);

    // Enemy actions
    void missTarget(int waveIdx);

    // Bullet actions
    void emitBullet(int slotId);
    void bulletStrike(int slotId, Vec2 destination);


    // user control IF
    void pause();
    void resume();
    void restart();

    void update(float dt);
    
protected:
    explicit BattleField();

    void updateEnemies();
    void updateTowers();
    void UpdateAllies();

protected:
    EventHandler* m_eventHandler;
    Sprite* m_mapSprite;
    std::vector<Enemy*> m_enemies;
    std::vector<Tower*> m_towers;
    std::vector<TowerSlot*> m_towerSlots;
};
#endif /* defined(__TowerDefense__BattleField__) */
