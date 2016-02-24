//
//  EnemyBase.h
//  TowerDefense
//
//  Created by jowu on 16/2/17.
//
//

#ifndef __TowerDefense__upgradeIcon__
#define __TowerDefense__upgradeIcon__

#include <vector>
#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;

class upgradeIcon : public Node
{
    enum State {
        Selected = 1,
        Confrim,
        Disabled
    };
    
public:
    static upgradeIcon* create(const std::string& name);
    virtual bool init(const std::string& name);
    virtual bool onTouchBegan(Touch* touch, Event* event);

    CC_SYNTHESIZE(int, m_cost, Cost);
    CC_SYNTHESIZE(State, m_state, State);

    CC_SYNTHESIZE_READONLY(int, m_tid, Tid);

private:
    Sprite* m_texture;
};

#endif
