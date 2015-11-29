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

USING_NS_CC;

enum TowerType {
    TowerType_Invalid = -1,
    TowerType_Ancher = 0,
    TowerType_Barracks = 1,
    TowerType_Mage = 2,
    TowerType_Cannon = 3
};

enum WeaponType {
    WeaponType_Invalid = -1,
    WeaponType_Normal = 0,
    WeaponType_Archer = 1,
    WeaponType_Mage = 2,
    WeaponType_Bomb = 3,
};

enum ArmorType {
    ArmorType_Invalid = -1,
    ArmorType_Non = 0,
    ArmorType_Small = 1,
    ArmorType_Mid = 2,
    ArmorType_Heavy = 3,
    ArmorType_Stone = 4,
    ArmorType_Hero = 5,
    ArmorType_Holy = 6
};

enum SpeedType {
    SpeedType_VerySlow = 0,
    SpeedType_Slow,
    SpeedType_Normal,
    SpeedType_Fast,
    SpeedType_VeryFast
};

struct EnemyInfo
{
    int id;
    char name[24];
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

enum EnemyID
{
    EnemyID_Arachnomancer = 1,
    EnemyID_Arachnomancer_MiniSpider = 2,
    EnemyID_Arachnomancer_Spider = 3,
    EnemyID_Bandersnatch = 4,
    EnemyID_BloodServant = 5,
    EnemyID_BloodsydianGnoll = 6,
    EnemyID_BloodsydianWarlock = 7,
    EnemyID_Boss_Drow_Queen_Zealot = 8,
    EnemyID_Dark_Spitters = 9, //ERR
    EnemyID_Drider = 10,
    EnemyID_Ettin = 11,
    EnemyID_FungusRider = 12,
    EnemyID_FungusRider_Medium = 13,
    EnemyID_FungusRider_Small = 14, // err
    EnemyID_Gloomy = 15,
    EnemyID_Gnoll_Blighter = 16,
    EnemyID_Gnoll_Burner = 17,
    EnemyID_Gnoll_Gnawer = 18,
    EnemyID_Gnoll_Reaver = 19,
    EnemyID_Gollem = 20,
    EnemyID_Grim_Devourers = 21, // E
    EnemyID_Harraser = 22,
    EnemyID_Hyena = 23,
    EnemyID_Knocker = 24, // ?
    EnemyID_Mantaray = 25,
//    EnemyID_Miniboss_Gnoll = 26,
//    EnemyID_MountedAvenger = 27,
    EnemyID_Ogre_Mage = 28,
    EnemyID_Perython = 29,
    EnemyID_Rabbit = 30,
    EnemyID_Razorboar = 31,
    EnemyID_Redcap = 32,
    EnemyID_Satyr = 33,
    EnemyID_SatyrHoplite = 34,
    EnemyID_Scourger = 35,
    EnemyID_Scourger_Shadow = 36,
    EnemyID_Screecher_Bat = 37,
    EnemyID_Shadow_Champion = 38, // shadow_champion_animations
    EnemyID_Shadow_Spawn = 39, // shadow_spawn_animations
    EnemyID_Son_Of_Mactans = 40,
    EnemyID_Sword_Spider = 41,
    EnemyID_Tarantula = 42,
    EnemyID_TheBeheader = 43,
    EnemyID_Twilight_Avenger = 44,
    EnemyID_Twilight_Bannerbearer = 45, //
    EnemyID_Twilight_Evoker = 46,
    EnemyID_Twilight_Heretic = 47,
    EnemyID_WebspitterSpider = 48,
    EnemyID_Num = EnemyID_WebspitterSpider,
};

enum EnemyState
{
    EnemyState_Invalid = -1,
    EnemyState_AttackLeft,
    EnemyState_AttackRight,
    EnemyState_CastSpellLeft,
    EnemyState_CastSpellRight,
    EnemyState_Dead,
    EnemyState_WalkLeft,
    EnemyState_WalkRight,
    EnemyState_WalkDown,
    EnemyState_WalkUp,
    EnemyState_ChargeDown,
    EnemyState_ChargeLeft,
    EnemyState_ChargeRight,
    EnemyState_ChargeUp,
    EnemyState_SpeicalAttackLeft,
    EnemyState_SpeicalAttackRight,
    EnemyState_Appear,
    EnmeyState_Num
};

enum Direction
{
    Direction_Invalid = -1,
    Direction_Left,
    Direction_Right,
    Direction_Down,
    Direction_Up
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
    
private:
    std::vector<Vec2> m_points;
    uint m_pathIndex;
    Direction m_dir;
};

class Enemy : public Sprite
{
public:
    void sendToBattle(const std::vector<Vec2>& waypoints);
    void moveToNext(float dt);
    
    
    virtual void attack();
    virtual void idle();
    virtual void walkingLeft();
    virtual void walkingRight();
    virtual void walkingDown();
    virtual void walkingUp();
    
    virtual void death();
    virtual void spawn();
    virtual void respawn();
    virtual void shoot();
    virtual void cast();
    virtual void speicialAttack();
    
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
    Enemy();
    virtual ~Enemy();

    WayPoints m_wayPoints;
    CC_DISALLOW_COPY_AND_ASSIGN(Enemy)
};


#endif /* defined(__TowerDefense__EnemyBase__) */
