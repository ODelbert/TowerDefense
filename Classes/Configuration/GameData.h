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
#include "Enemy.h"
#include "Tower.h"
static std::string s_enemiesIntroduction[] = {
    
};

static TowerInfo s_towersInfo[] = {
    { 1, TowerID_Archer, 1, "ArcherLevel1", 0, 0, 0, 0, 0 },
    { 2, TowerID_Archer, 2, "Archerevel2", 0, 0, 0, 0, 0 },
    { 3, TowerID_Archer, 3, "ArcherLevel3", 0, 0, 0, 0, 0 },
    { 4, TowerID_Mage, 1, "MageLevel1", 0, 0, 0, 0, 0 },
    { 5, TowerID_Mage, 2, "MageLevel2", 0, 0, 0, 0, 0 },
    { 6, TowerID_Mage, 3, "MageLevel3", 0, 0, 0, 0, 0 },
    { 7, TowerID_Artillery, 1, "ArtilleryLevel1", 0, 0, 0, 0, 0 },
    { 8, TowerID_Artillery, 2, "ArtilleryLevel2", 0, 0, 0, 0, 0 },
    { 9, TowerID_Artillery, 3, "ArtilleryLevel3", 0, 0, 0, 0, 0 },
    { 10, TowerID_Archer_Arcane, 4, "ArcherArcane", 0, 0, 0, 0, 0 },
    { 11, TowerID_Archer_Silver, 4, "ArcherSilver", 0, 0, 0, 0, 0 },
    { 12, TowerID_Mage_Wild, 4, "MageWild", 0, 0, 0, 0, 0 },
    { 13, TowerID_Mage_HighElven, 4, "MageHighElven", 0, 0, 0, 0, 0 },
    { 14, TowerID_Artillery_Henge, 4, "ArtilleryHenge", 0, 0, 0, 0, 0 },
    { 15, TowerID_Artillery_Tree, 4, "ArtilleryTree", 0, 0, 0, 0, 0 }
};

