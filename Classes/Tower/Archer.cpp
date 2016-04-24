#include "Archer.h"
#include "Animation/AnimationManager.h"
#include "Base/GameManager.h"
#include "ResourceId.h"
#include "Sprite/TouchNode.h"
#include "Tower/Bullet.h"

class PositionAdpater : public TouchNode
{
public:
    CREATE_FUNC(PositionAdpater)
    bool init();
    bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    
private:
    Vec2 m_lastPos;
};

bool PositionAdpater::init()
{
    auto touchReceiver = Sprite::createWithSpriteFrameName("archer_shooter_0001.png");
    addChild(touchReceiver);
    initWithTouchReceiver(touchReceiver);
    return true;
}

bool PositionAdpater::onTouchBegan(Touch* touch, Event* event)
{
    m_lastPos = convertToNodeSpace(touch->getLocation());
    return TouchNode::onTouchBegan(touch, event);
}

void PositionAdpater::onTouchMoved(Touch* touch, Event* event)
{
    Vec2 deltaPos = convertToNodeSpace(touch->getLocation()) - m_lastPos;
//    log("touch->getLocation(): %f %f", touch->getLocation().x, touch->getLocation().y);
//    log("convertToNodeSpace(touch->getLocation()): %f %f", convertToNodeSpace(touch->getLocation()).x, convertToNodeSpace(touch->getLocation()).y);
//    log("convertToWorldSpace(touch->getLocation()): %f %f", convertToWorldSpace(touch->getLocation()).x, convertToWorldSpace(touch->getLocation()).y);
    
    Sprite* tower = dynamic_cast<Sprite*>(getParent());
    if (tower) {
        log("tower pos [%f %f] shooter pos[%f %f] detla[%f %f]", tower->getPosition().x, tower->getPosition().y, getPosition().x, getPosition().y, convertToNodeSpace(tower->getPosition()).x, convertToNodeSpace(tower->getPosition()).y);
    }
    
    setPosition(getPosition().x + deltaPos.x, getPosition().y + deltaPos.y);
    m_lastPos = convertToNodeSpace(touch->getLocation());
}

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
    // TODO::fix attack rate!
    Animation* shootAnim = AnimationCache::getInstance()->getAnimation(Direction_Up == m_oriention ? AID_TOWER_ARCHER_SHOOTER_UP : AID_TOWER_ARCHER_SHOOTER_DOWN);
    if (m_texture) {
        setState(Shooter::State::Attack);
        m_texture->runAction(Sequence::create(Animate::create(shootAnim), /*DelayTime::create(0.01)*/ CallFunc::create([&]() {
            setState(Shooter::State::Idel);
        }), nullptr));
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
    // init shooters
    switch (towerId) {
    case TowerID_Archer_Lv1:
    {
        auto* shooter = ArcherShooter::create();
        m_texture->addChild(shooter, 1);
        m_shooters.push_back(shooter);
        shooter->setPosition(m_texture->getPosition().x + m_texture->getContentSize().width / 2, m_texture->getPosition().y + m_texture->getContentSize().height / 2);
    }
        break;
    case TowerID_Archer_Lv2:
    {
        const static Vec2 s_pos2[2] = { { 46, 56 }, { 82, 64 } };
        for (int i = 0; i < 2; ++i) {
            auto st = PositionAdpater::create();
            m_texture->addChild(st);
            st->setPosition(s_pos2[i]);
        }
    }
        break;
    case TowerID_Archer_Lv3:
    {
        const static Vec2 s_pos3[3] = { { 46, 56 }, { 82, 64 }, { 60, 82 } };
        for (int i = 0; i < 3; ++i) {
            auto st = PositionAdpater::create();
            m_texture->addChild(st);
            st->setPosition(s_pos3[i]);
        }
    }
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

void ArcaneShooter::shoot()
{
    // AID_TOWER_ARCHER_ARCANE_SHOOTER_SPECIALDOWN
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
