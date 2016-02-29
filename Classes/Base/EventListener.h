#ifndef __TowerDefense__EventListener__
#define __TowerDefense__EventListener__

#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"
#include "Base/Event.h"

USING_NS_CC;

class TDEventListener : public EventListener
{
public:
    static TDEventListener* create();
    
public:
    std::function<void(WaveEvent*)> onWaveEvent;
    std::function<void(TowerEvent*)> onTowerEvent;
    std::function<void(BulletEvent*)> onBulletEvent;
    
    virtual bool checkAvailable();

    virtual EventListener* clone();

    
private:
    TDEventListener();
};

#endif

