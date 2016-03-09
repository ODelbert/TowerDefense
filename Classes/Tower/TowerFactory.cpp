#include "TowerFactory.h"
#include "Tower/Archer.h"
#include "Tower/Barrack.h"

Tower* TowerFactory::create(TowerID id, TowerLevel level)
{
    Tower* tower = NULL;
    switch (id) {
    case TowerID_Archer_Lv1:
        tower = Archer::create(TowerID_Archer_Lv1);
        break;
    case TowerID_Archer_Lv2:
        tower = Archer::create(TowerID_Archer_Lv2);
        break;
    case TowerID_Archer_Lv3:
        tower = Archer::create(TowerID_Archer_Lv2);
        break;
    case TowerID_Archer_Arcane:
        tower = ArcaneTower::create();
        break;
    case TowerID_Archer_Silver:
        tower = SliverTower::create();
        break;

    default:
        break;
    }

    return tower;
}
