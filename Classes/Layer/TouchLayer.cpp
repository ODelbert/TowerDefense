//
//  TouchLayer.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/13.
//
//

#include "TouchLayer.h"
bool TouchLayer::init()
{
    auto touchlistener = EventListenerTouchOneByOne::create();
    touchlistener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
    touchlistener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
    touchlistener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
    touchlistener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener,this);
    
    return true;
}

bool TouchLayer::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("touch at pos [%f %f]", touch->getStartLocation().x, touch->getStartLocation().y);
    return true;
}

void TouchLayer::onTouchEnded(Touch* touch, Event* event)
{
}

void TouchLayer::onTouchMoved(Touch* touch, Event* event)
{
}
