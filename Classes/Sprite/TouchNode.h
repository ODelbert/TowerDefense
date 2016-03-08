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
    typedef std::function<void()> TouchCallBack;
public:
    enum State {
        Enabled = 0,
        Selected,
        Disabled
    };
    
public:
    static TouchNode* create(const std::string& name);
    virtual bool init(const std::string& name);

    void setTouchCallback(TouchCallBack callBack);
    bool inTouchRegion(Touch* touch);

    CC_SYNTHESIZE(State, m_state, State)
    CC_SYNTHESIZE(bool, m_forceLock, ForceLock) // designed for GatherFlag
protected:
    TouchNode();
    void initTouchListeners();
	virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);

protected:
	Sprite* m_texture;
    bool m_isTouchBegan;
    TouchCallBack m_callback;
};

#endif /* TouchNode_hpp */
