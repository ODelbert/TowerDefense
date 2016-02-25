#ifndef __TowerDefense__Event__
#define __TowerDefense__Event__

#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"
USING_NS_CC;

enum EventType
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

class Bullet;


class WaveEvent : public EventCustom
{
public:
    WaveEvent()
    : EventCustom("WaveEvent") {}
};

class BulletMissEvent : public EventCustom
{
public:
    BulletMissEvent(Bullet* bullet);
};
#endif