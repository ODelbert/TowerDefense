#ifndef __TowerDefense__Event__
#define __TowerDefense__Event__

#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"
USING_NS_CC;

class TDEventListener : public EventListenerCustom
{
    
};

auto waveListener = EventListenerCustom::create("WaveEvent", [=](EventCustom* event){
        typedef struct _WaveEventData {
            int id;
            int path;
            int subPath;
        } WaveEventData;
        
        WaveEventData* info = static_cast<WaveEventData*>(event->getUserData());

        auto enmey = EnemyFactory::create(static_cast<EnemyID>(info->id));
        enmey->sendToBattle(WaveManager::getInstance()->getPath(info->path, info->subPath));
        m_mapSprite->addChild(enmey);
    });