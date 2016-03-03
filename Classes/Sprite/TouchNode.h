//
//  TouchNode.h
//  TowerDefense
//
//  Created by jowu on 16/3/4.
//
//

#ifndef TouchNode_h
#define TouchNode_h

#include <vector>
#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;

class TouchNode : public Node
{
public:
    CREATE_FUNC(TouchNode);
    virtual bool init();
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    
protected:
    bool isTouched(Touch* touch);
};


#endif /* TouchNode_hpp */
