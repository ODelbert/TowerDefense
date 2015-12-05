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
#   include "tests/TestLayer.h"
#endif
#include "PListReader.h"
#include "ResourceManager.h"
#include "Layer/EncyclopediaLayer.h"
#include "Layer/TouchLayer.h"
#include "Maps/Stage1.h"

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
    
    ResourceManager::getInstance()->initialize();
    
    
#if 1//def TD_TEST
    auto layer = Stage1::create();
    addChild(layer);
#else
    
    auto layer = EncyclopediaLayer::create();
    addChild(layer);
    auto touchLayer = TouchLayer::create();
    addChild(touchLayer, -1);
#endif
    return true;
}
