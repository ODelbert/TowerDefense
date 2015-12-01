//
//  Level1.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/16.
//
//

#include "Stage1.h"
#include "CommonDef.h"
#include "Controller/WaveManager.h"
bool Stage1::init()
{
    //    ResourceManager::getInstance()->initialize();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level1_2-hd.plist");
    m_mapSprite = Sprite::createWithSpriteFrameName("Stage_1.png");
    
    loadLevel(1, 1);
    
    if (m_mapSprite) {
        m_mapSprite->setPosition(TD_WIDTH/2, TD_HEIGHT/2);
        addChild(m_mapSprite);
    }
    else {
        return false;
    }
    
    schedule(schedule_selector(BattleField::start), 0.0f, 1, 5.0f);
    
    return true;
}