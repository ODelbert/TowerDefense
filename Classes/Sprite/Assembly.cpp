#include "Assembly.h"

Assembly* Assembly::create(int slotId)
{
    Assembly* ret = new Assembly;
    if (ret && ret->init(slotId)) {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Assembly::init(int slotId)
{
    return true;
}

bool Assembly::onTouchBegan(Touch* touch, Event* event)
{
    if (!inTouchRegion(touch)) {
        m_isTouchBegan = false;
        return false;
    }

    m_isTouchBegan = true;
    return true;
}

void Assembly::onTouchMoved(Touch* touch, Event* event)
{
    if (!inTouchRegion(touch)) {
        m_isTouchBegan = false;
    }
}

void Assembly::onTouchEnded(Touch* touch, Event* event)
{
    if (m_isTouchBegan) {
        if (m_callback) {
            m_callback();
        }
    }
}


