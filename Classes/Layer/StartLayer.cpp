//
//  StartLayer.cpp
//  TowerDefense
//
//  Created by bluesChen on 15/11/11.
//
//

#include "StartLayer.h"
#include "CommonDef.h"

static const std::string ImageStartPlist[] =
{
    "mainmenu_spritesheet_32_1-hd.plist",
    "mainmenu_spritesheet_32_2-hd.plist"
};

//static double s_rate = 1.0f;

bool StartLayer::init()
{
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    for (int i = 0; i < sizeof(ImageStartPlist)/sizeof(ImageStartPlist[0]); ++i) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ImageStartPlist[i]);
    }
    
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_1-hd.plist");
    m_bkg = Sprite::createWithSpriteFrameName("mainmenu_bg.png");
    m_logo = Sprite::createWithSpriteFrameName("logo.png");
    
    m_bkg->setPosition(Vec2(TD_WIDTH/2, TD_HEIGHT/2));
    m_logo->setPosition(Vec2(TD_WIDTH/2, 640-194));
    
    
    auto startBtnNormal = Sprite::createWithSpriteFrameName("menu_startchain_0001.png");
    auto startBtnPressed = Sprite::createWithSpriteFrameName("menu_startchain_0002.png");
    startBtnPressed->setScale(0.8);
    
    auto creditsBtnNormal = Sprite::createWithSpriteFrameName("menu_creditschain_0001.png");
    auto creditsBtnPressed = Sprite::createWithSpriteFrameName("menu_creditschain_0002.png");
    creditsBtnPressed->setScale(0.8);
    
    auto startMenu = Menu::create(MenuItemSprite::create(startBtnNormal, startBtnPressed, [&](Ref *sender) {
        //start game
    }), nullptr);
    
    auto creditsMenu = Menu::create(MenuItemSprite::create(creditsBtnNormal, creditsBtnPressed, [&](Ref *sender) {
        //open credits
    }), nullptr);
    
    startMenu->setPosition(Vec2(TD_WIDTH/2, TD_HEIGHT/2- 60));
    creditsMenu->setPosition(Vec2(TD_WIDTH/2, TD_HEIGHT/2 - 240));
    
    addChild(m_bkg);
    addChild(creditsMenu);
    addChild(startMenu);    
    addChild(m_logo);
    
    
    
    
    
    return true;
}
