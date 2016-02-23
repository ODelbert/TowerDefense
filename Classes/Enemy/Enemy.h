//
//  EnemyBase.h
//  TowerDefense
//
//  Created by jowu on 15/11/7.
//
//

#ifndef __TowerDefense__EnemyBase__
#define __TowerDefense__EnemyBase__

#include <vector>
#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;

struct EnemyInfo
{
	int seq;
    int id;
    char name[32];
    int dmgMin;
    int dmgMax;
    int life;
    int weapon;
    int armor;
    int resist;
    int speed;
    int food;
    int flyable;
    int boss;
};

enum ActionEnemy {
    ActionEnemy_Attack = 0,
    ActionEnemy_WalkingDown,
    ActionEnemy_WalkingRightLeft,
    ActionEnemy_Idle,
    ActionEnemy_WalkingUp,
    ActionEnemy_Death,
    ActionEnemy_Spawn,
    ActionEnemy_Respawn,
    ActionEnemy_Shoot,
    ActionEnemy_Cast,
    ActionEnemy_Special,
    ActionEnemy_RunningDown,
    ActionEnemy_RunningRightLeft,
    ActionEnemy_RunningUp,
};

enum EnemyState
{
    EnemyState_Invalid = -1,
	EnemyState_Appear,
	EnemyState_WalkNext,
    EnemyState_RunningNext,
	EnemyState_Dead,
    
	EnemyState_AttackLeft,
    EnemyState_AttackRight,
    EnemyState_CastSpellLeft,
    EnemyState_CastSpellRight,
    EnemyState_SpeicalAttackLeft,
    EnemyState_SpeicalAttackRight,

    EnmeyState_Num
};


// debuff state last for seconds
enum DeBuffState
{
    DeBuffState_Weak = 0x0001, // more damage is taken
    DeBuffState_DisArm = 0x0002, // disable attack
    DeBuffState_Blooding = 0x0004, // blooding
    DeBuffState_Slow = 0x0008, // slow down move speed
    DeBuffState_Freeze = 0x0010, // freeze,can not move
    DeBuffState_Borning = 0x0020, // born, time lasting damage
    DeBuffState_Posion = 0x0040, // posion, time lasting damage
    DeBuffState_Stun = 0x0080, // stun, cannot move & attack
    DeBuffState_Armor = 0x0100, // decreace armor
};

// buff state last for seconds
enum BuffState {
    BuffState_Hasten = 0x0001, // speed up
    BuffState_Recover = 0x0002, // life recover
    BuffState_Fury = 0x0004, // attack damage up
    BuffState_EnegyShield = 0x0008 // protect shield
};

class WayPoints : public Ref
{
public:
    void setPoints(const std::vector<Vec2>& points);
    Vec2 getcurPoint() const;
    Direction getDirection() const;
    bool moveToNextPoint();
    float fulfilledPercent() const;

private:
    std::vector<Vec2> m_points;
    uint m_pathIndex;
    Direction m_dir;
};

class Enemy : public Node
{
public:
    virtual void updateState(float dt);

    virtual void attack() {}
    virtual void idle();
    virtual void walkingLeft();
    virtual void walkingRight();
    virtual void walkingDown();
    virtual void walkingUp();
    virtual void runningLeft();
    virtual void runningRight();
    virtual void runningDown();
    virtual void runningUp();
    virtual void death();
    virtual void spawn();
    virtual void respawn();
    virtual void shoot();
    virtual void cast();
    virtual void speicialAttack();

    void sendToBattle(const std::vector<Vec2>& waypoints);
    void moveToNext();
    float fulfilledPercent() const;

private:
    // properties
    CC_SYNTHESIZE_READONLY(EnemyID, m_id, Id);
    CC_SYNTHESIZE(std::string, m_name, name);
    CC_SYNTHESIZE(int, m_damageMin, damageMin);
    CC_SYNTHESIZE(int, m_damageMax, damageMax);
    CC_SYNTHESIZE(int, m_maxLife, maxLife);
    CC_SYNTHESIZE(int, m_life, life);
    CC_SYNTHESIZE(WeaponType, m_weapon, weapon);
    CC_SYNTHESIZE(ArmorType, m_armor, armor);
    CC_SYNTHESIZE(SpeedType, m_speed, speed);

    CC_SYNTHESIZE_READONLY(uint, m_buffs, buffs);
    CC_SYNTHESIZE_READONLY(uint, m_debuffs, debuffs);
    CC_SYNTHESIZE_READONLY(EnemyState, m_state, state);
    CC_SYNTHESIZE_READONLY(Direction, m_direction, direction);

protected:
    bool initWithEnemyId(EnemyID id);
    
protected:
    Enemy() {}
    virtual ~Enemy() {}

    WayPoints m_wayPoints;
    Sprite* m_texture;
    CC_DISALLOW_COPY_AND_ASSIGN(Enemy)
};

#define DECLARE_ENEMY(monster) \
    class monster : public Enemy \
    { \
    public: \
        CREATE_FUNC(monster); \
        virtual bool init(); \
    }; \

#define DECLARE_ENEMY_START(monster) \
    class monster : public Enemy \
    { \
    public: \
        CREATE_FUNC(monster); \
        virtual bool init(); \

#define DECLARE_ENEMY_END(monster) \
    }; \

#define DEFINE_ENEMY(monster) \
    bool monster::init() \
    { \
        initWithEnemyId(EnemyID_##monster); \
        return true; \
    } \

// cat CommonDef.h  | grep -Eo EnemyID_[a-zA-Z_]+  | sed 's/EnemyID_//g' | sed 's/^/DECLARE_ENEMY(&/;s/$/&)/'

#endif /* defined(__TowerDefense__EnemyBase__) */
