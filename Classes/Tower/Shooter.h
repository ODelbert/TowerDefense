//
//  Shooter.h
//  TowerDefense
//
//  Created by jowu on 15/12/27.
//
//

#ifndef __TowerDefense__Shooter__
#define __TowerDefense__Shooter__

#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;

class Shooter : public Node
{
public:
    explicit Shooter(TowerID id, TowerLevel level);
    virtual ~Shooter();
    
    virtual void shoot();
    Direction getOriention();
    void setOriention(Direction dir);
    
protected:
    TowerID m_id;
    TowerLevel m_level;
    Direction m_oriention;
    Sprite* m_texture;
};

#endif /* defined(__TowerDefense__Shooter__) */
