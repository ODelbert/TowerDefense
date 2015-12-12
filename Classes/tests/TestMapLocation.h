//
//  TestMapLocation.h
//  TowerDefense
//
//  Created by jowu on 15/12/9.
//
//

#ifndef __TowerDefense__TestMapLocation__
#define __TowerDefense__TestMapLocation__

#include "cocos2d.h"
USING_NS_CC;

class TestMapLocation : public Layer
{
public:
    CREATE_FUNC(TestMapLocation);
    bool init();

    void loadLevel(int stage, int difficult);
    
    virtual bool onTouchBegan(Touch* touch, Event* event) override;
    virtual void onTouchMoved(Touch* touch, Event* event) override;
    virtual void onTouchEnded(Touch* touch, Event* event) override;

protected:
    Sprite* m_mapSprite;
    Node* base;
    
    int currentStage;
    int pathIndex;
    int subPathIndex;
    Menu* scaleXUp;
    Menu* scaleXDown;
    Menu* scaleYUp;
    Menu* scaleYDown;
    Menu* previousStage;
    Menu* nextStage;
    Menu* nextPath;
    Menu* nextSubPath;
    LabelTTF* scaleX;
    LabelTTF* scaleY;
};

#endif /* defined(__TowerDefense__TestMapLocation__) */
