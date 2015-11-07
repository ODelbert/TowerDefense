//
//  TestLayer.h
//  TowerDefense
//
//  Created by jowu on 15/10/31.
//  test class
//

#ifndef __TowerDefense__TestLayer__
#define __TowerDefense__TestLayer__

#include <stdio.h>
#include <vector>
#include "cocos2d.h"

USING_NS_CC;

class TestLayer : public Layer
{
public:
    CREATE_FUNC(TestLayer)
    virtual bool init() override;
    
private:
    void moveSprite(float dt);
    
private:
    Sprite* m_bkg;
    std::vector<Vec2> m_path;
    Sprite* m_runningEnemy;
    unsigned int m_pathIndex;
};

#endif /* defined(__TowerDefense__TestLayer__) */
