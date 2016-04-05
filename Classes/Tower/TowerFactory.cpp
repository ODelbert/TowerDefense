#include "TowerFactory.h"
#include "Tower/Archer.h"
#include "Tower/Barrack.h"
#include "Tower/Mage.hpp"

Tower* TowerFactory::create(TowerID id)
{
    Tower* tower = NULL;
    switch (id) {
    case TowerID_Archer_Lv1:
    case TowerID_Archer_Lv2:
    case TowerID_Archer_Lv3:
        tower = Archer::create(id);
        break;
    case TowerID_Archer_Arcane:
        tower = ArcaneTower::create();
        break;
    case TowerID_Archer_Silver:
        tower = SliverTower::create();
        break;
    case TowerID_Barrack_Lv1:
    case TowerID_Barrack_Lv2:
    case TowerID_Barrack_Lv3:
        tower = Barrack::create(id);
        break;
    case TowerID_ForestKeeper:
        tower = ForesetKeeperHub::create();
        break;
    case TowerID_BladeSinger:
        tower = BladeSingerHall::create();
        break;
    case TowerID_Mage_Lv1:
    case TowerID_Mage_Lv2:
    case TowerID_Mage_Lv3:
        tower = Mage::create(id);
        break;
            
    default:
        break;
    }

    return tower;
}
