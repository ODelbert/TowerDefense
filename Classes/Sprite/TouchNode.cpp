//
//  TouchNode.cpp
//  TowerDefense
//
//  Created by jowu on 16/3/4.
//
//

#include "TouchNode.h"
#include "Base/GameManager.h"

bool TouchNode::initWithTouchReceiver(Sprite* touchReceiver)
{
    if (!touchReceiver) return false;
    m_touchReceiver = touchReceiver;
    auto touchlistener = EventListenerTouchOneByOne::create();
    if (!touchlistener) return false;
    
    touchlistener->onTouchBegan = CC_CALLBACK_2(TouchNode::onTouchBegan, this);
    touchlistener->onTouchMoved = CC_CALLBACK_2(TouchNode::onTouchMoved, this);
    touchlistener->onTouchEnded = CC_CALLBACK_2(TouchNode::onTouchEnded, this);
    touchlistener->setSwallowTouches(true);
    GM->addEventListenerWithSceneGraphPriority(touchlistener, this);
    return true;
}

TouchNode::TouchNode()
    : m_touchReceiver(nullptr),
    m_isTouchBegan(false),
    m_forceLock(false),
    m_state(Enabled)
{}

bool TouchNode::onTouchBegan(Touch* touch, Event* event)
{
    if (!inTouchRegion(touch)) {
        log("TouchNode::onTouchBegan not in touch region!");
        m_isTouchBegan = false;
        if (m_outRangeCallBack) {
            m_outRangeCallBack();
        }
        return false;
    }

    log("TouchNode::onTouchBegan pos [%f %f, nodeSpace %f %f] in touch region!", touch->getLocation().x, touch->getLocation().y, convertToNodeSpace(touch->getLocation()).x, convertToNodeSpace(touch->getLocation()).y);

    m_isTouchBegan = true;
    return true;
}

void TouchNode::onTouchMoved(Touch* touch, Event* event)
{
    if (!inTouchRegion(touch)) {
        m_isTouchBegan = false;
        if (m_outRangeCallBack) {
            m_outRangeCallBack();
        }
    }
    else {

    }
}

void TouchNode::onTouchEnded(Touch* touch, Event* event)
{
    if (m_isTouchBegan) {
        if (m_callback) {
            m_callback();
        }
    }
}

void TouchNode::setTouchCallback(TouchCallBack callBack)
{
    m_callback = callBack;
}

void TouchNode::setOutRangeCallback(TouchCallBack callBack)
{
    m_outRangeCallBack = callBack;
}

bool TouchNode::inTouchRegion(Touch* touch)
{
    if (touch && isVisible() && m_touchReceiver)
    {
        Vec2 touchLocation = touch->getLocation();
        Size contentSize = m_touchReceiver->getContentSize();
        Vec2 anchorPoint = m_touchReceiver->getAnchorPoint();
        Vec2 position = Vec2::ZERO;
        Vec2 local = convertToNodeSpace(touchLocation);
        Rect r(position.x - contentSize.width * anchorPoint.x,
             position.y - contentSize.height * anchorPoint.y,
             contentSize.width, contentSize.height);
        
        if (r.containsPoint(local))
        {
            return true;
        }
    }
    
    return false;
}
