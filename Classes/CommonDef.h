#ifndef COMMONDEF_H
#define COMMONDEF_H
#include<random>
#include "ResourceId.h"
#define TD_TEST
//#define TD_DEBUG

#define TD_WIDTH 1136
#define TD_HEIGHT 640

#define MAP_WIDTH 1200
#define MAP_HEIGHT 1000

#define TD_FONT "Arial"

#define LOGF CCLOG(__FUNCTION__); // __PRETTY_FUNCTION__

#define TD_LEN(x) (sizeof(x)/sizeof(x[0]))

#define TD_SIZE(x) CCLOG("%s size = %f %f", #x, x->getContentSize().width, x->getContentSize().height);
#define TD_POS(x) CCLOG("%s pos = %f %f", #x, x.x, x.y);
#define TD_POS_NODE(x) CCLOG("%s pos = %f %f", #x, convertToNodeSpace(x.x, convertToNodeSpace(x.y);
#define TD_POS_WORLD(x) CCLOG("%s pos = %f %f", #x, convertToWorldSpace(x.x, convertToWorldSpace(x.y);

#define TD_SYNTHESIZE_CHECK(varType, varName, funName)\
protected: varType varName;\
public: virtual varType is##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

static float RAND_FLOAT(float min, float max)
{
    std::default_random_engine random(time(NULL));
    std::uniform_real_distribution<double> dis(min, max);
    return dis(random);
}

static int RAND_INT(int min, int max)
{
    std::default_random_engine random(time(NULL));
    std::uniform_int_distribution<int> dis(min, max);
    return dis(random);
}

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

enum FireRateType {
    FireRate_Invalid = -1,
    FireRate_VerySlow,
    FireRate_Slow,
    FireRate_Normal,
    FireRate_Fast,
    FireRate_VeryFast,
};

enum RangeType {
    Range_Invalid = -1,
    Range_Short,
    Range_Average,
    Range_Long,
    Range_Great,
    Range_Extreme,
};

enum WeaponType {
    WeaponType_Invalid = -1,
    WeaponType_Normal = 0,
    WeaponType_Archer = 1,
    WeaponType_Mage = 2,
    WeaponType_Artillery = 3,
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
    TowerID_Archer_Lv1,
    TowerID_Archer_Lv2,
    TowerID_Archer_Lv3,
    TowerID_Barrack_Lv1,
    TowerID_Barrack_Lv2,
    TowerID_Barrack_Lv3,
    TowerID_Mage_Lv1,
    TowerID_Mage_Lv2,
    TowerID_Mage_Lv3,
    TowerID_Artillery_Lv1,
    TowerID_Artillery_Lv2,
    TowerID_Artillery_Lv3,

    TowerID_Archer_Arcane,
    TowerID_Archer_Silver,
    TowerID_BladeSinger,
    TowerID_ForestKeeper,
    TowerID_Mage_Wild,
    TowerID_Mage_HighElven,
    TowerID_Artillery_Henge,
    TowerID_Artillery_Tree,
};

enum EnemyID
{
    EnemyID_Invalid = -1,
    EnemyID_Gnoll_Reaver,
    EnemyID_Gnoll_Burner,
    EnemyID_Gnoll_Gnawer,
    EnemyID_Hyena,
    EnemyID_Perython,
    EnemyID_Gnoll_Blighter,
    EnemyID_Ettin,
    EnemyID_Harraser,
    EnemyID_Sword_Spider,
    EnemyID_Satyr,
    EnemyID_SatyrHoplite,
    EnemyID_WebspitterSpider,
    EnemyID_Gloomy,
    EnemyID_Scourger,
    EnemyID_Bandersnatch,
    EnemyID_Redcap,
    EnemyID_Twilight_Avenger,
    EnemyID_FungusRider_Small,
    EnemyID_FungusRider_Medium,
    EnemyID_FungusRider,
    EnemyID_Razorboar,
    EnemyID_Twilight_Evoker,
    EnemyID_Gollem,
    EnemyID_Mantaray,
    EnemyID_Arachnomancer_Spider,
    EnemyID_Twilight_Heretic,
    EnemyID_Son_Of_Mactans,
    EnemyID_Arachnomancer,
    EnemyID_Drider,
    EnemyID_BloodsydianGnoll,
    EnemyID_BloodsydianWarlock,
    EnemyID_Ogre_Mage,
    EnemyID_BloodServant,
    EnemyID_Screecher_Bat,
    EnemyID_MountedAvenger,
    EnemyID_Shadow_Spawn,
    EnemyID_Grim_Devourers,
    EnemyID_Dark_Spitters,
    EnemyID_Shadow_Champion,
    EnemyID_Zealot,
    EnemyID_Num = EnemyID_Zealot,
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
