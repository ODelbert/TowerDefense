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
    friend class SlotRing;
public:
    CREATE_FUNC(TowerSlot);
    virtual bool init();

    virtual void onTouchEvent();
    CC_SYNTHESIZE(int, m_slotId, SlotId)
    
    CC_SYNTHESIZE_READONLY(Tower*, m_tower, Tower)
    CC_SYNTHESIZE_READONLY(SlotRing*, m_ring, ring)
};

#endif /* defined(__TowerDefense__TowerSlot__) */
