#include "Icon.h"
#include "Tower/Tower.h"
#include "Base/Event.h"
#include "Sprite/TowerSlot.h"

UpgradeIcon* UpgradeIcon::create(const std::string& name, int tid)
{
    UpgradeIcon* ret = new UpgradeIcon(tid);
    if (ret && ret->init(name)) {
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool UpgradeIcon::init(const std::string& name)
{
    m_texture = Sprite::createWithSpriteFrameName(name);
    if (!m_texture) return false;
    
    addChild(m_texture);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    touchListener->onTouchBegan = CC_CALLBACK_2(UpgradeIcon::onTouchBegan, this);

    GM->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

UpgradeIcon::UpgradeIcon(int tid)
    : m_tid(tid),
    m_state(Enabled),
    m_texture(nullptr)
{}

bool UpgradeIcon::onTouchBegan(Touch* touch, Event* event)
{
    if (!isTouched(touch)) {
        return false;
    }
    
    switch (m_state) {
    case Enabled:
        {
            m_state = Selected;
            m_texture = Sprite::createWithSpriteFrameName("main_icons_0111.png");
            // sound
        }
        break;
    case Selected:
        {
            if (!getParent() || !getParent()->getParent()) return false;
            TowerSlot* towerSlot = static_cast<TowerSlot*>(getParent()->getParent());
            if (towerSlot != nullptr) {
                auto tower = towerSlot->getTower();
                if (tower) {
                    Tower* t = static_cast<Tower*>(tower);
                    TowerEvent evt(towerSlot->getSlotId(), TowerEvent::Command::Upgrade);
                    GM->dispatchEvent(&evt);
                    
                    // sound
                    GM->setGold(GM->getGold() + t->getUpgradeGold());
                    // add new tower
                    
                    t->removeFromParent();
                }
            }
        }
        break;
    case Disabled:
    default:
        {}
        break;
    }
    
    return true;
}
