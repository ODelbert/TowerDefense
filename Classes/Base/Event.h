#ifndef __TowerDefense__Event__
#define __TowerDefense__Event__

#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"
USING_NS_CC;

class Bullet;

enum TDEventType
{
    EventType_Wave,
    EventType_Bullet_Miss,
    EventType_Bullet_Fire,
    EventType_Bullet_Strike,
    EventType_Build,
    EventType_Sell,
    EventType_Upgrade,
    EventType_Death,
    EventType_Reborn,
    EventType_LevelUp,
    EventType_Action,
    EventType_Assemble,
    EventType_Reinforcement,
    EventType_Lighting,
    EventType_HeroSpell
};


class TDEvent : public EventCustom
{
public:
    TDEvent(TDEventType type, const std::string& listnerId);
    
    inline TDEventType getEventType() const { return m_type; }
    void setPriority(int priority) { m_priority = priority; }
    inline int getPriority() const { return m_priority; }
private:
    TDEventType m_type;
    int m_priority;
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

typedef struct _WaveEventData {
    int id;
    int path;
    int subPath;
} WaveEventData;

WaveEventData eventData;
eventData.id = name2Id(m_waves[m_waveIndex].spwans()[m_spawnIndex].id);
eventData.path = m_waves[m_waveIndex].getPathIndex();
eventData.subPath = m_waves[m_waveIndex].spwans()[m_spawnIndex].path;

WaveEvent event;
event.setUserData(&eventData);

class WaveEvent : public TDEvent
{
    struct WaveEventData {
        int id;
        int path;
        int subPath;
    };
public:
    WaveEvent()
    : EventCustom("WaveEvent") {}
    
    void setWaveData(int id, int path, int subpath);
};

class BulletMissEvent : public EventCustom
{
public:
    BulletMissEvent(Bullet* bullet);
};




#endif