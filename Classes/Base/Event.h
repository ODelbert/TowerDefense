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

enum TDEventType
{
    TDEventType_Invaild = -1,
    // WAVE
    TDEventType_Wave,
    // BULLET
    TDEventType_Bullet,
    // TOWER
    TDEventType_Tower,
    // ENEMY
    TDEventType_Enemy,
    // HERO
    TDEventType_Hero,
    // ALLY
    TDEventType_Ally
    // HERO / ALLY / ENEMY
};

class TDEvent : public EventCustom
{
public:
    TDEvent(TDEventType type = TDEventType_Invaild);
    CC_SYNTHESIZE_READONLY(TDEventType, m_eventType, EventType)
};

class WaveEvent : public TDEvent
{
public:
    WaveEvent();
    int getEnemyId() const;
    int getPathIndex() const;
    int getSubPathIndex() const;
    int waveCount() const;
    void setWaveData(int id, int path, int subpath, int waveCount);

private:
    int m_eId;
    int m_waveCount;
    int m_path;
    int m_subPath;
};

class TowerEvent : public TDEvent
{
public:
    enum Command
    {
        Invaild,
        Build, // slot, towerId
        UpgradeTower, // slot, towerId, level
        Sell, // slot, towerId, level2
        Disabled, // slot
        Assemble, // slot
        UpgradeTechnology, // slot, towerId, tid
        Hint, // slot, towerId
        Demonstrate // slot, towerId
    };

public:
    TowerEvent(Command cmd = Invaild, int slotId = -1, TowerID id = TowerID_Invaild, int tid = -1);
    CC_SYNTHESIZE(TowerID, m_towerId, TowerId)
    CC_SYNTHESIZE(int, m_slotId, SlotId)
    CC_SYNTHESIZE(int, m_technologyId, TechnologyId)
    CC_SYNTHESIZE(Command, m_command, Command)
};

class EnemyEvent : public TDEvent
{
public:
    enum Command
    {
        Invaild,
        Appear,
        Disppear,
        Death,
        Demonstrate
    };

    CC_SYNTHESIZE(EnemyID, m_id, Id)
    CC_SYNTHESIZE(Command, m_command, Command)

    EnemyEvent(Command cmd = Invaild, EnemyID id = EnemyID_Invalid);
};

class BulletEvent : public TDEvent
{
public:
    BulletEvent(Bullet* bullet, TDEventType action);
    //CC_SYNTHESIZE(Node*, m_sender, Sender);
    //CC_SYNTHESIZE(Node*, m_receiver, Receiver);
    
private:
    Bullet* m_bullet;
};

#endif
