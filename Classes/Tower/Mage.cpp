//
//  Mage.cpp
//  TowerDefense
//
//  Created by jowu on 16/3/18.
//
//

#include "Mage.hpp"

MageShooter::MageShooter()
: Shooter(TowerID_Mage_Lv1) {
    
}

bool MageShooter::init()
{
    return true;
}

void MageShooter::shoot()
{
    Animation* shootAnim = AnimationCache::getInstance()->getAnimation(Direction_Up == m_oriention ? AID_TOWER_MAGE_TOWER_SHOOTER_SHOOTUP : AID_TOWER_MAGE_TOWER_SHOOTER_SHOOTDOWN);
    if (m_texture) {
        m_texture->runAction(Animate::create(shootAnim));
    }
}

Mage* Mage::create(TowerID towerId)
{
    Mage* ret = new Mage;
    if (ret && ret->init(towerId)) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Mage::init(TowerID towerId)
{
    Tower::initWithTowerId(towerId);
    switch (towerId) {
    case TowerID_Mage_Lv1:
    case TowerID_Mage_Lv2:
    case TowerID_Mage_Lv3:
    {
        int imgIndex = 1 + static_cast<int>(m_id - TowerID_Mage_Lv1) * 32;
        const char* format = imgIndex < 10 ? "mage_towers_layer%d_000%d.png" : "mage_towers_layer%d_00%2d.png";
        m_texture = Sprite::createWithSpriteFrameName(String::createWithFormat(format, 2, imgIndex)->getCString());
        auto ornaments = Sprite::createWithSpriteFrameName(String::createWithFormat(format, 1, imgIndex)->getCString());
        addChild(ornaments);
        addChild(m_texture);
    }
    break;
    case TowerID_Mage_Wild:
        {
            m_texture = Sprite::createWithSpriteFrameName("mage_towers_layer1_0097.png");
            // mage_wild_stones_0001.png -> mage_wild_stones_00010.png 悬浮石子
        }
        break;
    case TowerID_Mage_HighElven:
        {
            m_texture = Sprite::createWithSpriteFrameName("mage_towers_layer1_0098.png");
        }
        break;
    default:
        break;
    }

    if (!m_texture) {
        return false;
    }

    return true;
}

void Mage::shoot()
{
    for (int i = 0; i < m_shooters.size(); ++i) {
        m_shooters[i]->shoot();
    }
}
