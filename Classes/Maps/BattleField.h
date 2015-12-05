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
USING_NS_CC;

class BattleField : public Layer
{
public:
    virtual void addTerrian() {}
    virtual void addOrnament() {}
    void loadLevel(int stage, int difficult);
    void start(float dt);

    virtual bool onTouchBegan(Touch* touch, Event* event) override;
    virtual void onTouchEnded(Touch* touch, Event* event) override;
    virtual void onTouchMoved(Touch* touch, Event* event) override;
    
protected:
    explicit BattleField();

    void updateEnemies();
    void updateTowers();
    void UpdateAllies();

    
protected:
    Sprite* m_mapSprite;
};
#endif /* defined(__TowerDefense__BattleField__) */
