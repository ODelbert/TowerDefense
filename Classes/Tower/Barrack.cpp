#include "Barrack.h"

Barrack* Barrack::create(TowerID towerId)
{
    Barrack* ret = new Barrack;
    if (ret && ret->init(towerId)) {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Barrack::init(TowerID towerId)
{
    Tower::initWithTowerId(towerId);
    int imgIndex = 0;
    switch (towerId) {
    case TowerID_ForestKeeper:
        imgIndex = 1;
    case TowerID_BladeSinger:
    case TowerID_Barrack_Lv1:
    case TowerID_Barrack_Lv2:
    case TowerID_Barrack_Lv3:
        {
            imgIndex += m_level - TowerLevel_1;
            imgIndex *= 25;
            ++imgIndex;

            // Layer1
            const char* format = imgIndex < 10 ? "barracks_towers_layer1_000%d.png" : imgIndex < 100 ? "barracks_towers_layer1_00%2d.png" : "barracks_towers_layer1_0%3d.png";
            m_texture = Sprite::createWithSpriteFrameName(String::createWithFormat(format, imgIndex)->getCString());
            addChild(m_texture);
            if (TowerID_ForestKeeper != towerId) {
                // Layer2
                // 四个开门动画, 1->4, 26->29 ...
                const char* format2 = imgIndex < 10 ? "barracks_towers_layer2_000%d.png" : imgIndex < 100 ? "barracks_towers_layer2_00%2d.png" : "barracks_towers_layer2_0%3d.png";
                m_door = Sprite::createWithSpriteFrameName(String::createWithFormat(format2, imgIndex)->getCString());
                //addChild(m_door);
                return true;
            }
        }
        break;
    default:
        break;
    }
}

bool ForesetKeeperHub::init()
{
    Barrack::init(TowerID_ForestKeeper);
    return true;
}

bool BladeSingerHall::init()
{
    Barrack::init(TowerID_BladeSinger);
    return true;
}

