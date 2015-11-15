//
//  GameData.h
//  TowerDefense
//
//  Created by jowu on 15/11/15.
//
//

#ifndef __TowerDefense__GameData__
#define __TowerDefense__GameData__

#ifdef TD_DEBUG
#include "Enemy.h"
static std::string s_enemiesIntroduction[] = {
    
};


static EnemyInfo s_enemiesInfo[] = {
//    int id;
//    char name[24];
//    int dmgMin;
//    int dmgMax;
//    int life;
//    int armor;
//    int resist;
//    int speed;
//    int food;
//    int flyable;
//    int boss;
    { 1, "gnoll_reaver", 3, 6, 50, 0, 0, 2, 1, 0, 0 },
    { 2, "gnoll_burner", 2, 4, 60, 0, 0, 2, 1, 0, 0 },
    { 3, "gnoll_gnawer", 10, 20, 250, 1, 0, 1, 1, 0, 0 },
    { 4, "hyena", 0, 0, 40, 0, 0, 3, 1, 0, 0 },
    { 5, "perython", 0, 0, 120, 0, 0, 2, 1, 1, 0 },
    { 6, "gnoll_blighter", 8, 12, 700, 0, 2, 1, 1, 0, 0 },
    { 7, "ettin", 85, 95, 900, 0, 0, 2, 2, 0, 0 },
    { 8, "harsser", 20, 30, 275, 1, 0, 2, 1, 0, 0 },
    { 9, "enha", 70, 90, 7000, 2, 0, 1, 20, 0, 1 },
    { 10, "warleader", 50, 80, 2500, 0, 0, 1, 20, 0, 0 },
    { 11, "sword_spider", 8, 12, 130, 0, 3, 2, 1, 0, 0 },
    { 12, "satyr", 6, 10, 150, 0, 0, 2, 1, 0, 0 },
    { 13, "satyr_hoplite", 25, 35, 600, 2, 0, 1, 1, 0, 0 },
    { 14, "webspitter", 10, 14, 550, 0, 2, 2, 1, 0, 0 },
    { 15, "gloomy", 0, 0, 35, 0, 0, 2, 1, 0, 1 },
    { 16, "scourger", 15, 35, 400, 0, 2, 1, 1, 0, 0 },
    { 17, "bandersnatch", 40, 60, 3000, 0, 0, 2, 2, 0, 0 },
    { 18, "redcap", 15, 25, 125, 0, 0, 2, 1, 0, 0 },
    { 19, "twilight_avenger", 50, 75, 1100, 2, 0, 1, 1, 0, 0 },
    { 20, "fungusrider_small", 0, 0, 75, 0, 0, 2, 1, 0, 0 },
    { 21, "fungusrider_medium", 5, 15, 200, 0, 0, 2, 2, 0, 0 },
    { 22, "fungusrider_big", 500, 20, 40, 0, 0, 1, 4, 0, 0 },
    { 23, "malicia", 120, 120, 9000, 0, 0, 1, 20, 0, 1 },
    { 24, "razorboar", 30, 40, 1250, 2, 0, 1, 1, 0, 0 },
    { 25, "twilight_evoker", 5, 15, 600, 0, 2, 1, 1, 0, 0 },
    { 26, "golem", 120, 180, 4000, 3, 0, 0, 3, 0, 0 },
    { 27, "mantaray", 0, 0, 90, 0, 0, 2, 1, 1, 0 },
    { 28, "spider_small", 4, 6, 100, 0, 0, 2, 1, 0, 0 },
    { 29, "twilight_heretic", 40, 50, 2000, 0, 2, 1, 2, 0, 0 },
    { 30, "son_of_mactans", 8, 12, 325, 0, 2, 2, 1, 0, 0 },
    { 31, "arachnomancer", 16, 24, 900, 0, 0, 1, 3, 0, 0 },
    { 32, "drider", 10, 20, 500, 0, 0, 2, 1, 0, 0 },
    { 33, "spider_goddness", 80, 120, 15000, 0, 1, 1, 20, 0, 1 },
    { 34, "blood_gnoll", 16, 24, 450, 0, 0, 2, 1, 0, 0 },
    { 35, "blood_warlock", 23, 30, 1250, 2, 0, 1, 1, 0, 0 },
    { 36, "ogre_mage", 48, 72, 2000, 0, 2, 1, 1, 0, 0 },
    { 37, "beheader", 100, 150, 10000, 0, 0, 1, 20, 0, 1 },
    { 38, "blood_servant", 16, 24, 200, 0, 0, 2, 1, 0, 0 },
    { 39, "screecher_bat", 0, 0, 120, 0, 0, 2, 1, 1, 0 },
    { 40, "twilight_avenger_mounted", 60, 90, 1000, 0, 1, 2, 2, 0, 0 },
    { 41, "bajnimen", 120, 150, 10000, 0, 0, 1, 20, 0, 1 },
    { 42, "twilight_bruce", 50, 80, 2500, 0, 0, 1, 20, 0, 1 },
    { 43, "shadow_spwan", 16, 24, 350, 0, 0, 2, 1, 0, 1 },
    { 44, "devourer", 32, 48, 600, 1, 0, 2, 1, 0, 0 },
    { 45, "dark_spitter", 24, 36, 800, 2, 0, 1, 1, 0, 0 },
    { 46, "champoin", 64, 96, 2500, 3, 0, 1, 3, 0, 0 },
    { 47, "Godieth", 200, 250, 12000, 0, 0, 1, 20, 0, 1 }
};

#endif





#endif /* defined(__TowerDefense__GameData__) */
