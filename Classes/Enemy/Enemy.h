//
//  EnemyBase.h
//  TowerDefense
//
//  Created by jowu on 15/11/7.
//
//

#ifndef __TowerDefense__EnemyBase__
#define __TowerDefense__EnemyBase__

#include <stdio.h>

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
    EnemyID_Dark_Spitters = 9,
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
    EnemyID_Grim_Devourers = 21,
    EnemyID_Harraser = 22,
    EnemyID_Hyena = 23,
    EnemyID_Knocker = 24,
    EnemyID_Mantaray = 25,
    EnemyID_Miniboss_Gnoll = 26,
    EnemyID_MountedAvenger = 27,
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
    EnemyID_Shadow_Champion = 38,
    EnemyID_Shadow_Spawn = 39,
    EnemyID_Son_Of_Mactans = 40,
    EnemyID_Sword_Spider = 41,
    EnemyID_Tarantula = 42,
    EnemyID_TheBeheader = 43,
    EnemyID_Twilight_Avenger = 44,
    EnemyID_Twilight_Bannerbearer = 45,
    EnemyID_Twilight_Evoker = 46,
    EnemyID_Twilight_Heretic = 47,
    EnemyID_WebspitterSpider = 48,
    EnemyID_Num = EnemyID_WebspitterSpider,
};

enum EnemyState {
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

// debuff state last for seconds
enum DeBuffState {
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

#endif /* defined(__TowerDefense__EnemyBase__) */
