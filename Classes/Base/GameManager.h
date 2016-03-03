//  GameManager.h
//  TowerDefense
//
//  Created by jowu on 15/11/22.
//
//
#ifndef __TowerDefense__GameManager__
#define __TowerDefense__GameManager__

#include "cocos2d.h"
#include "Singleton.h"
#include "Event.h"

USING_NS_CC;

class Technology;
class DamageSystem;
class TDEvent;
class GameManager : public Ref, public Singleton<GameManager>
{
public:
    GameManager();
    void dispatchEvent(TDEvent* event);

    CC_SYNTHESIZE(int, m_gold, Gold);
};

#define GM GameManager::getInstance()


#endif /* defined(__TowerDefense__GameManager__) */
