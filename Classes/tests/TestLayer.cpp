//
//  TestLayer.cpp
//  TowerDefense
//
//  Created by jowu on 15/10/31.
//
//

#include <vector>
#include "TestLayer.h"
#include "PListReader.h"

static double s_rate = 1.0f;

enum ActionTag {
    ActionTag_WalkingLeft = 0,
    ActionTag_WalkingRight,
    ActionTag_WalkingDown,
    ActionTag_WalkingUp,
    ActionTag_Num,
};

static const std::string ImageAnimationPlist[] =
{
    "elves_bittering_rancor_2_enemies-hd.plist",
    "elves_bittering_rancor_2_enemies-ipadhd.plist",
    "elves_bittering_rancor_2_enemies.plist",
    "elves_bittering_rancor_enemies-hd.plist",
    "elves_faerie_grove_enemies-hd.plist",
    "elves_faerie_grove_enemies_2-hd.plist",
    "elves_hulking_rage_2_enemies-hd.plist",
    "elves_hulking_rage_enemies-hd.plist",
    "elves_metropolis_enemies-hd.plist",
    "elves_metropolis_enemies_2-hd.plist",
    "elves_woods_2_enemies-hd.plist",
    "elves_woods_enemies-hd.plist"
};

static const std::string AnimationNamePlist[] =
{
    "ewok_animations.plist",
    "hyena_animations.plist",
    "knocker_animations.plist",
    
    "mactans_malicia_animations.plist",
    "malicia_animations.plist",
    
    "mantaray_animations.plist",
    "ogre_mage_animations.plist",
    "ogre_mage_aura_animations.plist",
    "ogre_mage_proy_animations.plist",
    "ogre_mage_shield_animations.plist",
    "perython_animations.plist",
    "perython_rockthrower_animations.plist",
    "arachnomancer_animations.plist",
    "arachnomancer_miniSpider_animations.plist",
    "arachnomancer_spider_animations.plist",
    "babyAshbite_animations.plist",
    "bandersnatch_animations.plist",
    "bandersnatch_spines_animations.plist",
    "bandersnatch_spines_blood_animations.plist",
    "bloodServant_animations.plist",
    "bloodsydianGnoll_animations.plist",
    "bloodsydianWarlock_animations.plist",
    "dark_spitters_animations.plist",
    "dark_spitters_proy_animations.plist",
    "drider_animations.plist",
    "elves_enemies_bittering_rancor_animations.plist",
    "elves_enemies_endless2_animations.plist",
    "elves_enemies_endless_animations.plist",
    "elves_enemies_faerie_grove_animations.plist",
    "elves_enemies_forgotten_animations.plist",
    "elves_enemies_hulking_rage_animations.plist",
    "elves_enemies_metropolis_animations.plist",
    "elves_enemies_woods_animations.plist",
    "ettin_animations.plist",
    "fungusRider_animations.plist",
    "fungusRider_medium_animations.plist",
    "fungusRider_small_animations.plist",
    "gloomy_animations.plist",
    "gnollBush_animations.plist",
    "gnoll_blighter_animations.plist",
    "gnoll_blighter_energy_animations.plist",
    "gnoll_blighter_proy_animations.plist",
    "gnoll_burner_animations.plist",
    "gnoll_burner_proy_animations.plist",
    "gnoll_gnawer_animations.plist",
    "gnoll_reaver_animations.plist",
    "gollem_animations.plist",
    "grim_devourers_animations.plist",
    "harraser_animations.plist",
    "razorboar_animations.plist",
    "redcap_animations.plist",
    "satyrHoplite_animations.plist",
    "satyr_animations.plist",
    "scourger_animations.plist",
    "scourger_shadow_animations.plist",
    "screecher_bat_animations.plist",
    "screecher_bat_stun_animations.plist",
    "shadow_champion_animations.plist",
    "shadow_spawn_animations.plist",
    "son_of_mactans_animations.plist",
    "son_of_mactans_particles_animations.plist",
    "spiderQueen_layer_animations.plist",
    "sword_spider_animations.plist",
    "tarantula_animations.plist",
    "theBeheader_animations.plist",
    "twilight_avenger_animations.plist",
    "twilight_avenger_effect_big_animations.plist",
    "twilight_avenger_effect_small_animations.plist",
    "twilight_avenger_explosion_animations.plist",
    "twilight_bannerbearer_animations.plist",
    "twilight_bannerbearer_aura_animations.plist",
    "twilight_bannerbearer_enemy_aura_animations.plist",
    "twilight_evoker_animations.plist", 
    "twilight_heretic_animations.plist", 
    "webspitterSpider_animations.plist", 
    "webspitterSpider_web_animations.plist"
};

