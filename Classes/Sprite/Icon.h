//
//  EnemyBase.h
//  TowerDefense
//
//  Created by jowu on 16/2/17.
//
//

#ifndef __TowerDefense__UpgradeIcon__
#define __TowerDefense__UpgradeIcon__

#include <vector>
#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;

class UpgradeIcon : public Node
{
    enum State {
        Enabled = 0,
        Selected,
        Confrim,
        Disabled
    };
    
public:
    static UpgradeIcon* create(const std::string& name, int tid = -1);
    virtual bool init(const std::string& name);
    virtual bool onTouchBegan(Touch* touch, Event* event);

    CC_SYNTHESIZE(int, m_cost, Cost);
    CC_SYNTHESIZE(State, m_state, State);

    CC_SYNTHESIZE_READONLY(int, m_tid, Tid);

private:
    UpgradeIcon(int tid);

private:
    Sprite* m_texture;
};

#endif
