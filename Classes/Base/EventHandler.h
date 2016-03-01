//
//  EventHandler.h
//  TowerDefense
//
//  Created by jowu on 16/2/28.
//
//

#ifndef EventHandler_h
#define EventHandler_h


#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"
#include "Event.h"
#include "EventListener.h"


USING_NS_CC;

class BattleField;

class EventHandler : public Ref
{
public:
    static EventHandler* create(BattleField* map);
    bool init();

    void onEvent(TDEvent* event);
    
private:
    void onWaveEvent(WaveEvent* event);
    void onTowerEvent(TowerEvent* event);
    void onBulletEvent(BulletEvent* event);
    
private:
    EventHandler(BattleField* map);
    
private:
    BattleField* m_map;
};

#endif /* EventHandler_h */
