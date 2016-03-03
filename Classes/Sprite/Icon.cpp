#include "Icon.h"
#include "Tower/Tower.h"
#include "Base/Event.h"
#include "Tower/TowerSlot.h"

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

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

UpgradeIcon::UpgradeIcon(int tid)
    : m_tid(tid),
    m_state(Enabled),
    m_texture(nullptr)
{}

bool UpgradeIcon::onTouchBegan(Touch* touch, Event* event)
{
    switch (m_state) {
    case Disabled:
        return false;
    break;
    case Enabled:
        {
            m_state = Selected;
            m_texture = Sprite::createWithSpriteFrameName("main_icons_0111.png");
            // sound
        }
        break;
    case Selected:
        {
            TowerSlot* towerSlot = static_cast<TowerSlot*>(getParent());
            if (towerSlot != nullptr) {
                auto tower = towerSlot->getParent();
                if (tower) {
                    Tower* t = static_cast<Tower*>(tower);
                    TowerEvent evt(towerSlot->getSlotId(), TowerEvent::Command::Upgrade);
                    GM->dispatchEvent(&evt);
                    t->removeFromParent();
                    // sound
                    GM->setGold(GM->getGold() + t->getUpgradeGold());
                    // add new tower
                }
            }
        }
        break;
    }
}
