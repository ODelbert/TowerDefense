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
        Select = 1,
        Confrim,
        Disabled
    };
    
public:
    static upgradeIcon* create(const std::string& name);
    virtual bool init(const std::string& name);
    virtual bool onTouchBegan(Touch* touch, Event* event);
    
private:
    State m_state;
    Sprite* m_texture;
};

#endif