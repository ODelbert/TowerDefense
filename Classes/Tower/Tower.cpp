
#include "Tower.h"

Shooter* Shooter::createShooter(TowerID id)
{
    auto me = new Shooter;
    if (me && me->init()) {
        me->autoRelease();
        return me;
    }

    CC_SAFE_DELETE(me);
    return nullptr;
}

bool Shooter::init()
{
    m_texture = Sprite::createWithFrameName();
    if (!m_texture) m_texture = Sprite::createWithFrameName("redcap_0001.png");
    addChild(m_texture);
    return true;
}

void setOriention(Direction dir)
{
    switch (dir) {
        case Direction_Down:
        case Direction_LeftDown:
        case Direction_RightDown:
            m_dir = Direction_Down;
            break;
        case Direction_Up:
        case Direction_LeftUp:
        case Direction_RightUp:
            m_dir = Direction_Up;
            break;
        default:
            break;
    }
}

void Tower::initWithTowerId(TowerID id)
{
    // TODO:: config
    m_name = "baseTower";
    m_damageMin = 0;
    m_damageMax = 0;
    m_fireRate = 0;
    m_range = 0;
    m_weapon = WeaponType_Invalid;
}

void Tower::showTowerInfo()
{
    // TODO:: UI
}

int Tower::Towersell()
{
    return 0.7 * m_costGold;
}

bool Tower::isLimitTechnology() const
{
    return m_maxLevel < TowerLevel_4;
}
void Tower::setLimitTechnology(TowerLevel level)
{
    m_maxLevel = level;
}

