#include "Tower.h"
#include "Maps/BattleField.h"
#include "Shooter.h"
#include "Configuration/GameData.h"
#include "Base/GameManager.h"
#include "Enemy/Enemy.h"
#include "Bullet.h"

Tower::Tower()
    : m_id(TowerID_Invaild),
      m_level(TowerLevel_1),
      m_name("baseTower"),
      m_damageMax(0),
      m_damageMin(0),
      m_fireRate(FireRate_Invalid),
      m_range(Range_Invalid),
      m_technologyMask(0),
      m_weapon(WeaponType_Invalid),
      m_texture(nullptr),
      m_target(nullptr)
{
}

void Tower::initWithTowerId(TowerID id)
{
    m_id = id;
    TowerInfo info = s_towersInfo[id];
    m_level = static_cast<TowerLevel>(info.level);
    m_type = TowerType_Invalid; // fix later
    m_name = info.name;
    m_damageMax = info.dmgMax;
    m_damageMin = info.dmgMin;
    m_fireRate = static_cast<FireRateType>(info.fireRate);
    m_range = static_cast<RangeType>(info.range);
    m_weapon = static_cast<WeaponType>(info.weapon);
    schedule(schedule_selector(Tower::scout), 0.1f);
}

void Tower::scout(float dt)
{
    int min = -1;
    int index = -1;
    std::vector<Enemy*> enmeies = GM->getEnemies();
    for (int i = 0;i < enmeies.size(); ++i) {
        TowerSlot* slot = static_cast<TowerSlot*>(getParent());
        if (slot) {
            Vec2 towerPos = slot->getPosition();
            log("tower [%f %f] enemy [%f %f] [%d] distance [%f] ", towerPos.x, towerPos.y, enmeies[i]->getPosition().x, enmeies[i]->getPosition().y , i , towerPos.distance(enmeies[i]->getPosition()));
            if (towerPos.distance(enmeies[i]->getPosition()) > 160 + 20 * (m_range - Range_Average)) continue;
            if (enmeies[i]->fulfilledPercent() > min) {
                min = enmeies[i]->fulfilledPercent();
                index = i;
            }
        }
    }

    if (-1 == index) return;
    setTarget(enmeies[index]);
    for (int i = 0; i < m_shooters.size(); ++i) {
        if ( Shooter::State::Attack == m_shooters[i]->getState()) continue;
        if (enmeies[index]->getPosition().y > m_shooters[i]->getPosition().y &&
            Direction_Down == m_shooters[i]->getOriention()) {
            m_shooters[i]->setOriention(Direction_Up);
        }
        else if (enmeies[index]->getPosition().y < m_shooters[i]->getPosition().y &&
            Direction_Up == m_shooters[i]->getOriention()) {
            m_shooters[i]->setOriention(Direction_Down);
        }
        else {
        }

        m_shooters[i]->shoot();
        BulletEvent event(BulletEvent::Command::Lanuch, 0);
        GM->dispatchEvent(&event);
    }
}

void Tower::upgradeTechnology(int tid)
{
    log("Tower::upgradeTechnology old mask 0x%x", m_technologyMask);
    m_technologyMask = m_technologyMask & ~(0xf<<tid) | ((m_technologyMask & (0xf<<tid)) + 1);
    log("Tower::upgradeTechnology new mask 0x%x", m_technologyMask);
}

int Tower::getTechnologyRank(int tid)
{
    return (m_technologyMask & (0xf<<tid)) >> tid;
}

Vec2 Tower::getLocation()
{
    TowerSlot* slot = static_cast<TowerSlot*>(getParent());
    if (slot) {
        return slot->getPosition();
    }

    return Vec2();
}
