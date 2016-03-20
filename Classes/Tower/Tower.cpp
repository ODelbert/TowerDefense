#include "Tower.h"
#include "Maps/BattleField.h"
#include "Shooter.h"

Tower::Tower()
    : m_id(TowerID_Invaild),
      m_level(TowerLevel_1),
      m_name("baseTower"),
      m_damageMax(0),
      m_damageMin(0),
      m_range(0),
      m_technologyMask(0),
      m_weapon(WeaponType_Invalid),
      m_texture(nullptr)
{
}

void Tower::initWithTowerId(TowerID id, TowerLevel level)
{
    m_id = id;
    m_level = level;
    // TODO:: fix config
    switch (id) {
    case TowerID_Archer_Lv1:
    case TowerID_Archer_Lv2:
    case TowerID_Archer_Lv3:
        m_texture = Sprite::createWithSpriteFrameName(String::createWithFormat("archer_towers_000%d.png", static_cast<int>(id - TowerID_Archer_Lv1 + 1))->getCString());
        break;
    case TowerID_Archer_Arcane:
        m_texture = Sprite::createWithSpriteFrameName("archer_towers_0004.png");
        break;
    case TowerID_Archer_Silver:
        m_texture = Sprite::createWithSpriteFrameName("archer_towers_0005.png");
        break;
    case TowerID_Barrack_Lv1:
    case TowerID_Barrack_Lv2:
    case TowerID_Barrack_Lv3:
        m_texture = Sprite::createWithSpriteFrameName(String::createWithFormat("archer_towers_000%d.png", static_cast<int>(id - TowerID_Archer_Lv1 + 1))->getCString());
        break;
    case TowerID_ForestKeeper:
        m_texture = Sprite::createWithSpriteFrameName("archer_towers_0004.png");
        break;
    case TowerID_BladeSinger:
        m_texture = Sprite::createWithSpriteFrameName("archer_towers_0005.png");
        break;
    case TowerID_Mage_Lv1:
    case TowerID_Mage_Lv2:
    case TowerID_Mage_Lv3:
        {
            auto ornaments = Sprite::createWithSpriteFrameName(String::createWithFormat("mage_towers_layer1_00%2d.png", static_cast<int>((id - TowerID_Mage_Lv1) * 32 + 1))->getCString());
            m_texture = Sprite::createWithSpriteFrameName(String::createWithFormat("mage_towers_layer2_00%2d.png", static_cast<int>((id - TowerID_Mage_Lv1) * 32 + 1))->getCString());
            m_texture->addChild(ornaments);
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
    case TowerID_Artillery_Lv1:
    case TowerID_Artillery_Lv2:
    case TowerID_Artillery_Lv3:
        m_texture = Sprite::createWithSpriteFrameName(String::createWithFormat("artillery_base_000%d.png", static_cast<int>(id - TowerID_Artillery_Lv1 + 1))->getCString());
        break;
    case TowerID_Artillery_Henge:
        m_texture = Sprite::createWithSpriteFrameName("archer_towers_0005.png");
        break;
    case TowerID_Artillery_Tree:
        // m_texture = Sprite::createWithSpriteFrameName("archer_towers_0005.png");
        break;
    default:
        break;
    }

    if (m_texture) {
        addChild(m_texture);

            //TODO: mage

            // mage_towers_layer1_0001.png lv1外围碎石子
            // mage_towers_layer1_0033.png lv2外围碎石子
            // mage_towers_layer1_0065.png lv3外围碎石子
            // mage_towers_layer2_0001.png LV1 魔法塔
            // mage_towers_layer2_0033.png LV2 魔法塔
            // mage_towers_layer2_0065.png LV3 魔法塔
            
            // mage_towers_layer1_0098.png 高阶精灵塔
            // mage_towers_layer2_0097.png 野性魔塔
            // mage_wild_stones_0001.png -> mage_wild_stones_00010.png 悬浮石子
            
            // TODO: artillery
            
            // artillery_base_0001.png LV1
            // artillery_base_0001.png LV2
            // artillery_base_0001.png LV3
            // artillery_base_0005.png 德鲁伊石塔

    }
}

void Tower::detectNearBy()
{
    BattleField* map = static_cast<BattleField*>(this->getParent());
    if (map) {
        int min = -1;
        int index = -1;
        const std::vector<Enemy*> enmeies = map->getEnemies();
        for (int i = 0;i < enmeies.size(); ++i) {
            if (getPosition().distance(enmeies[i]->getPosition()) > m_range) continue;
            if (enmeies[i]->fulfilledPercent() > min) {
                min = enmeies[i]->fulfilledPercent();
                index = i;
            }
        }

		for (int i = 0; i < m_shooters.size(); ++i) {
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
		}
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
