//
//  TestLayer.cpp
//  TowerDefense
//
//  Created by jowu on 15/10/31.
//
//

#include "TestLayer.h"
#include "PListReader.h"

bool TestLayer::init()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // load resources
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("elves_woods_enemies-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("elves_woods_2_enemies-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("elves_metropolis_enemies-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("elves_metropolis_enemies_2-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("elves_hulking_rage_enemies-hd .plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("elves_hulking_rage_2_enemies-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("elves_faerie_grove_enemies-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("elves_faerie_grove_enemies_2-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("elves_bittering_rancor_enemies-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("elves_bittering_rancor_2_enemies-hd.plist");
    PListReader::getInstance()->createAnimationWithPlist("redcap_animations.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level1_2-hd.plist");
    m_bkg = Sprite::createWithSpriteFrameName("Stage_1.png");
    if (m_bkg) {
        CCLOG("map size = %f %f", m_bkg->getContentSize().width, m_bkg->getContentSize().height);
        m_bkg->setScale(visibleSize.width/m_bkg->getContentSize().width);
        m_bkg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        addChild(m_bkg);
    }
    else {
        return false;
    }
    
    auto attacker = Sprite::createWithSpriteFrameName("redcap_0001.png");
    auto actionAttack = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("redcap_attack")));
    if (!attacker || !actionAttack) {
        return false;
    }
    
    attacker->runAction(actionAttack);
    attacker->setPosition(Vec2(200, 200));
    m_bkg->addChild(attacker);
    
    schedule(schedule_selector(TestLayer::moveSprite));
    //m_path = PListReader::getInstance()->readPathPlist(1);
    
    return true;
}


void TestLayer::moveSprite(float dt)
{
    
}
