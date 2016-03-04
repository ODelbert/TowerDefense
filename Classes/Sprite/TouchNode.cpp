//
//  TouchNode.cpp
//  TowerDefense
//
//  Created by jowu on 16/3/4.
//
//

#include "TouchNode.h"

TouchNode* TouchNode::create(const std::string& name)
{

    m_texture = Sprite::createWithSpriteName(name);
    addChild(m_texture);
}

bool TouchNode::init(const std::string& name)
{
    m_touchlistener = EventListenerTouchOneByOne::create();
    m_touchlistener->onTouchBegan = CC_CALLBACK_2(TouchNode::onTouchBegan, this);
    m_touchlistener->onTouchEnded = CC_CALLBACK_2(TouchNode::onTouchMoved, this);
    m_touchlistener->onTouchMoved = CC_CALLBACK_2(TouchNode::onTouchEnded, this);
    m_touchlistener->setSwallowTouches(true);
    GM->addEventListenerWithSceneGraphPriority(m_touchlistener, this);
    return true;
}

TouchNode::TouchNode()
    : m_texture(nullptr)
{}

void TouchNode::setTouchCallBack(onTouchBegan begin, onTouchMoved move, onTouchEnded end)
{

}

bool TouchNode::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void TouchNode::onTouchMoved(Touch* touch, Event* event)
{
    return;
}

void TouchNode::onTouchEnded(Touch* touch, Event* event)
{
    return;
}

bool TouchNode::handleTouch(Touch* touch, Event* event)
{
    Vec2 touchLocation = touch->getLocation();
    if (isVisible() && m_texture)
    {
        Vec2 local = convertToNodeSpace(touchLocation);
        Rect r( _position.x - _contentSize.width * _anchorPoint.x,
             _position.y - _contentSize.height * _anchorPoint.y,
             _contentSize.width, _contentSize.height);
        r.origin = Vec2::ZERO;
        
        if (r.containsPoint(local))
        {
            return true;
        }
    }
    
    return false;
}
