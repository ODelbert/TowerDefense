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
    static TouchNode* create(const std::string& name);
    virtual bool init(const std::string& name);

    // void setTouchCallback(onTouchBegan begin, onTouchMoved move, onTouchEnded end);
    
protected:
	virtual bool handleEvent(Event* touch);

private:
	virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);

private:
	Sprite* m_texture;
};

#endif /* TouchNode_hpp */