static EnemyInfo s_enemiesInfo[] = {
    { 1, EnemyID_Gnoll_Reaver, "gnoll_reaver", 3, 6, 50, 0, 0, 2, 1, 0, 0 },
    { 2, EnemyID_Gnoll_Burner, "gnoll_burner", 2, 4, 60, 0, 0, 2, 1, 0, 0 },
    { 3, EnemyID_Gnoll_Gnawer, "gnoll_gnawer", 10, 20, 250, 1, 0, 1, 1, 0, 0 },
    { 4, EnemyID_Hyena, "hyena", 0, 0, 40, 0, 0, 3, 1, 0, 0 },
    { 5, EnemyID_Perython, "perython", 0, 0, 120, 0, 0, 2, 1, 1, 0 },
    { 6, EnemyID_Gnoll_Blighter,"gnoll_blighter", 8, 12, 700, 0, 2, 1, 1, 0, 0 },
    { 7, EnemyID_Ettin, "ettin", 85, 95, 900, 0, 0, 2, 2, 0, 0 },
    { 8, EnemyID_Harraser, "harsser", 20, 30, 275, 1, 0, 2, 1, 0, 0 },
    { 9, EnemyID_Invalid, "enha", 70, 90, 7000, 2, 0, 1, 20, 0, 1 },
    { 10, EnemyID_Invalid, "warleader", 50, 80, 2500, 0, 0, 1, 20, 0, 0 },
    { 11, EnemyID_Sword_Spider, "sword_spider", 8, 12, 130, 0, 3, 2, 1, 0, 0 },
    { 12, EnemyID_Satyr, "satyr", 6, 10, 150, 0, 0, 2, 1, 0, 0 },
//    { 13, EnemyID_SatyrHoplite, "satyr_hoplite", 25, 35, 600, 2, 0, 1, 1, 0, 0 },
    { 14, EnemyID_WebspitterSpider, "webspitter", 10, 14, 550, 0, 2, 2, 1, 0, 0 },
    { 15, EnemyID_Gloomy, "gloomy", 0, 0, 35, 0, 0, 2, 1, 0, 1 },
    { 16, EnemyID_Scourger, "scourger", 15, 35, 400, 0, 2, 1, 1, 0, 0 },
    { 17, EnemyID_Bandersnatch, "bandersnatch", 40, 60, 3000, 0, 0, 2, 2, 0, 0 },
    { 18, EnemyID_Redcap, "redcap", 15, 25, 125, 0, 0, 2, 1, 0, 0 },
    { 19, EnemyID_Twilight_Avenger, "twilight_avenger", 50, 75, 1100, 2, 0, 1, 1, 0, 0 },
    { 20, EnemyID_FungusRider_Small, "fungusrider_small", 0, 0, 75, 0, 0, 2, 1, 0, 0 },
    { 21, EnemyID_FungusRider_Medium, "fungusrider_medium", 5, 15, 200, 0, 0, 2, 2, 0, 0 },
    { 22, EnemyID_FungusRider, "fungusrider_big", 500, 20, 40, 0, 0, 1, 4, 0, 0 },
    { 23, EnemyID_Invalid, "malicia", 120, 120, 9000, 0, 0, 1, 20, 0, 1 },
    { 24, EnemyID_Razorboar, "razorboar", 30, 40, 1250, 2, 0, 1, 1, 0, 0 },
    { 25, EnemyID_Twilight_Evoker, "twilight_evoker", 5, 15, 600, 0, 2, 1, 1, 0, 0 },
    { 26, EnemyID_Gollem, "gollem", 120, 180, 4000, 3, 0, 0, 3, 0, 0 },
    { 27, EnemyID_Mantaray, "mantaray", 0, 0, 90, 0, 0, 2, 1, 1, 0 },
    { 28, EnemyID_Arachnomancer_Spider, "spider_small", 4, 6, 100, 0, 0, 2, 1, 0, 0 },
    { 29, EnemyID_Twilight_Heretic, "twilight_heretic", 40, 50, 2000, 0, 2, 1, 2, 0, 0 },
    { 30, EnemyID_Son_Of_Mactans, "son_of_mactans", 8, 12, 325, 0, 2, 2, 1, 0, 0 },
    { 31, EnemyID_Arachnomancer, "arachnomancer", 16, 24, 900, 0, 0, 1, 3, 0, 0 },
    { 32, EnemyID_Drider, "drider", 10, 20, 500, 0, 0, 2, 1, 0, 0 },
    { 33, EnemyID_Invalid, "spider_goddness", 80, 120, 15000, 0, 1, 1, 20, 0, 1 },
    { 34, EnemyID_BloodsydianGnoll, "blood_gnoll", 16, 24, 450, 0, 0, 2, 1, 0, 0 },
    { 35, EnemyID_BloodsydianWarlock, "blood_warlock", 23, 30, 1250, 2, 0, 1, 1, 0, 0 },
    { 36, EnemyID_Ogre_Mage, "ogre_mage", 48, 72, 2000, 0, 2, 1, 1, 0, 0 },
    { 37, EnemyID_Invalid, "beheader", 100, 150, 10000, 0, 0, 1, 20, 0, 1 },
    { 38, EnemyID_BloodServant, "blood_servant", 16, 24, 200, 0, 0, 2, 1, 0, 0 },
    { 39, EnemyID_Screecher_Bat, "screecher_bat", 0, 0, 120, 0, 0, 2, 1, 1, 0 },
    { 40, EnemyID_MountedAvenger, "twilight_avenger_mounted", 60, 90, 1000, 0, 1, 2, 2, 0, 0 },
    { 41, EnemyID_Invalid, "bajnimen", 120, 150, 10000, 0, 0, 1, 20, 0, 1 },
    { 42, EnemyID_Invalid, "twilight_bruce", 50, 80, 2500, 0, 0, 1, 20, 0, 1 },
    { 43, EnemyID_Shadow_Spawn, "shadow_spwan", 16, 24, 350, 0, 0, 2, 1, 0, 1 },
    { 44, EnemyID_Grim_Devourers, "devourer", 32, 48, 600, 1, 0, 2, 1, 0, 0 },
    { 45, EnemyID_Dark_Spitters, "dark_spitter", 24, 36, 800, 2, 0, 1, 1, 0, 0 },
    { 46, EnemyID_Shadow_Champion, "champoin", 64, 96, 2500, 3, 0, 1, 3, 0, 0 },
    { 47, EnemyID_Invalid, "Godieth", 200, 250, 12000, 0, 0, 1, 20, 0, 1 }
};

#endif





#endif /* defined(__TowerDefense__GameData__) */
