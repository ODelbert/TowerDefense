//
//  TestMapLocation.cpp
//  TowerDefense
//
//  Created by jowu on 15/12/9.
//
//

#include "TestMapLocation.h"
#include "CommonDef.h"
#include "Base/WaveManager.h"
#include "Enemy/EnemyFactory.h"
#include "Base/WaveManager.h"
#include "Enemy/EnemyFactory.h"

static bool s_flag = false;
bool TestMapLocation::init()
{
    pathIndex = 0;
    subPathIndex = 0;
    auto touchlistener = EventListenerTouchOneByOne::create();
    touchlistener->onTouchBegan = CC_CALLBACK_2(TestMapLocation::onTouchBegan, this);
    touchlistener->onTouchEnded = CC_CALLBACK_2(TestMapLocation::onTouchEnded, this);
    touchlistener->onTouchMoved = CC_CALLBACK_2(TestMapLocation::onTouchMoved, this);
    touchlistener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener,this);
    
    auto waveListener = EventListenerCustom::create("WaveEvent", [=](EventCustom* event){
        typedef struct _WaveEventData {
            int id;
            int path;
            int subPath;
        } WaveEventData;
        
        WaveEventData* info = static_cast<WaveEventData*>(event->getUserData());
        
        auto enmey = EnemyFactory::create(static_cast<EnemyID>(info->id));
        enmey->sendToBattle(WaveManager::getInstance()->getPath(info->path, info->subPath));
        m_mapSprite->addChild(enmey);
    });
    
    _eventDispatcher->addEventListenerWithFixedPriority(waveListener, 1);
    loadLevel(1, 0);
    return true;
}

bool TestMapLocation::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("touch at pos [%f %f]", touch->getStartLocation().x, touch->getStartLocation().y);
    return true;
}

void TestMapLocation::onTouchEnded(Touch* touch, Event* event)
{
}

void TestMapLocation::onTouchMoved(Touch* touch, Event* event)
{
    Vec2 offset = touch->getLocation() - touch->getPreviousLocation();
    base->setPosition(base->getPosition() + offset);
    CCLOG("set at pos %f %f", base->getPosition().x, base->getPosition().y);
    /*
     if (base->getPosition().x + offset.x > 0.5 * MAP_WIDTH) {
     newPos.x = 0.5 * MAP_WIDTH;
     }
     else if (base->getPosition().x + offset.x < TD_WIDTH - 0.5 * MAP_WIDTH) {
     newPos.x = TD_WIDTH - 0.5 * MAP_WIDTH;
     }
     else {
     newPos.x = base->getPosition().x + offset.x;
     }
     
     if (base->getPosition().y + offset.y > 0.5 * MAP_HEIGHT) {
     newPos.y = 0.5 * MAP_HEIGHT;
     }
     else if (base->getPosition().y + offset.y < TD_HEIGHT - 0.5 * MAP_HEIGHT) {
     newPos.y = TD_HEIGHT - 0.5 * MAP_HEIGHT;
     }
     else {
     newPos.y = base->getPosition().y + offset.y;
     }
     
     base->setPosition(newPos);
     */
}

