//
//  StartLayer.cpp
//  TowerDefense
//
//  Created by bluesChen on 15/11/11.
//
//

#include "StartLayer.h"
#include "CommonDef.h"

class GameButtons : public Node
{
public:
    CREATE_FUNC(GameButtons);
    bool init();
    
private:
    Sprite* m_startButton;
    Sprite* m_creditsButtonS;
    
};

class SoundButtons : public Node
{
public:
    CREATE_FUNC(SoundButtons);
    bool init();
    
private:
    Sprite* m_mutexButton;
    Sprite* m_creditsButton;
    
};

bool GameButtons::init()
{
//    Size winSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    return true;
}

bool SoundButtons::init()
{
    //    Size winSize = Director::getInstance()->getVisibleSize();
    //    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    return true;
}

static double s_rate = 1.0f;

bool StartLayer::init()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_bkg = Sprite::createWithSpriteFrameName("Stage_1.png");
    if (m_bkg) {
        CCLOG("map size = %f %f   game rect [%f %f]", m_bkg->getContentSize().width, m_bkg->getContentSize().height, visibleSize.width, visibleSize.height);
        s_rate = visibleSize.width / 1200;
        m_bkg->setScale(visibleSize.width/m_bkg->getContentSize().width);
        m_bkg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        addChild(m_bkg);
    }
    else {
        return false;
    }
    
    return true;
}
