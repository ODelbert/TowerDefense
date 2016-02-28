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
    void onEvent(TDEvent* event);
    
};
//
//auto waveListener = EventListenerCustom::create(Event, [=](EventCustom* event){
//    typedef struct _WaveEventData {
//        int id;
//        int path;
//        int subPath;
//    } WaveEventData;
//    
//    WaveEventData* info = static_cast<WaveEventData*>(event->getUserData());
//    auto enmey = EnemyFactory::create(static_cast<EnemyID>(info->id));
//    enmey->sendToBattle(WaveManager::getInstance()->getPath(info->path, info->subPath));
//
//    m_mapSprite->addChild(enmey);
//});
//
//
//
//
#endif /* EventHandler_hpp */
