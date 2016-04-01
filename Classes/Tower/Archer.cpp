#include "Archer.h"
#include "Animation/AnimationManager.h"
#include "Base/GameManager.h"
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
//    auto shitBullet = [&]()
//    {
//        Bullet* arrow = Arrow::create();
//        BulletEvent be;
//        GM->dispatchEvent();
//    };
    Animation* shootAnim = AnimationCache::getInstance()->getAnimation(Direction_Up == m_oriention ? AID_TOWER_ARCHER_SHOOTER_UP : AID_TOWER_ARCHER_SHOOTER_DOWN);
    if (m_texture) {
        m_texture->runAction(Animate::create(shootAnim));
    }
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
    if (!m_texture) {
        return false;
    }
    
    addChild(m_texture);
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

void ArcaneShooter::shoot()
{
    // AID_TOWER_ARCHER_ARCANE_SHOOTER_SPECIALDOWN
    //
    Animation* shootAnim = AnimationCache::getInstance()->getAnimation(Direction_Up == m_oriention ? AID_TOWER_ARCHER_ARCANE_SHOOTER_SHOOTUP : AID_TOWER_ARCHER_ARCANE_SHOOTER_SHOOTDOWN);
    if (m_texture) {
        m_texture->runAction(Animate::create(shootAnim));
    }
}

bool ArcaneTower::init()
{
    Tower::initWithTowerId(TowerID_Archer_Arcane);
    m_texture = Sprite::createWithSpriteFrameName("archer_towers_0004.png");
    if (!m_texture) {
        return false;
    }

    addChild(m_texture);
    return true;
}

bool SliverShooter::init()
{
    return true;
}

void SliverShooter::shoot()
{
}

bool SliverTower::init()
{
    Tower::initWithTowerId(TowerID_Archer_Silver);
    m_texture = Sprite::createWithSpriteFrameName("archer_towers_0005.png");
    if (!m_texture) {
        return false;
    }

    addChild(m_texture);
    return true;
}
