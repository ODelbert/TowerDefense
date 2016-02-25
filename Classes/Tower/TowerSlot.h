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

USING_NS_CC;

class SlotRing;
class Icon;
class TowerSlot : public Node
{
    friend SlotRing;
public:
    CREATE_FUNC(TowerSlot);
    virtual bool init();
    
    Tower* getTower() const;
    void onTouchBegan(Touch* touch, Event* evt);
    
private:
    std::vector<Icon*> getTowerIcons(Tower* tower);

private:
    Sprite* m_terrian;
    SlotRing* m_slotRing;
    Tower* m_tower;
    
};

#endif /* defined(__TowerDefense__TowerSlot__) */
