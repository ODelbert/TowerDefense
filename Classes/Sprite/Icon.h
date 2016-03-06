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
#include "TouchNode.h"

USING_NS_CC;

class UpgradeIcon : public TouchNode
{
public:
    static UpgradeIcon* create(TowerType type);
    virtual bool init(TowerType type);
    void onTouchEvent();
    
private:
    Sprite* m_selectedImage;
    Sprite* m_disabledImage;
};

class TechnologyIcon : public TouchNode
{
public:
    static TechnologyIcon* create(TowerType type, int tid);
    virtual bool init(TowerType type, int tid);
    void onTouchEvent();
    
    CC_SYNTHESIZE_READONLY(int, m_tid, Tid);
    
private:
    Sprite* m_selectedImage;
    Sprite* m_disabledImage;
};

class SellIcon : public TouchNode
{
public:
    static SellIcon* create();
    virtual bool init();
    void onTouchEvent();
    
private:
    Sprite* m_selectedImage;
};

#endif
