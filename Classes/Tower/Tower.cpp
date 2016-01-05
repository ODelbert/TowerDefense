
#include "Tower.h"
#include "BattleField.h"
#include "Shooter.h"

void Tower::initWithTowerId(TowerID id, TowerLevel level)
{
    // TODO:: fix config
    m_name = "baseTower";
    m_damageMin = 0;
    m_damageMax = 0;
    m_fireRate = 0;
    m_range = 0;
    m_weapon = WeaponType_Invalid;
    
    switch (id) {
        case TowerID_Archer:
            switch (level) {
                case TowerLevel_1:
                    m_texture = Sprite::createWithSpriteFrameName("archer_towers_0001.png");
                    break;
                case TowerLevel_2:
                    m_texture = Sprite::createWithSpriteFrameName("archer_towers_0002.png");
                    break;
                case TowerLevel_3:
                    m_texture = Sprite::createWithSpriteFrameName("archer_towers_0003.png");
                    break;
                default:
                    break;
            }
            break;
        case TowerID_Archer_Arcane:
            m_texture = Sprite::createWithSpriteFrameName("archer_towers_0004.png");
            break;
        case TowerID_Archer_Silver:
            m_texture = Sprite::createWithSpriteFrameName("archer_towers_0005.png");
            break;
            
        default:
            break;
            
            
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

void Tower::showTowerInfo()
{
    // TODO:: UI
}

int Tower::sell()
{
    return 0.7 * m_costGold;
}

bool Tower::isLimitTechnology() const
{
    return m_limitLevel < TowerLevel_4;
}
void Tower::setLimitTechnology(TowerLevel level)
{
    m_limitLevel = level;
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