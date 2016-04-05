//
//  Mage.hpp
//  TowerDefense
//
//  Created by jowu on 16/3/18.
//
//

#ifndef Mage_hpp
#define Mage_hpp

#include "cocos2d.h"
#include "Tower/Tower.h"
#include "Tower/Shooter.h"
USING_NS_CC;

class Mage : public Tower
{
public:
    static Mage* create(TowerID level);
    virtual bool init(TowerID level);

    virtual void shoot();
    
};

class MageShooter : public Shooter
{
public:
    CREATE_FUNC(MageShooter)
    virtual bool init();
    virtual void shoot();
protected:
    explicit MageShooter();
};

class MageWild : public Mage
{
public:
    CREATE_FUNC(MageWild)
    virtual bool init();

};

class MageHighElf : public Mage
{
public:
    CREATE_FUNC(MageHighElf)
    virtual bool init();
};


#endif /* Mage_hpp */
