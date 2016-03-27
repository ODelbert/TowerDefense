#ifndef __TowerDefense__barrack_
#define __TowerDefense__barrack_

#include "Tower.h"
#include "cocos2d.h"

USING_NS_CC;

class AssembleFlag;
class Solider;
class Barrack : public Tower
{
public:
    static Barrack* create(TowerID towerId);
    virtual bool init(TowerID towerId);

private:
    Sprite* m_door;
    std::vector<Solider*> m_soliders;
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
