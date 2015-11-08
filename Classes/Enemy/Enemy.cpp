//
//  EnemyBase.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/7.
//
//

#include "cocos2d.h"
#include "CommonDef.h"
#include "Enemy.h"

USING_NS_CC;

enum ActionCommon
{
    ActionCommon_Attack = 0,
    ActionCommon_WalkingDown,
    ActionCommon_WalkingRightLeft,
    ActionCommon_Idle,
    ActionCommon_WalkingUp,
    ActionCommon_Death,
    ActionCommon_Spawn,
    ActionCommon_Respawn,
    ActionCommon_Shoot,
    ActionCommon_Cast,
    ActionCommon_Special,
};

class Enemy : public Node
{
public:
    virtual bool init() = 0;
    bool loadEnemyInfo(const std::string& name);
    void born(const std::vector<Vec2>& waypoints);
    
    virtual void underAttack(int dmg, WeaponType wp) {}
    
    // properties
    CC_SYNTHESIZE(int, m_damageMin, damageMin);
    CC_SYNTHESIZE(int, m_damageMax, damageMax);
    CC_SYNTHESIZE(int, m_maxLife, maxLife);
    CC_SYNTHESIZE(int, m_life, life);
    CC_SYNTHESIZE(WeaponType, m_weapon, weapon);
    CC_SYNTHESIZE(ArmorType, m_armor, armor);
    CC_SYNTHESIZE(SpeedType, m_speed, speed);
};
