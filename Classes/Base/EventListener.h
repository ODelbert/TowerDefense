#ifndef __TowerDefense__Event__
#define __TowerDefense__Event__

#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"
#include "Event.h"

USING_NS_CC;

class TDEventListener : public EventListener
{
public:
    static TDEventListener* create();

};

