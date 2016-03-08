//
//  Shooter.cpp
//  TowerDefense
//
//  Created by jowu on 15/12/27.
//
//

#include "Shooter.h"

#include "Animation/AnimationManager.h"
#include "ResourceId.h"

Shooter::Shooter(TowerID id)
    : m_id(id)
{
    switch (id) {
    case TowerID_Archer_Lv1:
    case TowerID_Archer_Lv2:
    case TowerID_Archer_Lv3:
        m_texture = Sprite::createWithSpriteFrameName("archer_shooter_0001.png");
        break;
    case TowerID_Mage_Lv1:
    case TowerID_Mage_Lv2:
    case TowerID_Mage_Lv3:
        m_texture = Sprite::createWithSpriteFrameName("mage_tower_shooter_0001.png");
        break;
    case TowerID_Artillery_Lv1:
        m_texture = Sprite::createWithSpriteFrameName("artillery_thrower_0001.png");
        break;
    case TowerID_Artillery_Lv2:
        m_texture = Sprite::createWithSpriteFrameName("artillery_thrower_lvl2_0001.png");
        break;
    case TowerID_Artillery_Lv3:
        m_texture = Sprite::createWithSpriteFrameName("artillery_thrower_lvl3_0001.png");
        break;
    case TowerID_Archer_Arcane:
        m_texture = Sprite::createWithSpriteFrameName("archer_arcane_shooter_0001.png");
        break;
    case TowerID_Archer_Silver:
        m_texture = Sprite::createWithSpriteFrameName("archer_silver_shooter_0001.png");
        break;
    case TowerID_Mage_HighElven:
        m_texture = Sprite::createWithSpriteFrameName("mage_highElven_shooter_0001.png");
        break;
    case TowerID_Mage_Wild:
        m_texture = Sprite::createWithSpriteFrameName("mage_wild_shooter_0001.png");
        break;
    case TowerID_Artillery_Henge:
        m_texture = Sprite::createWithSpriteFrameName("archer_shooter_0001.png");
        break;
    default:
        break;
    }

    if (!m_texture) return;
    addChild(m_texture);
}

Shooter::~Shooter()
{
}

void Shooter::shoot()
{
    switch (m_id) {
    case TowerID_Archer_Lv1:
    case TowerID_Archer_Lv2:
    case TowerID_Archer_Lv3:
        AnimationManager::getInstance()->runAction(m_texture, Direction_Up == m_oriention ? AnimationTower_Archer_Shooter_Up : AnimationTower_Archer_Shooter_Down);
        break;
    case TowerID_Mage_Lv1:
    case TowerID_Mage_Lv2:
    case TowerID_Mage_Lv3:
        AnimationManager::getInstance()->runAction(m_texture, Direction_Up == m_oriention ? AnimationTower_Mage_Tower_Shooter_ShootUp : AnimationTower_Mage_Tower_Shooter_ShootDown);
        break;
    case TowerID_Artillery_Lv1:
        AnimationManager::getInstance()->runAction(m_texture, Direction_Up == m_oriention ? AnimationTower_Artillery_Thrower_ShootUp : AnimationTower_Artillery_Thrower_ShootDown);
        break;
    case TowerID_Artillery_Lv2:
        AnimationManager::getInstance()->runAction(m_texture, Direction_Up == m_oriention ? AnimationTower_Artillery_Thrower_Lvl2_ShootUp : AnimationTower_Artillery_Thrower_Lvl2_ShootDown);
        break;
    case TowerID_Artillery_Lv3:
        AnimationManager::getInstance()->runAction(m_texture, Direction_Up == m_oriention ? AnimationTower_Artillery_Thrower_Lvl3_ShootUp : AnimationTower_Artillery_Thrower_Lvl3_ShootDown);
        break;
    default:
        break;
    }
}

Direction Shooter::getOriention()
{
    return m_oriention;
}

void Shooter::setOriention(Direction dir)
{
    switch (dir) {
        case Direction_Down:
        case Direction_LeftDown:
        case Direction_RightDown:
            m_oriention = Direction_Down;
            break;
        case Direction_Up:
        case Direction_LeftUp:
        case Direction_RightUp:
            m_oriention = Direction_Up;
            break;
        default:
            break;
    }
}
