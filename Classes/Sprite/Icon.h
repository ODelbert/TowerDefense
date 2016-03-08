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
    static UpgradeIcon* create(TowerID id, bool enabled = true);
    virtual bool init(TowerID id, bool enabled = true);
    void onTouchEvent();

    CC_SYNTHESIZE(TowerID, m_id, Id)
    TD_SYNTHESIZE_CHECK(bool, m_enabled, Enabled)
private:
    Sprite* m_selectedImage;
    Sprite* m_disabledImage;
};

class TechnologyIcon : public TouchNode
{
public:
    static TechnologyIcon* create(TowerID id, int tid, bool enabled = true);
    virtual bool init(TowerID id, int tid, bool enabled = true);
    void onTouchEvent();
    
    CC_SYNTHESIZE_READONLY(int, m_tid, Tid)
    CC_SYNTHESIZE(int, m_visibleFlag, VisibleFlag)
private:
    Sprite* m_confrimImage;
    Sprite* m_disabledConfrimImage;
    Sprite* m_enabledImage;
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
