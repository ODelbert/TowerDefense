//
//  TouchLayer.h
//  TowerDefense
//
//  Created by jowu on 15/11/13.
//
//

#ifndef __TowerDefense__TouchLayer__
#define __TowerDefense__TouchLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class TouchLayer : public Layer
{
public:
    CREATE_FUNC(TouchLayer);
    virtual bool init() override;
    
    virtual bool onTouchBegan(Touch* touch, Event* event) override;
    virtual void onTouchEnded(Touch* touch, Event* event) override;
    virtual void onTouchMoved(Touch* touch, Event* event) override;
};


#endif /* defined(__TowerDefense__TouchLayer__) */
