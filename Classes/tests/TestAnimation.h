//
//  TestAnimation.h
//  TowerDefense
//
//  Created by jowu on 15/12/18.
//
//

#ifndef __TowerDefense__TestAnimation__
#define __TowerDefense__TestAnimation__

#include "cocos2d.h"
#include "Animation/AnimationManager.h"

USING_NS_CC;

struct _Tag2Name;
class TestAnimation : public Layer
{
public:
    CREATE_FUNC(TestAnimation);
    virtual bool init();
    
    void demonstrateEnemy(const _Tag2Name* tags, int len);
    void demonstrateTower(const _Tag2Name* tags, int len);
    Menu* rootMenu;
    Menu* enemyMenu;
    Node* baseTower;
    Node* baseEnemy;
    int counterE;
    int counterT;
    
};

#endif /* defined(__TowerDefense__TestAnimation__) */
