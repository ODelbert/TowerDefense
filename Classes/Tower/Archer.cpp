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
    AnimationManager::getInstance()->runAction(m_texture, Direction_Up == m_oriention ? "":"");//AID_TOWER_ARCHER_SHOOTER_UP : AID_TOWER_ARCHER_SHOOTER_DOWN);
}

Archer* Archer::create(TowerID towerId)
{
	Archer* ret = new Archer;
	if (ret && ret->init(towerId)) {
        ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool Archer::init(TowerID towerId)
{
    Tower::initWithTowerId(towerId);
    m_texture = Sprite::createWithSpriteFrameName(String::createWithFormat("archer_towers_000%d.png", static_cast<int>(towerId - TowerID_Archer_Lv1 + 1))->getCString());
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
    Tower::initWithTowerId(TowerID_Archer_Arcane);
    m_texture = Sprite::createWithSpriteFrameName("archer_towers_0004.png");
    return true;
}

bool SliverShooter::init()
{
    return true;
}

bool SliverTower::init()
{
    Tower::initWithTowerId(TowerID_Archer_Silver);
    m_texture = Sprite::createWithSpriteFrameName("archer_towers_0005.png");
    return true;
}
