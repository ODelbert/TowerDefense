#ifndef LIFEBAR_H
#define LIFEBAR_H

#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;

class LifeBar : public Node
{
public:
    enum Scale { Small = 0, Med, MedBig, Big  };

public:
    static LifeBar* create(Sprite* owner = 0, Scale scale = Small);
    virtual bool init(Scale scale);
    void setPercentage(float precent);

private:
    LifeBar(Sprite* owner);
    
private:
    Sprite* m_owner;
    ProgressTimer* m_bar;
};

#endif // LIFEBAR_H


