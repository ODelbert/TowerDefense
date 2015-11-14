//
//  GameScene.h
//  TowerDefense
//
//  Created by jowu on 15/10/31.
//
//

#ifndef __TowerDefense__GameScene__
#define __TowerDefense__GameScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class GameScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene)
};

#endif /* defined(__TowerDefense__GameScene__) */
