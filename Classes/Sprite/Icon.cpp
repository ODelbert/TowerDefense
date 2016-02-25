#include "Icon.h"
#include "Tower/Tower.h"


upgradeIcon* upgradeIcon::create(const std::string& name)
{
    upgradeIcon* ret = new upgradeIcon;
    if (ret && ret->init(name)) {
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool upgradeIcon::init(const std::string& name)
{
    m_texture = Sprite::createWithSpriteFrameName(name);
    if (!m_texture) return false;
    
    addChild(m_texture);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    touchListener->onTouchBegan = CC_CALLBACK_2(upgradeIcon::onTouchBegan, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

bool upgradeIcon::onTouchBegan(Touch* touch, Event* event)
{
    if (m_state == Disabled) return false;

    // icon for towers
    auto towerSlot = getParent();
    if (towerSlot != nullptr) {
        auto tower = towerSlot->getParent();
        if (tower) {
            Tower* t = static_cast<Tower*>(tower);
            if (Selected == m_state) {
                m_state = Confrim;
                // FIXME:: sound support
            }
            else if (Confrim == m_state) {
                t->upgrade(m_tid);
            }
            else {
            }
        }
    }

    return true;
}
