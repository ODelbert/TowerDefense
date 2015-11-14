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
#include "ResourceManager.h"
#include "EncyclopediaLayer.h"
#include "TouchLayer.h"

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
    
    ResourceManager::getInstance()->initialize();
    
    auto layer = EncyclopediaLayer::create();
    addChild(layer);
    auto touchLayer = TouchLayer::create();
    addChild(touchLayer, -1);
#endif
    return true;
}
