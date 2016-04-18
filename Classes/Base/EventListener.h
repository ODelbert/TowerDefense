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
    static TDEventListener* create(const std::function<void(TDEvent*)>& callback);
    
public:  
    virtual bool checkAvailable();
    virtual EventListener* clone();

private:
    TDEventListener();
    
    bool init(const ListenerID& listenerId, const std::function<void(TDEvent*)>& callback);
    
private:
    std::function<void(TDEvent*)> _onTDEvent;
};

#endif

