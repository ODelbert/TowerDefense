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
    static Archer* create(TowerLevel level);
    virtual bool init();
    
    virtual void updateState();
};

class ArcaneShooter : public Shooter
{
public:
    CREATE_FUNC(ArcaneShooter);
	virtual bool init();
	virtual void shoot();

protected:
	explicit ArcaneShooter();		
};

class ArcaneTower : public Tower
{
public:
    CREATE_FUNC(ArcaneTower);
    virtual bool init();
    
    virtual void updateState();
};

class SliverShooter : public Shooter
{
public:
    CREATE_FUNC(SliverShooter);
	virtual bool init();
	virtual void shoot();

protected:
	explicit ArcaneShooter();		
};

class SliverTower : public Tower
{
public:
    CREATE_FUNC(SliverTower);
    virtual bool init();
    
    virtual void updateState();
};

#endif