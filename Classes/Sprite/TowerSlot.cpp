//
//  TowerSlot.cpp
//  TowerDefense
//
//  Created by jowu on 15/12/30.
//
//

#include "TowerSlot.h"
#include "Sprite/Icon.h"

// Tower upgrade icons
#define ICON_UPGRADE "main_icons_0005.png"
#define ICON_LOCK "main_icons_0005.png"
#define ICON_UPGRADE "main_icons_0014.png"
#define ICON_HARMMER "main_icons_0015.png"
#define ICON_CONFRIM "main_icons_0019.png"
#define ICON_ARCHER "main_icons_0100.png"
#define ICON_BARRACKS "main_icons_0101.png"
#define ICON_MAGE "main_icons_0102.png"
#define ICON_ARTILLERY "main_icons_0103.png"
#define ICON_BLADESINGER "main_icons_0104.png"
#define ICON_FORESTKEEPER "main_icons_0105.png"
#define ICON_WILD "main_icons_0106.png"
#define ICON_HIGHELF "main_icons_0107.png"
#define ICON_ARCANE "main_icons_0108.png"
#define ICON_SILVER "main_icons_0109.png"
#define ICON_HENGE "main_icons_0110.png"
#define ICON_TREE "main_icons_0111.png"

#define ICON_SELL "ico_sell_0001.png"
#define ICON_SELL_CONFIRM "ico_sell_0002.png"
#define ICON_CANNOT_SELL "ico_sell_disabled_0001.png"

#define ICON_WEAPON_MAGIC "toptip_icons_0010.png"

#define ICON_BLADESINGER_1 "main_icons_0104.png"
#define ICON_BLADESINGER_2 "main_icons_0104.png"
#define ICON_BLADESINGER_3 "main_icons_0104.png"
#define ICON_FORESTKEEPER_1 "main_icons_0105.png"
#define ICON_FORESTKEEPER_2 "main_icons_0105.png"
#define ICON_FORESTKEEPER_3 "main_icons_0105.png"
#define ICON_WILD_1 "main_icons_0106.png"
#define ICON_WILD_2 "main_icons_0106.png"
#define ICON_WILD_3 "main_icons_0106.png"
#define ICON_HIGHELF_1 "main_icons_0107.png"
#define ICON_HIGHELF_2 "main_icons_0107.png"
#define ICON_HIGHELF_3 "main_icons_0107.png"
#define ICON_ARCANE_1 "main_icons_0108.png"
#define ICON_ARCANE_2 "main_icons_0108.png"
#define ICON_ARCANE_3 "main_icons_0108.png"
#define ICON_SILVER_1 "main_icons_0109.png"
#define ICON_SILVER_2 "main_icons_0109.png"
#define ICON_SILVER_3 "main_icons_0109.png"
#define ICON_HENGE_1 "main_icons_0110.png"
#define ICON_HENGE_2 "main_icons_0110.png"
#define ICON_HENGE_3 "main_icons_0110.png"
#define ICON_TREE_1 "main_icons_0111.png"
#define ICON_TREE_2 "main_icons_0111.png"
#define ICON_TREE_3 "main_icons_0111.png"

#define ICON_CONFRIM "main_icons_0111.png"

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

std::vector<std::string> SlotRing::getIcons()
{
    std::vector<std::string> ret;
    Tower* tower = m_owner->getTower();
    if (!tower) {
        ret.push_back(ICON_ARCHER);
        ret.push_back(ICON_BARRACKS);
        ret.push_back(ICON_MAGE);
        ret.push_back(ICON_ARTILLERY);
        return ret;
    }
    
    if (tower->getLevel() >= TowerLevel_3) {
        switch (tower->getId()) {
            case TowerID_Archer:
            {
                ret.push_back(ICON_ARCANE);
                ret.push_back(ICON_SILVER);
            }
                break;
            case TowerID_Barrack:
            {
                ret.push_back(ICON_BLADESINGER);
                ret.push_back(ICON_FORESTKEEPER);
            }
                break;
            case TowerID_Mage:
            {
                ret.push_back(ICON_WILD);
                ret.push_back(ICON_HIGHELF);
            }
                break;
            case TowerID_Artillery:
            {
                ret.push_back(ICON_HENGE);
                ret.push_back(ICON_TREE);
            }
                break;

            // level4 towers updrage icons
            case TowerID_Archer_Arcane:
            {
                ret.push_back(ICON_ARCANE_1);
                ret.push_back(ICON_ARCANE_2);
                ret.push_back(ICON_ARCANE_3);
            }
                break;
            case TowerID_Archer_Silver:
            {
                ret.push_back(ICON_SILVER_1);
                ret.push_back(ICON_SILVER_2);
                ret.push_back(ICON_SILVER_3);
            }
                break;
            case TowerID_BladeSinger:
            {
                ret.push_back(ICON_BLADESINGER_1);
                ret.push_back(ICON_BLADESINGER_2);
                ret.push_back(ICON_BLADESINGER_3);
            }
                break;
            case TowerID_ForestKeeper:
            {
                ret.push_back(ICON_FORESTKEEPER_1);
                ret.push_back(ICON_FORESTKEEPER_2);
                ret.push_back(ICON_FORESTKEEPER_3);
            }
                break;
            case TowerID_Mage_Wild:
            {
                ret.push_back(ICON_WILD_1);
                ret.push_back(ICON_WILD_2);
                ret.push_back(ICON_WILD_3);
            }
                break;
            case TowerID_Mage_HighElven:
            {
                ret.push_back(ICON_HIGHELF_1);
                ret.push_back(ICON_HIGHELF_2);
                ret.push_back(ICON_HIGHELF_3);
            }
                break;
            case TowerID_Artillery_Henge:
            {
                ret.push_back(ICON_HENGE_1);
                ret.push_back(ICON_HENGE_2);
                ret.push_back(ICON_HENGE_3);
            }
                break;
            case TowerID_Artillery_Tree:
            {
                ret.push_back(ICON_TREE_1);
                ret.push_back(ICON_TREE_2);
                ret.push_back(ICON_TREE_3);
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
    m_texture->removeAllChildrenWithCleanup(false);
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
    m_terrian = Sprite::createWithSpriteFrameName("build_terrain_0001.png");
    m_terrian->setPosition(0, 0);
    addChild(m_terrian);
    
    m_slotRing = SlotRing::create(this);
    m_slotRing->setPosition(0, 0);
    addChild(m_slotRing);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(TowerSlot::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

Tower* TowerSlot::getTower() const
{
    return m_tower;
}

bool TowerSlot::onTouchBegan(Touch* touch, Event* event)
{
    if (isTouched(touch)) return false;
    if (!m_slotRing) return false;
    if (!m_slotRing->isVisible()) {
        m_slotRing->onTouch();
        m_slotRing->setVisible(true);
    }
    else
        m_slotRing->setVisible(false);
    
    return true;
}
