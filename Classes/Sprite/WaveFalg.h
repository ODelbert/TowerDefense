#ifndef WAVEFALG_H
#define WAVEFALG_H

#include "cocos2d.h"
#include "TouchNode.h"

USING_NS_CC;

class WaveFalg : public TouchNode
{
    enum State { enabled, selected };

public:
    static WaveFlag* create(float duration);
    virtual bool init();
    void onTouchEvent();

private:
    ProgressTimer* m_circle;
};

#endif // WAVEFALG_H
