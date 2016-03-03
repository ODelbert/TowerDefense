//
//  TowerSlot.h
//  TowerDefense
//
//  Created by jowu on 15/12/30.
//
//

#ifndef __TowerDefense__TowerSlot__
#define __TowerDefense__TowerSlot__

#include "cocos2d.h"
#include "Tower.h"
#include "TouchNode.h"

USING_NS_CC;

class SlotRing;
class TowerSlot : public TouchNode
{
    friend SlotRing;
public:
    CREATE_FUNC(TowerSlot);
    virtual bool init();
    
    Tower* getTower() const;
    bool onTouchBegan(Touch* touch, Event* evt);
    CC_SYNTHESIZE(int, m_slotId, SlotId);

private:
    Sprite* m_terrian;
    SlotRing* m_slotRing;
    Tower* m_tower;
    
};

#endif /* defined(__TowerDefense__TowerSlot__) */
