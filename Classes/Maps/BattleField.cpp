//
//  BattleField.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/15.
//
//

#include "BattleField.h"
#include "CommonDef.h"

#define MAP_WIDTH 1200
#define MAP_HEIGHT 1000

BattleField::BattleField()
{
    auto touchlistener = EventListenerTouchOneByOne::create();
    touchlistener->onTouchBegan = CC_CALLBACK_2(BattleField::onTouchBegan, this);
    touchlistener->onTouchEnded = CC_CALLBACK_2(BattleField::onTouchEnded, this);
    touchlistener->onTouchMoved = CC_CALLBACK_2(BattleField::onTouchMoved, this);
    touchlistener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener,this);
}

bool BattleField::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("touch at pos [%f %f]", touch->getStartLocation().x, touch->getStartLocation().y);
    return true;
}

void BattleField::onTouchEnded(Touch* touch, Event* event)
{
}

void BattleField::onTouchMoved(Touch* touch, Event* event)
{
    Vec2 offset = touch->getLocation() - touch->getPreviousLocation();
    //TD_POS(m_mapSprite)
    Vec2 newPos;
    if (m_mapSprite->getPosition().x + offset.x > 0.5 * MAP_WIDTH) {
        newPos.x = 0.5 * MAP_WIDTH;
    }
    else if (m_mapSprite->getPosition().x + offset.x < TD_WIDTH - 0.5 * MAP_WIDTH) {
        newPos.x = TD_WIDTH - 0.5 * MAP_WIDTH;
    }
    else {
        newPos.x = m_mapSprite->getPosition().x + offset.x;
    }
    
    if (m_mapSprite->getPosition().y + offset.y > 0.5 * MAP_HEIGHT) {
        newPos.y = 0.5 * MAP_HEIGHT;
    }
    else if (m_mapSprite->getPosition().y + offset.y < TD_HEIGHT - 0.5 * MAP_HEIGHT) {
        newPos.y = TD_HEIGHT - 0.5 * MAP_HEIGHT;
    }
    else {
        newPos.y = m_mapSprite->getPosition().y + offset.y;
    }
    //TD_POS(m_mapSprite)
    
    m_mapSprite->setPosition(newPos);
}
