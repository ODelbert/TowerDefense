//
//  TowerSlot.cpp
//  TowerDefense
//
//  Created by jowu on 15/12/30.
//
//

#include "TowerSlot.h"
#include "Sprite/Icon.h"

#define ALERT_CREEP "creepAlert.png"

#define LBL_REBOREN_CD "icon_0001.png"
#define LBL_MOVESPEED "icon_0002.png"
#define LBL_COSTFOOD "icon_0003.png"
#define LBL_ARMOR "icon_0004.png"
#define LBL_RESIST "icon_0005.png"
#define LBL_BASELIFE "icon_0006.png"
#define LBL_PHYSICDAMAGE "icon_0007.png"
#define LBL_RANGE "icon_0008.png"
#define LBL_FIRERATE "icon_0009.png"
#define LBL_MAGICDAMAGE "icon_00010.png"
#define LBL_BOWDAMAGE "icon_00011.png"
#define LBL_GUNDAMAGE "icon_00012.png"

// 默认图标/禁用图标
struct IconEntry
{
    IconEntry(const std::string& nor, const std::string& dis)
    {
        normal = nor;
        disabled = dis;
    }
    
    std::string normal;
    std::string disabled;
};

struct Location
{
    float x;
    float y;
};

static Location s_location_1[1] =
{
    { 0, 1 },
};

static Location s_location_2[2] =
{
    { -0.707, 0.707 },
    { 0.707, 0.707 }
};

static Location s_location_3[3] =
{
    { -0.5, 0.866 },
    { 0, 1 },
    { 0.5, 0.866 }
};

static Location s_location_4[4] =
{
    { -0.707, 0.707 },
    { 0.707, 0.707 },
    { 0.707, -0.707 },
    { -0.707, -0.707 }
};

class SlotRing : public Node
{
public:
    static SlotRing* create(TowerSlot* owner);
    bool init(TowerSlot* owner);
    void onTouch();
    
private:
    std::vector<std::string> getIcons();

private:
    TowerSlot* m_owner;
    Sprite* m_texture;
};

SlotRing* SlotRing::create(TowerSlot* owner)
{
    auto ring = new SlotRing;
    if (ring && ring->init(owner)) {
        ring->autorelease();
        return ring;
    }
    
    CC_SAFE_DELETE(ring);
    return nullptr;
}

bool SlotRing::init(TowerSlot *owner)
{
    m_owner = owner;
    m_texture = Sprite::createWithSpriteFrameName("gui_ring.png");

    addChild(m_texture);
    return true;
}

std::vector<IconEntry> SlotRing::getIcons()
{
    std::vector<IconEntry> ret;
    Tower* tower = m_owner->getTower();
    if (!tower) {
        ret.push_back(IconEntry(ICON_ARCHER, ICON_DISABLED_ARCHER));
        ret.push_back(IconEntry(ICON_BARRACKS, ICON_DISABLED_BARRACKS));
        ret.push_back(IconEntry(ICON_MAGE, ICON_DISABLED_));
        ret.push_back(IconEntry(ICON_ARTILLERY, ICON_DISABLED_));
        return ret;
    }
    
    if (tower->getLevel() >= TowerLevel_3) {
        switch (tower->getId()) {
            case TowerID_Archer:
            {
                ret.push_back(IconEntry(ICON_ARCANE, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_SILVER, ICON_DISABLED_));
            }
                break;
            case TowerID_Barrack:
            {
                ret.push_back(IconEntry(ICON_BLADESINGER, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_FORESTKEEPER, ICON_DISABLED_));
            }
                break;
            case TowerID_Mage:
            {
                ret.push_back(IconEntry(ICON_WILD, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_HIGHELF, ICON_DISABLED_));
            }
                break;
            case TowerID_Artillery:
            {
                ret.push_back(IconEntry(ICON_HENGE, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_TREE, ICON_DISABLED_));
            }
                break;

            // level4 towers updrage icons
            case TowerID_Archer_Arcane:
            {
                ret.push_back(IconEntry(ICON_ARCANE_1, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_ARCANE_2, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_ARCANE_3, ICON_DISABLED_));
            }
                break;
            case TowerID_Archer_Silver:
            {
                ret.push_back(IconEntry(ICON_SILVER_1, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_SILVER_2, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_SILVER_3, ICON_DISABLED_));
            }
                break;
            case TowerID_BladeSinger:
            {
                ret.push_back(IconEntry(ICON_BLADESINGER_1, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_BLADESINGER_2, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_BLADESINGER_3, ICON_DISABLED_));
            }
                break;
            case TowerID_ForestKeeper:
            {
                ret.push_back(IconEntry(ICON_FORESTKEEPER_1, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_FORESTKEEPER_2, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_FORESTKEEPER_3, ICON_DISABLED_));
            }
                break;
            case TowerID_Mage_Wild:
            {
                ret.push_back(IconEntry(ICON_WILD_1, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_WILD_2, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_WILD_3, ICON_DISABLED_));
            }
                break;
            case TowerID_Mage_HighElven:
            {
                ret.push_back(IconEntry(ICON_HIGHELF_1, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_HIGHELF_2, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_HIGHELF_3, ICON_DISABLED_));
            }
                break;
            case TowerID_Artillery_Henge:
            {
                ret.push_back(IconEntry(ICON_HENGE_1, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_HENGE_2, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_HENGE_3, ICON_DISABLED_));
            }
                break;
            case TowerID_Artillery_Tree:
            {
                ret.push_back(IconEntry(ICON_TREE_1, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_TREE_2, ICON_DISABLED_));
                ret.push_back(IconEntry(ICON_TREE_3, ICON_DISABLED_));
            }
                break;
            default:
                break;
        }
    }
    else {
        ret.push_back(ICON_UPGRADE);
    }
}

void SlotRing::onTouch()
{
    std::vector<std::string> icons = getIcons();
    m_texture->removeAllChildrenWithCleanup(true);
    for (int i = 0; i < icons.size(); ++i) {
        auto towerFrame = Sprite::createWithSpriteFrameName("main_icons_over.png");
        auto towerIcon = UpgradeIcon::create(icons[i]);
        addChild(towerFrame);
        addChild(towerIcon);
        Location locate = icons.size() == 1 ? s_location_1[i]: icons.size() == 2 ? s_location_2[i] : icons.size() == 3 ? s_location_3[i] : icons.size() == 4 ? s_location_4[i] : Location();
        towerFrame->setPosition(locate.x * m_texture->getContentSize().width / 2, locate.y * m_texture->getContentSize().height / 2);
        towerIcon->setPosition(locate.x * m_texture->getContentSize().width / 2, locate.y * m_texture->getContentSize().height / 2);
    }
}

bool TowerSlot::init()
{
    TouchNode::init("build_terrain_0001.png");
    
    m_ring = SlotRing::create(this);
    if (!m_ring) return false;
    m_ring->setPosition(0, 0);
    addChild(m_ring);
    
    setTouchCallback(CC_CALLBACK_0(TowerSlot::onTouchEvent, this));
    return true;
}

void TowerSlot::onTouchEvent()
{
    if (!m_ring) return;
    if (!m_ring->isVisible()) {
        m_ring->onTouch();
        m_ring->setVisible(true);
    }
    else
        m_ring->setVisible(false);
}

