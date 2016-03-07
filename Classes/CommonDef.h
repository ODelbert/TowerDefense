#ifndef COMMONDEF_H
#define COMMONDEF_H

#include "Base/GameManager.h"

#define TD_TEST
//#define TD_DEBUG

#define TD_WIDTH 1136
#define TD_HEIGHT 640

#define MAP_WIDTH 1200
#define MAP_HEIGHT 1000

#define TD_FONT "Arial"

#define LOGF CCLOG(__FUNCTION__); // __PRETTY_FUNCTION__

#define SPEED_RATE(x) ((x) / 500)

#define TD_LEN(x) (sizeof(x)/sizeof(x[0]))

#define TD_SIZE(x) CCLOG("%s size = %f %f", #x, x->getContentSize().width, x->getContentSize().height);
#define TD_POS(x) CCLOG("%s pos = %f %f", #x, x->getPosition().x, x->getPosition().y);

typedef unsigned int uint;
//#define SINGLETON_IMPL(class) \
//class* class::s_instance = nullptr; \
//class* class::getInstance() \
//{ \
//    if (!s_instance) { \
//        s_instance = new class; \
//    } \
//    return s_instance; \
//} \
//void class::destroy() \
//{ \
//    if (s_instance) { \
//        delete s_instance; \
//        s_instance = nullptr; \
//    } \
//} \

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

enum TowerID {
    TowerID_Invaild = -1,
    TowerID_Archer_Arcane = 0,
    TowerID_Archer_Silver = 1,
    TowerID_Artillery_Henge = 2,
    TowerID_Artillery_Thrower = 3,
    TowerID_Artillery_Tree = 4,
    TowerID_ForestKeeper = 5,
    TowerID_Mage_HighElven = 6,
    TowerID_Mage_Tower = 7,
    TowerID_Mage_Wild = 8,
    TowerID_BladeSinger = 9,
    TowerID_Archer = 10,
    TowerID_Barrack = 11,
    TowerID_Mage = 12,
    TowerID_Artillery = 13,
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

enum AllyID
{
    AllyID_Catapult = 0,
    AllyID_Ewok = 1,
    AllyID_Reinforce_A0 = 2,
    AllyID_Reinforce_A1 = 3,
    AllyID_Reinforce_A2 = 4,
    AllyID_Reinforce_A3 = 5,
    AllyID_Reinforce_B0 = 6,
    AllyID_Reinforce_B1 = 7,
    AllyID_Reinforce_B2 = 8,
    AllyID_Reinforce_B3 = 9,
    AllyID_Reinforce_C0 = 10,
    AllyID_Reinforce_C1 = 11,
    AllyID_Reinforce_C2 = 12,
    AllyID_Reinforce_C3 = 13,
};

enum HeroID {
    HeroID_Archer_Hero = 0,
    HeroID_Bravebark = 1,
    HeroID_Denas = 2,
    HeroID_Alleria = 3,
    HeroID_Arivan = 4,
    HeroID_Bolverk = 5,
    HeroID_Bruce = 6,
    HeroID_Durax = 7,
    HeroID_Regson = 8,
    HeroID_Fallen_Angel = 9,
    HeroID_Faustus = 10,
    HeroID_Wilburg = 11,
    HeroID_Lynn = 12,
    HeroID_Malik = 13,
    HeroID_Xin = 14,
    HeroID_Phoenix = 15,
    HeroID_Catha = 16,
    HeroID_RazzAndRaggs = 17,
    HeroID_Veznan = 18,
};

enum BossID
{
    BossID_Bajnimen = 0,
    BossID_Ainyl = 1,
    BossID_Boss_Godieth = 2,
    BossID_SpiderQueen = 3,
    BossID_BossHiena = 4,
};

enum Direction
{
    Direction_Invalid = -1,
    Direction_Left,
    Direction_Right,
    Direction_Down,
    Direction_Up,

    Direction_LeftDown,
    Direction_LeftUp,
    Direction_RightDown,
    Direction_RightUp
};

enum TowerLevel
{
    TowerLevel_1 = 1,
    TowerLevel_2 = 2,
    TowerLevel_3 = 3,
    TowerLevel_4 = 4,
};


#endif /* COMMONDEF_H */
