//
//  StartLayer.cpp
//  TowerDefense
//
//  Created by bluesChen on 15/11/11.
//
//

#include "StartLayer.h"
#include "CommonDef.h"
#include "Animation/AnimationManager.h"

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
    
    //创建菜单
    auto startBtnNormal = Sprite::createWithSpriteFrameName("menu_startchain_0001.png");
    auto startBtnPressed = Sprite::createWithSpriteFrameName("menu_startchain_0002.png");
    //startBtnPressed->setScale(0.8);
    
    auto creditsBtnNormal = Sprite::createWithSpriteFrameName("menu_creditschain_0001.png");
    auto creditsBtnPressed = Sprite::createWithSpriteFrameName("menu_creditschain_0002.png");
    //creditsBtnPressed->setScale(0.8);
    
    auto startBtnItem = MenuItemSprite::create(startBtnNormal, startBtnPressed, [&](Ref *sender) {
        //start game
        onStartBtnClick();
    });
    
    auto creditsItem = MenuItemSprite::create(creditsBtnNormal, creditsBtnPressed, [&](Ref *sender) {
        //open credits
        onCreditBtnClick();
    });
    
    startBtnItem->setPosition(Vec2(0, -60));
    creditsItem->setPosition(Vec2(0, -230));
    
    
    auto gameMenu = Menu::create(creditsItem, startBtnItem, nullptr);
    gameMenu->setPosition(Vec2(TD_WIDTH/2, TD_HEIGHT/2));
    //end
   
    //创建开关按钮
    m_isKeySoundOn = true;
    auto keySoundBtnOn = Sprite::createWithSpriteFrameName("options_overlay_buttons_0003.png");
    auto keySoundBtnOff = Sprite::createWithSpriteFrameName("options_overlay_buttons_0004.png");
    
    m_isBGMOn = true;
    auto BGMBtnOn = Sprite::createWithSpriteFrameName("options_overlay_buttons_0001.png");
    auto BGMBtnOff = Sprite::createWithSpriteFrameName("options_overlay_buttons_0002.png");
    
   
    auto keySoundItem = MenuItemSprite::create(keySoundBtnOn, keySoundBtnOff, [&](Ref *sender) {
        //start game
        MenuItemSprite* item = (MenuItemSprite*)sender;
        auto keySoundBtnOnTmp = Sprite::createWithSpriteFrameName("options_overlay_buttons_0003.png");
        auto keySoundBtnOffTmp = Sprite::createWithSpriteFrameName("options_overlay_buttons_0004.png");
        if (m_isKeySoundOn) {
            item->setNormalImage(keySoundBtnOffTmp);
            item->setSelectedImage(keySoundBtnOnTmp);
        }
        else
        {
            item->setNormalImage(keySoundBtnOnTmp);
            item->setSelectedImage(keySoundBtnOffTmp);
        }
        
        m_isKeySoundOn = !m_isKeySoundOn;
    });

    
    auto BGMItem = MenuItemSprite::create(BGMBtnOn, BGMBtnOff, [&](Ref *sender) {
        //start game
        MenuItemSprite* item = (MenuItemSprite*)sender;
        auto BGMBtnOnTmp = Sprite::createWithSpriteFrameName("options_overlay_buttons_0001.png");
        auto BGMBtnOffTmp = Sprite::createWithSpriteFrameName("options_overlay_buttons_0002.png");
        if (m_isBGMOn) {
            item->setNormalImage(BGMBtnOffTmp);
            item->setSelectedImage(BGMBtnOnTmp);
        }
        else
        {
            item->setNormalImage(BGMBtnOnTmp);
            item->setSelectedImage(BGMBtnOffTmp);
        }
        
        m_isBGMOn = !m_isBGMOn;
    });
    
    keySoundItem->setPosition(Vec2(40, -40));
    BGMItem->setPosition(Vec2(120, -40));
    
    auto soundMenu = Menu::create(keySoundItem, BGMItem, nullptr);
    soundMenu->setPosition(Vec2(0, TD_HEIGHT));
    //end
    
    //animate
   // Vector<cocos2d::SpriteFrame *> arrayOfSpriteFrameNames;
    auto animation = Animation::create();
    for (int i = 1; i <= 20; ++i)
    {
        std::string frameImgName = String::createWithFormat("logo_brillo_00%02d.png", i)->getCString();
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameImgName);
       // arrayOfSpriteFrameNames.pushBack(frame);
        animation->addSpriteFrame(frame);
        
    }
    animation->setDelayPerUnit(1.5f / 20.0f);
    animation->setRestoreOriginalFrame(true);
    auto logoBrillo = Sprite::create();

    auto brillo = CCRepeatForever::create(Animate::create(animation));
    //auto brillo = Animate::create(animation);
    if (!logoBrillo || !brillo) {
        return false;
    }
    logoBrillo->runAction(brillo);
    logoBrillo->setPosition(Vec2(TD_WIDTH/2, 640-194));

    //end
    
    addChild(m_bkg);
    m_bkg->addChild(gameMenu);
    m_bkg->addChild(m_logo);
    
    m_bkg->addChild(soundMenu);
    m_bkg->addChild(logoBrillo);
    
    return true;
}

void StartLayer::onStartBtnClick()
{
    
}

void StartLayer::onCreditBtnClick()
{
    
}


void StartLayer::onKeySoundBtnClick()
{
    
}

void StartLayer::onBGMBtnClick()
{
    
}
