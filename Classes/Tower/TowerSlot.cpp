//
//  TowerSlot.cpp
//  TowerDefense
//
//  Created by jowu on 15/12/30.
//
//




#include "TowerSlot.h"

// Tower upgrade icons
#define ICON_UPGRADE "main_icons_0005.png"
#define ICON_LOCK "main_icons_0005.png"
#define ICON_UPGRADE "main_icons_00014.png"
#define ICON_HARMMER "main_icons_00015.png"
#define ICON_CONFRIM "main_icons_0019.png"
#define ICON_ARCHER "main_icons_0100.png"
#define ICON_BARRACKS "main_icons_0101.png"
#define ICON_MAGE "main_icons_0102.png"
#define ICON_ARTILLERY "main_icons_103.png"
#define ICON_BLADESINGER "main_icons_104.png"
#define ICON_FORESTKEEPER "main_icons_105.png"
#define ICON_WILD "main_icons_106.png"
#define ICON_HIGHELF "main_icons_107.png"
#define ICON_ARCANE "main_icons_108.png"
#define ICON_SILVER "main_icons_0109.png"
#define ICON_HENGE "main_icons_0110.png"
#define ICON_TREE "main_icons_0111.png"

#define ICON_SELL "ico_sell_0001.png"
#define ICON_SELL_CONFIRM "ico_sell_0002.png"
#define ICON_CANNOT_SELL "ico_sell_disabled_0001.png"

#define ICON_WEAPON_MAGIC "toptip_icons_0010.png"

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
    { 0, 1 }
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

std::vector<std::string> getIcons(Tower* tower)
{
    std::vector<std::string> ret;
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
            {}
                break;
            case TowerID_Archer_Silver:
            {}
                break;
            case TowerID_BladeSinger:
            {}
                break;
            case TowerID_ForestKeeper:
            {}
                break;
            case TowerID_Mage_Wild:
            {}
                break;
            case TowerID_Mage_HighElven:
            {}
                break;
            case TowerID_Artillery_Henge:
            {}
                break;
            case TowerID_Artillery_Tree:
            {}
                break;
            default:
                break;
        }
        
        ret.push_back(ICON_SELL);
    }
    else {
        ret.push_back(ICON_UPGRADE);
    }
}


class SlotRing : public Node
{
public:
    static SlotRing* create(TowerSlot* owner);
    bool init(TowerSlot* owner);
    virtual void onEnter();
    
private:
    
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

// price_tag.png
// price_tag_disabled.png
// price_tag_turnOff.png
void SlotRing::onEnter()
{
    Node::onEnter();
    if (m_owner) {
        if (m_owner->getTower()) {
            
        }
        else {
            m_texture->removeAllChildrenWithCleanup(false);
            //"main_icons_0100.png"
            auto archerFrame = Sprite::createWithSpriteFrameName("main_icons_over.png");
            auto archerIcon = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("main_icons_0100.png"), Sprite::createWithSpriteFrameName("main_icons_0100.png"), [&](Ref *sender) {
            }), NULL);
            addChild(archerFrame);
            addChild(archerIcon);
            archerFrame->setPosition(-0.3535 * m_texture->getContentSize().width, 0.3535 * m_texture->getContentSize().height);
            archerIcon->setPosition(-0.3535 * m_texture->getContentSize().width, 0.3535 * m_texture->getContentSize().height);

            auto barrackFrame = Sprite::createWithSpriteFrameName("main_icons_over.png");
            auto barrackIcon = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("main_icons_0101.png"), Sprite::createWithSpriteFrameName("main_icons_0101.png"), [&](Ref *sender) {
            }), NULL);
            addChild(barrackFrame);
            addChild(barrackIcon);
            barrackFrame->setPosition(0.3535 * m_texture->getContentSize().width, 0.3535 * m_texture->getContentSize().height);
            barrackIcon->setPosition(0.3535 * m_texture->getContentSize().width, 0.3535 * m_texture->getContentSize().height);
            
            auto artilleryFrame = Sprite::createWithSpriteFrameName("main_icons_over.png");
            auto artilleryIcon = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("main_icons_0102.png"), Sprite::createWithSpriteFrameName("main_icons_0102.png"), [&](Ref *sender) {
            }), NULL);
            addChild(artilleryFrame);
            addChild(artilleryIcon);
            artilleryFrame->setPosition(0.3535 * m_texture->getContentSize().width, -0.3535 * m_texture->getContentSize().height);
            artilleryIcon->setPosition(0.3535 * m_texture->getContentSize().width, -0.3535 * m_texture->getContentSize().height);
            
            auto mageFrame = Sprite::createWithSpriteFrameName("main_icons_over.png");
            auto mageIcon = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("main_icons_0103.png"), Sprite::createWithSpriteFrameName("main_icons_0103.png"), [&](Ref *sender) {
            }), NULL);
            addChild(mageFrame);
            addChild(mageIcon);
            mageFrame->setPosition(-0.3535 * m_texture->getContentSize().width, -0.3535 * m_texture->getContentSize().height);
            mageIcon->setPosition(-0.3535 * m_texture->getContentSize().width, -0.3535 * m_texture->getContentSize().height);
        }
    }
}

// special_icons_0020.png   ok

//  main_icons_turnOff.png

bool TowerSlot::init()
{
    m_terrian = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("build_terrain_0001.png"), Sprite::createWithSpriteFrameName("build_terrain_0001.png"), [&](Ref *sender) {
        if (m_slotRing->isVisible()) {
            m_slotRing->setVisible(false);
        }
        else {
            m_slotRing->removeAllChildren();
            if (m_tower) {
                
            }
            else {
                
            }
            m_slotRing->setVisible(true);
        }
        
        
        
        
        
        if (m_slotRing->isVisible()) {
            m_slotRing->setVisible(false);
        }
        else {
            m_slotRing->onEnter();
            
        }
    }), NULL);
    
    m_terrian->setPosition(0, 0);
    addChild(m_terrian);
    
    m_slotRing = SlotRing::create(this);
    //m_slotRing->setVisible(false);
    m_slotRing->setPosition(0, 0);
    addChild(m_slotRing);
    
    return true;
}

Tower* TowerSlot::getTower() const
{
    return m_tower;
}

void TowerSlot::choose()
{
    if (!m_tower) {
        
    }
    else {
        
        
    }
}
