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
	int seq;
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
    EnemyID_Invalid = 0,
    EnemyID_Bandersnatch = 0,
    EnemyID_BloodServant = 1,
    EnemyID_BloodsydianGnoll = 2,
    EnemyID_BloodsydianWarlock = 3,
    EnemyID_Zealot = 4,
    EnemyID_Dark_Spitters = 5,
    EnemyID_Drider = 6,
    EnemyID_Ettin = 7,
    EnemyID_Gloomy = 8,
    EnemyID_Gnoll_Blighter = 9,
    EnemyID_Gnoll_Burner = 10,
    EnemyID_Gnoll_Gnawer = 11,
    EnemyID_Gnoll_Reaver = 12,
    EnemyID_Gollem = 13,
    EnemyID_Grim_Devourers = 14,
    EnemyID_Harraser = 15,
    EnemyID_Hyena = 16,
    EnemyID_Knocker = 17,
    EnemyID_Mantaray = 18,
    EnemyID_GnollBerzerker = 19,
    EnemyID_MountedAvenger = 20,
    EnemyID_Ogre_Mage = 21,
    EnemyID_Perython = 22,
    EnemyID_Rabbit = 23,
    EnemyID_Razorboar = 24,
    EnemyID_Redcap = 25,
    EnemyID_Satyr = 26,
    EnemyID_Scourger = 27,
    EnemyID_Screecher_Bat = 28,
    EnemyID_Shadow_Champion = 29,
    EnemyID_Shadow_Spawn = 30,
    EnemyID_Son_Of_Mactans = 31,
    EnemyID_Sword_Spider = 32,
    EnemyID_Tarantula = 33,
    EnemyID_TheBeheader = 34,
    EnemyID_Twilight_Avenger = 35,
    EnemyID_Twilight_Bannerbearer = 36,
    EnemyID_Twilight_Evoker = 37,
    EnemyID_Twilight_Heretic = 38,
    EnemyID_WebspitterSpider = 39,
    EnemyID_FungusRider = 40,
    EnemyID_FungusRider_Medium = 41,
    EnemyID_FungusRider_Small = 42,
    EnemyID_Arachnomancer = 43,
    EnemyID_Arachnomancer_Mini = 44,
    EnemyID_Arachnomancer_Spider = 45,
    EnemyID_Num = EnemyID_Arachnomancer_Spider,
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

class Enemy : public Node
{
public:
	virtual void update(float dt) override;

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


#endif /* defined(__TowerDefense__EnemyBase__) */
