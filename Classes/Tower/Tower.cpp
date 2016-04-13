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

    // TODO:: fix config
//    switch (id) {
//    case TowerID_Archer_Lv1:
//    case TowerID_Archer_Lv2:
//    case TowerID_Archer_Lv3:
//        m_texture = Sprite::createWithSpriteFrameName(String::createWithFormat("archer_towers_000%d.png", static_cast<int>(id - TowerID_Archer_Lv1 + 1))->getCString());
//        break;
//    case TowerID_Archer_Arcane:
//        m_texture = Sprite::createWithSpriteFrameName("archer_towers_0004.png");
//        break;
//    case TowerID_Archer_Silver:
//        m_texture = Sprite::createWithSpriteFrameName("archer_towers_0005.png");
//        break;
//    case TowerID_Barrack_Lv1:
//    case TowerID_Barrack_Lv2:
//    case TowerID_Barrack_Lv3:
//    case TowerID_BladeSinger:
//    case TowerID_ForestKeeper:
//    {
//        // Layer1: sprite Layer2:door,init in barrack!
//        int imgIndex = 1 + (m_id - TowerID_Barrack_Lv1) * 25;
//        char* format = imgIndex < 10 ? "barracks_towers_layer1_000%d.png" : imgIndex < 100 ? "barracks_towers_layer1_00%2d" : "barracks_towers_layer1_03d";
//        m_texture = Sprite::createWithSpriteFrameName(String::createWithFormat(format, imgIndex)->getCString());
//    }
//    break;

//    case TowerID_Mage_Lv1:
//    case TowerID_Mage_Lv2:
//    case TowerID_Mage_Lv3:
//    {
//        int imgIndex = 1 + static_cast<int>(m_id - TowerID_Mage_Lv1) * 32;
//        char* format = imgIndex < 10 ? "barracks_towers_layer1_000%d.png" : "mage_towers_layer1_002d.png";
//        m_texture = Sprite::createWithSpriteFrameName(String::createWithFormat(format, imgIndex)->getCString());
//        auto ornaments = Sprite::createWithSpriteFrameName(String::createWithFormat("mage_towers_layer1_00%2d.png", static_cast<int>((id - TowerID_Mage_Lv1) * 32 + 1))->getCString());
//        m_texture = Sprite::createWithSpriteFrameName(String::createWithFormat("mage_towers_layer2_00%2d.png", static_cast<int>((id - TowerID_Mage_Lv1) * 32 + 1))->getCString());
//        m_texture->addChild(ornaments);
//    }
//    break;
//    case TowerID_Mage_Wild:
//        {
//            m_texture = Sprite::createWithSpriteFrameName("mage_towers_layer1_0097.png");
//            // mage_wild_stones_0001.png -> mage_wild_stones_00010.png 悬浮石子
//        }
//        break;
//    case TowerID_Mage_HighElven:
//        {
//            m_texture = Sprite::createWithSpriteFrameName("mage_towers_layer1_0098.png");
//        }
//        break;
//    case TowerID_Artillery_Lv1:
//    case TowerID_Artillery_Lv2:
//    case TowerID_Artillery_Lv3:
//        m_texture = Sprite::createWithSpriteFrameName(String::createWithFormat("artillery_base_000%d.png", static_cast<int>(id - TowerID_Artillery_Lv1 + 1))->getCString());
//        break;
//    case TowerID_Artillery_Henge:
//        m_texture = Sprite::createWithSpriteFrameName("archer_towers_0005.png");
//        break;
//    case TowerID_Artillery_Tree:
//        // m_texture = Sprite::createWithSpriteFrameName("archer_towers_0005.png");
//        break;
//    default:
//        break;
//    }

//    if (m_texture) {
//        addChild(m_texture);

//            //TODO: mage

//            // mage_towers_layer1_0001.png lv1外围碎石子
//            // mage_towers_layer1_0033.png lv2外围碎石子
//            // mage_towers_layer1_0065.png lv3外围碎石子
//            // mage_towers_layer2_0001.png LV1 魔法塔
//            // mage_towers_layer2_0033.png LV2 魔法塔
//            // mage_towers_layer2_0065.png LV3 魔法塔
            
//            // mage_towers_layer1_0098.png 高阶精灵塔
//            // mage_towers_layer2_0097.png 野性魔塔
//            // mage_wild_stones_0001.png -> mage_wild_stones_00010.png 悬浮石子
            
//            // TODO: artillery
            
//            // artillery_base_0001.png LV1
//            // artillery_base_0001.png LV2
//            // artillery_base_0001.png LV3
//            // artillery_base_0005.png 德鲁伊石塔

//    }
}

void Tower::scout(float dt)
{
    int min = -1;
    int index = -1;
    std::vector<Enemy*> enmeies = GM->getEnemies();

    for (int i = 0;i < enmeies.size(); ++i) {
        Vec2 towerPos = convertToWorldSpace(getPosition());

        log("enemy [%f %f] [%f %f] [%d] distance [%f] towerPos【%f %f】", getPosition().x, getPosition().y, enmeies[i]->getPosition().x, enmeies[i]->getPosition().y , i , getPosition().distance(enmeies[i]->getPosition()),
            towerPos.x, towerPos.y);
        if (towerPos.distance(enmeies[i]->getPosition()) > 160 + 20 * (m_range - Range_Average)) continue;
        if (enmeies[i]->fulfilledPercent() > min) {
            min = enmeies[i]->fulfilledPercent();
            index = i;
        }
    }

    if (-1 == index) return;
    setTarget(enmeies[index]);
    for (int i = 0; i < m_shooters.size(); ++i) {
        if ( Shooter::State::Attack == m_shooters[i]->getState()) continue;
        if (enmeies[index]->getPosition().y > m_shooters[i]->getPosition().y &&
            Direction_Down == m_shooters[i]->getOriention()) {
            m_shooters[i]->setOriention(Direction_Up);
            m_shooters[i]->shoot();

        }
        else if (enmeies[index]->getPosition().y < m_shooters[i]->getPosition().y &&
            Direction_Up == m_shooters[i]->getOriention()) {
            m_shooters[i]->setOriention(Direction_Down);
        }
        else {
        }

        BulletEvent event(BulletEvent::Command::Lanuch, 0);
        GM->dispatchEvent(&event);
//        BallBullet* ball = BallBullet::create(this);
//        addChild(ball);
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
    return convertToWorldSpace(getPosition());
}