bool TestLayer::init()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // load resources
    for (int i = 0; i < sizeof(ImageAnimationPlist)/sizeof(ImageAnimationPlist[0]); ++i) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ImageAnimationPlist[i]);
    }
    
   
    for (int i = 0; i < sizeof(AnimationNamePlist)/sizeof(AnimationNamePlist[0]); ++i) {
        PListReader::getInstance()->createAnimationWithPlist(AnimationNamePlist[i]);
    }
    
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level1_2-hd.plist");
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
    
    auto attacker = Sprite::createWithSpriteFrameName("redcap_0001.png");
    m_runningEnemy = Sprite::createWithSpriteFrameName("redcap_0001.png");
    auto actionAttack = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("redcap_attack")));
    if (!attacker || !actionAttack) {
        return false;
    }
    
    attacker->runAction(actionAttack);
    attacker->setPosition(Vec2(200, 200));
    m_bkg->addChild(attacker);
    m_bkg->addChild(m_runningEnemy);
    
    schedule(schedule_selector(TestLayer::moveSprite), 0.1);
    std::vector<std::vector<std::vector<Vec2> > > paths = PListReader::getInstance()->readPathPlist(1);
    m_path = paths[0][0];
    m_pathIndex = 0;
    return true;
}

void TestLayer::moveSprite(float dt)
{
    if (m_pathIndex + 1 >= m_path.size()) {
        unschedule(schedule_selector(TestLayer::moveSprite));
        m_bkg->removeChild(m_runningEnemy, true);
        return;
    }
    
    stopActions();
    Vec2 pos = m_path[m_pathIndex];
    Vec2 nextPos = m_path[m_pathIndex + 1];
    float angle = atan2f(nextPos.y - pos.y, nextPos.x - pos.x) * 180 / 3.14;
    CCLOG("angle =%f", angle);
    if (angle > -45 && angle <= 45) {
        // right
        CCLOG("->");
        auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("redcap_walkingRightLeft")));
        action->setTag(ActionTag_WalkingRight);
        m_runningEnemy->runAction(action);
    }
    else if (angle > 45 && angle <= 135) {
        // up
        auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("redcap_walkingUp")));
        action->setTag(ActionTag_WalkingUp);
        m_runningEnemy->runAction(action);
        CCLOG("Up");
    }
    else if (angle >=135 && angle <=225) {
        // left
        auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("redcap_walkingRightLeft")));
        action->setTag(ActionTag_WalkingLeft);
        m_runningEnemy->runAction(action);
        m_runningEnemy->setFlippedX(true);
        CCLOG("<-");
    }
    else {
        // down
        auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("redcap_walkingDown")));
        action->setTag(ActionTag_WalkingDown);
        m_runningEnemy->runAction(action);
        CCLOG("Down");
    }

    // 120, offset of path_x
    // 100, offset of path_y
    m_runningEnemy->setPosition(Vec2(s_rate * (nextPos.x + 120), s_rate * (nextPos.y + 100) + 59));
    ++m_pathIndex;
}

void TestLayer::stopActions()
{
    for (int i = 0; i <　static_cast<int>(ActionTag_Num); ++i) {
        m_runningEnemy->stopActionByTag(i);
    }
}
