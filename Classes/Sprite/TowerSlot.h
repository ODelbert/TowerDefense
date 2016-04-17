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
#include "RangeCircle.h"

USING_NS_CC;

class SlotRing;

class TowerSlot : public TouchNode
{
    friend class SlotRing;
public:
    static TowerSlot* create(int slotId);
    virtual bool init(int slotId);

    virtual void onTouchEvent();
    void addTower(Tower* tower);
    void removeTower();
    CC_SYNTHESIZE_READONLY(int, m_slotId, SlotId)
    
    CC_SYNTHESIZE_READONLY(Tower*, m_tower, Tower)
    CC_SYNTHESIZE_READONLY(SlotRing*, m_ring, ring)
};

#endif /* defined(__TowerDefense__TowerSlot__) */
