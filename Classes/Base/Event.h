#ifndef __TowerDefense__Event__
#define __TowerDefense__Event__

#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;

class Tower;
class Enemy;
class Ally;
class Bullet;

#define EVENT_WAVE "WAVE"
#define EVENT_BULLET "BULLET"
#define EVENT_TOWER "TOWER"
#define EVENT_HERO "HERO"
#define EVENT_ENEMY "ENEMY"
#define EVENT_ALLY "ALLY"
#define EVENT_SPELLS "OPTION"

enum EventActionType
{
    EventActionType_INVALID = -1,
    // WAVE
    EventActionType_Wave,
    // BULLET
    EventActionType_Bullet_Miss,
    EventActionType_Bullet_Fire,
    EventActionType_Bullet_Strike,
    // TOWER
    EventActionType_Build,
    EventActionType_Sell,
    EventActionType_Upgrade,
    // HERO / ALLY / ENEMY
    EventActionType_Death,
    EventActionType_Reborn,
    EventActionType_LevelUp,
    EventActionType_Action,
    EventActionType_Assemble,
    // OPTION
    EventActionType_Reinforcement,
    EventActionType_Lighting,
    EventActionType_HeroSpell
};

class TDEvent : public EventCustom
{
public:
    TDEvent(EventActionType action = EventActionType_INVALID);
    EventActionType getEventActionType();
    void setEventAction(EventActionType action);

private:
    EventActionType m_action;
};

class WaveEvent : public TDEvent
{
public:
    WaveEvent();
    int getEnemyId() const;
    int getPathIndex() const;
    int getSubPathIndex() const;
    void setWaveData(int id, int path, int subpath);
    
private:
    int m_eId;
    int m_path;
    int m_subPath;
};

class TowerEvent : public TDEvent
{
public:
    TowerEvent(Tower* tower, int slotId, EventActionType action);
    Tower* getTower() const;
    int getSlotId() const;

private:
    Tower* m_tower;
    int m_slotId;
};

class BulletEvent : public TDEvent
{
public:
    BulletEvent(Bullet* bullet, EventActionType action);
    
private:
    Bullet* m_bullet;
};




#endif