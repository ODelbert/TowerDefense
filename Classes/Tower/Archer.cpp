#include "Archer.h"
#include "AnimationManager.h"
#include "ResourceId.h"

ArcherShooter::ArcherShooter()
: Shooter(TowerID_Archer, TowerLevel_1)
{
}

bool ArcherShooter::init()
{
    return true;
}

void ArcherShooter::shoot()
{
    AnimationManager::getInstance()->runAction(m_texture, Direction_Up == m_oriention ? AnimationTower_Archer_Shooter_Up : AnimationTower_Archer_Shooter_Down);
}

