#ifndef __TowerDefense__archer__
#define __TowerDefense__archer__
#include "cocos2d.h"
#include "Tower.h"
#include "Shooter.h"

USING_NS_CC;

class ArcherShooter : public Shooter
{
public:
    CREATE_FUNC(ArcherShooter);
    virtual bool init();
    virtual void shoot();

protected:
    explicit ArcherShooter();
};

class Archer : public Tower
{
public:
    static Archer* createArcherTower(TowerLevel level);
    virtual bool init();
    
    virtual void updateState();
};

//

//class ArcaneShooter : public Shooter
//{
//public:
//    static
//};


#endif