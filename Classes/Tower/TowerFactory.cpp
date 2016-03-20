#include "TowerFactory.h"
#include "Tower/Archer.h"
#include "Tower/Barrack.h"

Tower* TowerFactory::create(TowerID id)
{
    Tower* tower = NULL;
    switch (id) {
    case TowerID_Archer_Lv1:
        tower = Archer::create(TowerLevel_1);
        break;
    case TowerID_Archer_Lv2:
        tower = Archer::create(TowerLevel_2);
        break;
    case TowerID_Archer_Lv3:
        tower = Archer::create(TowerLevel_3);
        break;
    case TowerID_Archer_Arcane:
        tower = ArcaneTower::create();
        break;
    case TowerID_Archer_Silver:
        tower = SliverTower::create();
        break;
    case TowerID_Barrack_Lv1:
        tower = Barrack::create(TowerLevel_1);
        break;
    case TowerID_Barrack_Lv2:
        tower = Barrack::create(TowerLevel_2);
        break;
    case TowerID_Barrack_Lv3:
        tower = Barrack::create(TowerLevel_3);
        break;
    case TowerID_ForestKeeper:
        tower = ForesetKeeperHub::create();
        break;
    case TowerID_BladeSinger:
        tower = BladeSingerHall::create();
        break;
            
    default:
        break;
    }

    return tower;
}
