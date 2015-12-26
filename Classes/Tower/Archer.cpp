#include "Archer.h"
#include "AnimationManager.h"


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
    TowerID_Mage = 11,
    TowerID_Artillery = 12,
    TowerID_Barrack = 13,

static const std::string s_shooterName[] = 
{
    "archer_arcane_shooter_0001.png",
    "archer_silver_shooter_0001.png",
    "archer_shooter_0001.png",
    "mage_highElven_shooter_0001.png"
    "mage_tower_shooter_0001.png"
};

artillery_thrower_0001.png
    "artillery_thrower_lvl2_0001.png"

"artillery_thrower_lvl3_0001.png"
Archer* Archer::createArcherTower(TowerLevel level)
{
    if ()
}

void Archer::shoot()
{
    switch (m_level) {
        case TowerLevel_1:
            AnimationManager::getInstance()->runAction(this, AnimationTower_Mage_Towers_Lvl1_Shoot);
            break;
        case TowerLevel_2:
            AnimationManager::getInstance()->runAction(this, AnimationTower_Mage_Towers_Lvl1_Shoot);
            break;
        case TowerLevel_2:
            AnimationManager::getInstance()->runAction(this, AnimationTower_Mage_Towers_Lvl1_Shoot);
            break;
        default:
            break;
    }
}

void Archer::idel()
{
    switch (m_level) {
        case TowerLevel_1:
            AnimationManager::getInstance()->runAction(this, AnimationTower_Mage_Towers_Lvl1_Shoot);
            break;
        case TowerLevel_2:
            AnimationManager::getInstance()->runAction(this, AnimationTower_Mage_Towers_Lvl1_Shoot);
            break;
        case TowerLevel_2:
            AnimationManager::getInstance()->runAction(this, AnimationTower_Mage_Towers_Lvl1_Shoot);
            break;
        default:
            break;
    }
}
