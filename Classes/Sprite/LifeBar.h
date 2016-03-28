#ifndef LIFEBAR_H
#define LIFEBAR_H

#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;

class LifeBar : public Node
{
public:
    static LifeBar* create(Sprite* owner = 0);
    virtual bool init(Sprite* parent);
    void setPercentage(float precent);

private:
    Sprite* m_owner;
    ProgressTimer* m_bar;
};

#endif // LIFEBAR_H
