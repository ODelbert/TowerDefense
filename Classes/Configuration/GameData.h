//
//  GameData.h
//  TowerDefense
//
//  Created by jowu on 15/11/15.
//
//

#ifndef __TowerDefense__GameData__
#define __TowerDefense__GameData__
#define TD_DEBUG
#ifdef TD_DEBUG
#include "Enemy/Enemy.h"
#include "Tower/Tower.h"

/*
 struct TowerInfo
 {
 int id;
 int level;
 char name[24];
 int dmgMin;
 int dmgMax;
 int range; // pix
 int fireRate; // attack rate pre second
 int weapon;
 int gold;
 int upgradeGold;
 };
 */
static TowerInfo s_towersInfo[] = {
    { TowerID_Archer_Lv1, 1, "ArcherLevel1", 2, 5, Range_Average, FireRate_Fast, WeaponType_Archer },
    { TowerID_Archer_Lv2, 2, "Archerevel2", 4, 9, Range_Long, FireRate_Fast, WeaponType_Archer },
    { TowerID_Archer_Lv3, 3, "ArcherLevel3", 5, 11, Range_Great, FireRate_VeryFast, WeaponType_Archer },
    { TowerID_Barrack_Lv1, 1, "BarrackLevel1", 0, 0, 0, 0, 0 },
    { TowerID_Barrack_Lv2, 2, "BarrackLevel2", 0, 0, 0, 0, 0 },
    { TowerID_Barrack_Lv3, 3, "BarrackLevel3", 0, 0, 0, 0, 0 },
    { TowerID_Mage_Lv1, 1, "MageLevel1", 8, 12, Range_Short, FireRate_Slow, WeaponType_Mage },
    { TowerID_Mage_Lv2, 2, "MageLevel2", 18, 30, Range_Average, FireRate_Slow, WeaponType_Mage },
    { TowerID_Mage_Lv3, 3, "MageLevel3", 34, 56, Range_Long, FireRate_Slow, WeaponType_Mage },
    { TowerID_Artillery_Lv1, 1, "ArtilleryLevel1", 7, 12, Range_Short, FireRate_VerySlow, WeaponType_Artillery },
    { TowerID_Artillery_Lv2, 2, "ArtilleryLevel2", 18, 30, Range_Average, FireRate_VerySlow, WeaponType_Artillery },
    { TowerID_Artillery_Lv3, 3, "ArtilleryLevel3", 30, 50, Range_Long, FireRate_VerySlow, WeaponType_Artillery },
    { TowerID_Archer_Arcane, 4, "ArcherArcane", 22, 36, Range_Great, FireRate_Normal, WeaponType_Archer },
    { TowerID_Archer_Silver, 4, "ArcherSilver", 45, 60, Range_Extreme, FireRate_Slow, WeaponType_Archer },
    { TowerID_Mage_Wild, 4, "MageWild", 8, 16, Range_Long, FireRate_VeryFast,  WeaponType_Mage},
    { TowerID_Mage_HighElven, 4, "MageHighElven", 41, 74, Range_Long, FireRate_Slow, WeaponType_Mage },
    { TowerID_Artillery_Henge, 4, "ArtilleryHenge", 30, 50, Range_Long, FireRate_Fast, WeaponType_Artillery },
    { TowerID_Artillery_Tree, 4, "ArtilleryTree", 62, 106, Range_Great, FireRate_VerySlow, WeaponType_Artillery }
};

//'arachnomancer_spider', \
//'gnollBerzerker', \  // boss
//'rabbit', \
//'tarantula', \  // >
//'theBeheader', \ // boss
//'twilight_bannerbearer', \ // boss

