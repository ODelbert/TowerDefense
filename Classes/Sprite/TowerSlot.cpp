//
//  TowerSlot.cpp
//  TowerDefense
//
//  Created by jowu on 15/12/30.
//
//

#include "TowerSlot.h"
#include "Sprite/Icon.h"
#include "Sprite/Assembly.h"
#include "Base/GameManager.h"

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
    m_texture->setTag(0x8888);
    addChild(m_texture);
    return true;
}

void SlotRing::onTouch()
{
    Vector<Node*> childs = getChildren();
    for (int i = 0; i < childs.size(); ++i) {
        if (0x8888 != childs.at(i)->getTag()) {
            childs.at(i)->removeFromParent();
        }
    }

    if (m_owner) {
        std::vector<Node*> icons;
        Tower* tower = m_owner->getTower();
        if (tower) {
            if (tower->getLevel() < TowerLevel_3) {
                // upgrade & sell ----> 2
                auto upgrader = UpgradeIcon::create(TowerID_Invaild, GM->enoughGold(tower->getUpgradeGold()));
                icons.push_back(upgrader);
            }
            else if (3 == tower->getLevel()) {
                Node* u1 = NULL;
                Node* u2 = NULL;
                switch (tower->getId()) {
                case TowerID_Archer_Lv3:
                    u1 = UpgradeIcon::create(TowerID_Archer_Arcane, GM->enoughGold(tower->getUpgradeGold()));
                    u2 = UpgradeIcon::create(TowerID_Archer_Silver, GM->enoughGold(tower->getUpgradeGold()));
                    break;
                case TowerID_Barrack_Lv3:
                    u1 = UpgradeIcon::create(TowerID_BladeSinger, GM->enoughGold(tower->getUpgradeGold()));
                    u2 = UpgradeIcon::create(TowerID_ForestKeeper, GM->enoughGold(tower->getUpgradeGold()));
                    break;
                case TowerID_Mage_Lv3:
                    u1 = UpgradeIcon::create(TowerID_Mage_Wild, GM->enoughGold(tower->getUpgradeGold()));
                    u2 = UpgradeIcon::create(TowerID_Mage_HighElven, GM->enoughGold(tower->getUpgradeGold()));
                    break;
                case TowerID_Artillery_Lv3:
                    u1 = UpgradeIcon::create(TowerID_Artillery_Henge, GM->enoughGold(tower->getUpgradeGold()));
                    u2 = UpgradeIcon::create(TowerID_Artillery_Tree, GM->enoughGold(tower->getUpgradeGold()));
                default:
                    break;
                }

                icons.push_back(u1);
                icons.push_back(u2);
            }
            else {
                // technology & sell ----> 3
                // FIXME:: price Icon
                auto t1 = TechnologyIcon::create(tower->getId(), 0);
                auto t2 = TechnologyIcon::create(tower->getId(), 1);
                icons.push_back(t1);
                icons.push_back(t2);
                if (TowerID_ForestKeeper == tower->getId() ||
                    TowerID_BladeSinger == tower->getId()) {
                    auto t3 = TechnologyIcon::create(tower->getId(), 2);
                    icons.push_back(t3);
                }
            }

            if (TowerID_Barrack_Lv1 == tower->getId() ||
                TowerID_Barrack_Lv2 == tower->getId() ||
                TowerID_Barrack_Lv3 == tower->getId() ||
                    TowerID_BladeSinger == tower->getId() ||
                    TowerID_ForestKeeper == tower->getId() ||
                    TowerID_Artillery_Henge == tower->getId()) {
                auto assembly = Assembly::create(m_owner->getSlotId());
                addChild(assembly);
                assembly->setPosition(0.5 * m_texture->getContentSize().width / 2, -0.866 * m_texture->getContentSize().height / 2);
            }

            auto seller = SellIcon::create();
            addChild(seller);
            seller->setPosition(0, -1 * m_texture->getContentSize().height / 2);
        }
        else {
            // 4 basic icon  ----> 4
            auto u1 = UpgradeIcon::create(TowerID_Archer_Lv1);
            auto u2 = UpgradeIcon::create(TowerID_Barrack_Lv1);
            auto u3 = UpgradeIcon::create(TowerID_Mage_Lv1);
            auto u4 = UpgradeIcon::create(TowerID_Artillery_Lv1);
            icons.push_back(u1);
            icons.push_back(u2);
            icons.push_back(u3);
            icons.push_back(u4);
        }

        for (int i = 0; i < icons.size(); ++i) {
            Node* icon = icons.at(i);
            if (!icon) continue;
            addChild(icon);
            Location locate = icons.size() == 1 ? s_location_1[i]: icons.size() == 2 ? s_location_2[i] : icons.size() == 3 ? s_location_3[i] : icons.size() == 4 ? s_location_4[i] : Location();
            icon->setPosition(locate.x * m_texture->getContentSize().width / 2, locate.y * m_texture->getContentSize().height / 2);
        }
    }
}

bool TowerSlot::init()
{
    auto touchReceiver = Sprite::createWithSpriteFrameName("build_terrain_0001.png");
    addChild(touchReceiver);
    initWithTouchReceiver(touchReceiver);

    m_ring = SlotRing::create(this);
    if (!m_ring) return false;
    m_ring->setPosition(0, 0);
    addChild(m_ring);
    m_ring->setVisible(false);
    
    auto outRangeCallBack = [&]() {
        if (m_ring->isVisible()) {
            Vector<Node*> childs = m_ring->getChildren();
            for (int i = 0; i < childs.size(); ++i) {
                TouchNode* tn = static_cast<TouchNode*>(childs.at(i));
                if (TouchNode::State::Selected == tn->getState()) {
                    // do not hide
                    return;
                }
            }
            
            m_ring->setVisible(false);
        }
    };
    
    setTouchCallback(CC_CALLBACK_0(TowerSlot::onTouchEvent, this));
    setOutRangeCallback(outRangeCallBack);
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

void TowerSlot::addTower(Tower* tower)
{
    m_tower = tower;
    addChild(tower);
}

void TowerSlot::removeTower()
{
    if (!m_tower) return;
    removeChild(m_tower);
    m_tower = nullptr;
}
