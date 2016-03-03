//
//  TouchNode.cpp
//  TowerDefense
//
//  Created by jowu on 16/3/4.
//
//

#include "TouchNode.h"


bool TouchNode::init()
{
    return true;
}

bool TouchNode::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

bool TouchNode::isTouched(Touch* touch)
{
    Vec2 touchLocation = touch->getLocation();
    if (isVisible())
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
