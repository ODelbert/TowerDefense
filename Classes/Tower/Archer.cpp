#include "Archer.h"
#include "Animation/AnimationManager.h"
#include "ResourceId.h"

ArcherShooter::ArcherShooter()
: Shooter(TowerID_Archer_Lv1)
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

Archer* Archer::create(TowerLevel level)
{
	Archer* ret = new Archer;
	if (ret && ret->init(level)) {
        ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool Archer::init(TowerLevel level)
{
    switch (level) {
    case TowerLevel_1:
        initWithTowerId(TowerID_Archer_Lv1, level);
        break;
    case TowerLevel_2:
        initWithTowerId(TowerID_Archer_Lv2, level);
        break;
    case TowerLevel_3:
        initWithTowerId(TowerID_Archer_Lv3, level);
        break;
    default:
        break;
    }

	return true;
}

void Archer::shoot()
{
	for (int i = 0; i < m_shooters.size(); ++i) {
		m_shooters[i]->shoot();
	}
}

bool ArcaneShooter::init()
{
    return true;
}

bool ArcaneTower::init()
{
    Tower::initWithTowerId(TowerID_Archer_Arcane, TowerLevel_4);
    return true;
}

bool SliverShooter::init()
{
    return true;
}

bool SliverTower::init()
{
    Tower::initWithTowerId(TowerID_Archer_Silver, TowerLevel_4);
    return true;
}