static EnemyInfo s_enemiesInfo[] = {
    { EnemyID_Gnoll_Reaver, "gnoll_reaver", 3, 6, 50, 0, 0, 2, 1, 0, 0 },
    { EnemyID_Gnoll_Burner, "gnoll_burner", 2, 4, 60, 0, 0, 2, 1, 0, 0 },
    { EnemyID_Gnoll_Gnawer, "gnoll_gnawer", 10, 20, 250, 1, 0, 1, 1, 0, 0 },
    { EnemyID_Hyena, "hyena", 0, 0, 40, 0, 0, 3, 1, 0, 0 },
    { EnemyID_Perython, "perython", 0, 0, 120, 0, 0, 2, 1, 1, 0 },
    { EnemyID_Gnoll_Blighter,"gnoll_blighter", 8, 12, 700, 0, 2, 1, 1, 0, 0 },
    { EnemyID_Ettin, "ettin", 85, 95, 900, 0, 0, 2, 2, 0, 0 },
    { EnemyID_Harraser, "harsser", 20, 30, 275, 1, 0, 2, 1, 0, 0 },
//    { 9, EnemyID_Invalid, "enha", 70, 90, 7000, 2, 0, 1, 20, 0, 1 },
//    { 10, EnemyID_Invalid, "warleader", 50, 80, 2500, 0, 0, 1, 20, 0, 0 },
    { EnemyID_Sword_Spider, "sword_spider", 8, 12, 130, 0, 3, 2, 1, 0, 0 },
    { EnemyID_Satyr, "satyr", 6, 10, 150, 0, 0, 2, 1, 0, 0 },
    { EnemyID_SatyrHoplite, "satyr_hoplite", 25, 35, 600, 2, 0, 1, 1, 0, 0 },
    { EnemyID_WebspitterSpider, "webspitter", 10, 14, 550, 0, 2, 2, 1, 0, 0 },
    { EnemyID_Gloomy, "gloomy", 0, 0, 35, 0, 0, 2, 1, 0, 1 },
    { EnemyID_Scourger, "scourger", 15, 35, 400, 0, 2, 1, 1, 0, 0 },
    { EnemyID_Bandersnatch, "bandersnatch", 40, 60, 3000, 0, 0, 2, 2, 0, 0 },
    { EnemyID_Redcap, "redcap", 15, 25, 125, 0, 0, 2, 1, 0, 0 },
    { EnemyID_Twilight_Avenger, "twilight_avenger", 50, 75, 1100, 2, 0, 1, 1, 0, 0 },
    { EnemyID_FungusRider_Small, "fungusrider_small", 0, 0, 75, 0, 0, 2, 1, 0, 0 },
    { EnemyID_FungusRider_Medium, "fungusrider_medium", 5, 15, 200, 0, 0, 2, 2, 0, 0 },
    { EnemyID_FungusRider, "fungusrider_big", 500, 20, 40, 0, 0, 1, 4, 0, 0 },
//    { 23, EnemyID_Invalid, "malicia", 120, 120, 9000, 0, 0, 1, 20, 0, 1 },
    { EnemyID_Razorboar, "razorboar", 30, 40, 1250, 2, 0, 1, 1, 0, 0 },
    { EnemyID_Twilight_Evoker, "twilight_evoker", 5, 15, 600, 0, 2, 1, 1, 0, 0 },
    { EnemyID_Gollem, "gollem", 120, 180, 4000, 3, 0, 0, 3, 0, 0 },
    { EnemyID_Mantaray, "mantaray", 0, 0, 90, 0, 0, 2, 1, 1, 0 },
    { EnemyID_Arachnomancer_Spider, "spider_small", 4, 6, 100, 0, 0, 2, 1, 0, 0 },
    { EnemyID_Twilight_Heretic, "twilight_heretic", 40, 50, 2000, 0, 2, 1, 2, 0, 0 },
    { EnemyID_Son_Of_Mactans, "son_of_mactans", 8, 12, 325, 0, 2, 2, 1, 0, 0 },
    { EnemyID_Arachnomancer, "arachnomancer", 16, 24, 900, 0, 0, 1, 3, 0, 0 },
    { EnemyID_Drider, "drider", 10, 20, 500, 0, 0, 2, 1, 0, 0 },
//    { 33, EnemyID_Invalid, "spider_goddness", 80, 120, 15000, 0, 1, 1, 20, 0, 1 },
    { EnemyID_BloodsydianGnoll, "blood_gnoll", 16, 24, 450, 0, 0, 2, 1, 0, 0 },
    { EnemyID_BloodsydianWarlock, "blood_warlock", 23, 30, 1250, 2, 0, 1, 1, 0, 0 },
    { EnemyID_Ogre_Mage, "ogre_mage", 48, 72, 2000, 0, 2, 1, 1, 0, 0 },
//    { 37, EnemyID_Invalid, "beheader", 100, 150, 10000, 0, 0, 1, 20, 0, 1 },
    { EnemyID_BloodServant, "blood_servant", 16, 24, 200, 0, 0, 2, 1, 0, 0 },
    { EnemyID_Screecher_Bat, "screecher_bat", 0, 0, 120, 0, 0, 2, 1, 1, 0 },
    { EnemyID_MountedAvenger, "twilight_avenger_mounted", 60, 90, 1000, 0, 1, 2, 2, 0, 0 },
//    { 41, EnemyID_Invalid, "bajnimen", 120, 150, 10000, 0, 0, 1, 20, 0, 1 },
//    { 42, EnemyID_Invalid, "twilight_bruce", 50, 80, 2500, 0, 0, 1, 20, 0, 1 },
    { EnemyID_Shadow_Spawn, "shadow_spwan", 16, 24, 350, 0, 0, 2, 1, 0, 1 },
    { EnemyID_Grim_Devourers, "devourer", 32, 48, 600, 1, 0, 2, 1, 0, 0 },
    { EnemyID_Dark_Spitters, "dark_spitter", 24, 36, 800, 2, 0, 1, 1, 0, 0 },
    { EnemyID_Shadow_Champion, "champoin", 64, 96, 2500, 3, 0, 1, 3, 0, 0 },
    { EnemyID_Zealot, "zealot", 6, 10, 100, 0, 0, 2, 1, 0, 0 }
//    { 47, EnemyID_Invalid, "Godieth", 200, 250, 12000, 0, 0, 1, 20, 0, 1 }
};

#endif
#endif /* defined(__TowerDefense__GameData__) */