void TestMapLocation::loadLevel(int stage, int difficult)
{
    if (0 >= stage || 10 <= stage) return;
    currentStage = stage;
    
    WaveManager::getInstance()->initialize(stage, difficult);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(String::createWithFormat("sprite_level%d_2-hd.plist", stage)->getCString());
    m_mapSprite = Sprite::createWithSpriteFrameName(String::createWithFormat("Stage_%d.png", stage)->getCString());
    
    if (m_mapSprite) {
        m_mapSprite->setPosition(TD_WIDTH / 2, TD_HEIGHT / 2);
        addChild(m_mapSprite);
    }
    
    base = new Node;
    if (base) {
        base->setPosition(0,0);
        addChild(base);
        base->removeAllChildren();
        std::vector<Vec2> paths = WaveManager::getInstance()->getPath(pathIndex, subPathIndex);
        for (int i = 0; i < paths.size(); ++i) {
            auto sp = Sprite::createWithSpriteFrameName("redcap_0001.png");
            base->addChild(sp);
            sp->setPosition(paths[i].x * 1.15 + 12, (paths[i].y) * 1.13 - 73);
            log("pos %f %f", paths[i].x * 1.15 + 60, (paths[i].y) * 1.13 - 95);
        }
    }
    
    scaleX = LabelTTF::create("1.0", TD_FONT, 20);
    scaleX->setColor(Color3B(102, 51, 0));
    scaleX->setPosition(400, TD_HEIGHT - 80);
    m_mapSprite->addChild(scaleX);
    
    scaleY = LabelTTF::create("1.0", TD_FONT, 20);
    scaleY->setColor(Color3B(102, 51, 0));
    scaleY->setPosition(400, TD_HEIGHT - 300);
    m_mapSprite->addChild(scaleY);
    
    scaleXUp = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png"), Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0002.png"), [&](Ref *sender) {
        float sfx = atof(scaleX->getString().c_str());
        float sfy = atof(scaleY->getString().c_str());
        sfx = sfx + 0.01f;
        char buf[50];
        snprintf(buf, 10,  "%f", sfx);
        std::string labelString(buf);
        scaleX->setString(labelString);
        base->removeAllChildren();
        for (int k = 0; k < 3; ++k) {
            std::vector<Vec2> paths = WaveManager::getInstance()->getPath(pathIndex, k);
            for (int i = 0; i < paths.size(); ++i) {
                auto sp = Sprite::createWithSpriteFrameName("redcap_0001.png");
                base->addChild(sp);
                sp->setPosition(paths[i].x * sfx, (paths[i].y * sfy));
            }
        }
    }), NULL);
    
    m_mapSprite->addChild(scaleXUp);
    scaleXUp->setPosition(600, TD_HEIGHT - 80);
    
    scaleXDown = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png"), Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0002.png"), [&](Ref *sender) {
        float sfx = atof(scaleX->getString().c_str());
        sfx = sfx - 0.01f;
        char buf[50];
        snprintf(buf, 10,  "%f", sfx);
        std::string labelString(buf);
        scaleX->setString(labelString);
        float sfy = atof(scaleY->getString().c_str());
        base->removeAllChildren();
        for (int k = 0; k < 3; ++k) {
            std::vector<Vec2> paths = WaveManager::getInstance()->getPath(pathIndex, k);
            for (int i = 0; i < paths.size(); ++i) {
                auto sp = Sprite::createWithSpriteFrameName("redcap_0001.png");
                base->addChild(sp);
                sp->setPosition(paths[i].x * sfx, (paths[i].y * sfy));
            }
        }
    }), NULL);
    
    m_mapSprite->addChild(scaleXDown);
    scaleXDown->setPosition(200, TD_HEIGHT - 80);
    
    //    scaleXDown->setPosition(50, TD_HEIGHT - 80);
    //
    //    scaleYUp->setPosition(150, TD_HEIGHT - 160);
    //    scaleYDown->setPosition(50, TD_HEIGHT - 160);
    
    
    scaleYUp = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png"), Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0002.png"), [&](Ref *sender) {
        float sfx = atof(scaleX->getString().c_str());
        float sfy = atof(scaleY->getString().c_str());
        sfy = sfy + 0.01f;
        char buf[50];
        snprintf(buf, 10,  "%f", sfy);
        std::string labelString(buf);
        scaleY->setString(labelString);
        base->removeAllChildren();
        for (int k = 0; k < 3; ++k) {
            std::vector<Vec2> paths = WaveManager::getInstance()->getPath(pathIndex, k);
            for (int i = 0; i < paths.size(); ++i) {
                auto sp = Sprite::createWithSpriteFrameName("redcap_0001.png");
                base->addChild(sp);
                sp->setPosition(paths[i].x * sfx, (paths[i].y * sfy));
            }
        }
    }), NULL);
    
    m_mapSprite->addChild(scaleYUp);
    scaleYUp->setPosition(600, TD_HEIGHT - 300);
    
    scaleYDown = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png"), Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0002.png"), [&](Ref *sender) {
        float sfx = atof(scaleX->getString().c_str());
        float sfy = atof(scaleY->getString().c_str());
        sfy = sfy - 0.01f;
        char buf[50];
        snprintf(buf, 10,  "%f", sfy);
        std::string labelString(buf);
        scaleY->setString(labelString);
        base->removeAllChildren();
        for (int k = 0; k < 3; ++k) {
            std::vector<Vec2> paths = WaveManager::getInstance()->getPath(pathIndex, k);
            for (int i = 0; i < paths.size(); ++i) {
                auto sp = Sprite::createWithSpriteFrameName("redcap_0001.png");
                base->addChild(sp);
                sp->setPosition(paths[i].x * sfx, (paths[i].y * sfy));
            }
        }
    }), NULL);
    
    m_mapSprite->addChild(scaleYDown);
    scaleYDown->setPosition(200, TD_HEIGHT - 300);
    
    nextStage = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png"), Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0002.png"), [&](Ref *sender) {
        loadLevel(currentStage + 1, 0);
    }), NULL);
    
    m_mapSprite->addChild(nextStage);
    nextStage->setPosition(600, TD_HEIGHT - 800);
    
    previousStage = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png"), Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0002.png"), [&](Ref *sender) {
        loadLevel(currentStage - 1, 0);
    }), NULL);
    
    m_mapSprite->addChild(previousStage);
    previousStage->setPosition(400, TD_HEIGHT - 800);
    
    
    
    nextPath = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png"), Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0002.png"), [&](Ref *sender) {
        pathIndex = (pathIndex + 1) % WaveManager::getInstance()->getPathCount();
        loadLevel(currentStage, 0);
    }), NULL);
    
    m_mapSprite->addChild(nextPath);
    nextPath->setPosition(100, TD_HEIGHT - 800);
    
    
    nextSubPath = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png"), Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0002.png"), [&](Ref *sender) {
        subPathIndex = (subPathIndex + 1) % 3;
        loadLevel(currentStage, 0);
    }), NULL);
    
    m_mapSprite->addChild(nextSubPath);
    nextSubPath->setPosition(200, TD_HEIGHT - 800);
}
