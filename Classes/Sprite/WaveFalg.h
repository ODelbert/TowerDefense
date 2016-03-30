
#ifndef WAVEFALG_H
#define WAVEFALG_H

#include "cocos2d.h"
#include "TouchNode.h"

USING_NS_CC;

class WaveFalg : public TouchNode
{
    enum State { enabled, selected };
    enum Type { normal, flying };

public:
    static WaveFlag* create(Type type = normal, float duration);
    virtual bool init(Type type = normal, float duration);
    void onTouchEvent();

private:
    ProgressTimer* m_circle;
    Sprite* m_breathLed;
    State m_state;
};

#endif // WAVEFALG_H
