#include "GatherFlag.h"

bool Assembly::init()
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


