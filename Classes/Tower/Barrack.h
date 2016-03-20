#ifndef __TowerDefense__barrack_
#define __TowerDefense__barrack_

#include "Tower.h"
#include "cocos2d.h"

USING_NS_CC;

class Barrack : public Tower
{
public:
    static Barrack* create(TowerLevel level);
    virtual bool init(TowerLevel level);

};

class ForesetKeeperHub : public Barrack
{
public:
    CREATE_FUNC(ForesetKeeperHub)
    virtual bool init();
};

class BladeSingerHall : public Barrack
{
public:
    CREATE_FUNC(BladeSingerHall)
    virtual bool init();
};



#endif