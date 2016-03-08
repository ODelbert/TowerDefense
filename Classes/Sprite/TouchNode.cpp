//
//  TouchNode.cpp
//  TowerDefense
//
//  Created by jowu on 16/3/4.
//
//

#include "TouchNode.h"
#include "Base/GameManager.h"

TouchNode* TouchNode::create(const std::string& name)
{
    auto ret = new TouchNode;
    if (ret && ret->init(name)) {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool TouchNode::init(const std::string& name)
{
    m_texture = Sprite::createWithSpriteFrameName(name);
    if (!m_texture) return false;

    addChild(m_texture);
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
    : m_texture(nullptr),
    m_isTouchBegan(false),
    m_forceLock(false)
{}

bool TouchNode::onTouchBegan(Touch* touch, Event* event)
{
    if (!inTouchRegion(touch)) {
        m_isTouchBegan = false;
        return false;
    }

    m_isTouchBegan = true;
    return true;
}

void TouchNode::onTouchMoved(Touch* touch, Event* event)
{
    if (!inTouchRegion(touch)) {
        m_isTouchBegan = false;
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

bool TouchNode::inTouchRegion(Touch* touch)
{
    if (touch && isVisible() && m_texture)
    {
        Vec2 touchLocation = touch->getLocation();
        Size contentSize = m_texture->getContentSize();
        Vec2 anchorPoint = m_texture->getAnchorPoint();
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
