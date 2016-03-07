#ifndef GATHERFLAG_H
#define GATHERFLAG_H

#include "cocos2d.h"
#include "TouchNode.h"
USING_NS_CC;

class AllyFlag : public Node
{
public:
    CREATE_FUNC(AllyFlag);
    virtual bool init();

    void setFlagAt(Vec2 pos);
private:
    Sprite* m_texture;
};

class Assembly : public TouchNode
{
public:
    static Assembly* create(int slotId);
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    CC_SYNTHESIZE(int, m_slotId, SlotId)

private:
    int m_range;
};

#endif // GATHERFLAG_H
