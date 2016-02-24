//
//  TowerSlot.cpp
//  TowerDefense
//
//  Created by jowu on 15/12/30.
//
//

#include "TowerSlot.h"

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
            m_slotRing->onEnter();
            m_slotRing->setVisible(true);
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
