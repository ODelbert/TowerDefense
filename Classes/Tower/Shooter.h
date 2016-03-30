//
//  Shooter.h
//  TowerDefense
//
//  Created by jowu on 15/12/27.
//
//

#ifndef __TowerDefense__Shooter__
#define __TowerDefense__Shooter__

#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;

class Shooter : public Node
{
    enum State { Idel, Attack };
public:
    explicit Shooter(TowerID id);
    virtual ~Shooter();
    
    CC_SYNTHESIZE_READONLY(TowerID, m_towerId, TowerId)
    CC_SYNTHESIZE(Direction, m_oriention, Oriention)
    CC_SYNTHESIZE(State, m_state, State)
    virtual void shoot() = 0;

protected:
    TowerID m_towerId;
    Direction m_oriention;
    State m_state;
    Sprite* m_texture;
};

#endif /* defined(__TowerDefense__Shooter__) */
