#include "GatherFlag.h"

GatherFlag* GatherFlag::create(int slotId)
{
    GatherFlag* ret = new GatherFlag;
    if (ret && ret->init(slotId)) {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool GatherFlag::init(int slotId)
{
    return true;
}

bool GatherFlag::onTouchBegan(Touch* touch, Event* event)
{
    if (!inTouchRegion(touch)) {
        m_isTouchBegan = false;
        return false;
    }

    m_isTouchBegan = true;
    return true;
}

void GatherFlag::onTouchMoved(Touch* touch, Event* event)
{
    if (!inTouchRegion(touch)) {
        m_isTouchBegan = false;
    }
}

void GatherFlag::onTouchEnded(Touch* touch, Event* event)
{
    if (m_isTouchBegan) {
        if (m_callback) {
            m_callback();
        }
    }
}


