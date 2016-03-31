
#ifndef WAVEFALG_H
#define WAVEFALG_H

#include "cocos2d.h"
#include "TouchNode.h"

USING_NS_CC;

class WaveFlag : public TouchNode
{
public:
    enum Type { Normal, Flying };

public:
    static WaveFlag* create(Type type, float duration);
    virtual bool init(Type type, float duration);
    void onTouchEvent();
    void onTimeout();
    
private:
    ProgressTimer* m_circle;
    Sprite* m_breathLed;
    Sprite* m_selectedRing;
};

#endif // WAVEFALG_H
