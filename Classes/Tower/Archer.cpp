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

Archer* Archer::create(TowerLevel level)
{
	Archer* ret = new Archer;
	if (ret && ret->init(level)) {
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool Archer::init(TowerLevel level)
{
	initWithTowerId(TowerID_Archer, level);
	return true;
}

void Archer::shoot()
{
	for (int i = 0; i < m_shooters.size(); ++i) {
		m_shooters[i]->shoot();
	}
}

void Archer::choose()
{
	switch (m_level) {
		case TowerLevel_1:
		case TowerLevel_2:
			{}
			break;
        case TowerLevel_3:
			{}
			break;
	}
}

void Archer::upgrade(int tId)
{
//    if (m_level < 4)
//        m_level++;
	

}



