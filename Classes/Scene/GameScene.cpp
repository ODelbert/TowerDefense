//
//  GameScene.cpp
//  TowerDefense
//
//  Created by jowu on 15/10/31.
//
//

#include "GameScene.h"
#include "CommonDef.h"
#ifdef TD_TEST
#   include "TestLayer.h"
#endif
#include "PListReader.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
#ifdef TD_TEST
    auto layer = TestLayer::create();
    addChild(layer);
#else
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
#endif
    return true;
}
