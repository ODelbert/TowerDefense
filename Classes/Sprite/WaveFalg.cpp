#include "WaveFalg.h"

static WaveFlag* create(float duration);

bool WaveFalg::init(float duration)
{
    m_circle = ProgressTimer::create(Sprite::create("TODO.png"));
    addChild(m_circle);

    m_circle->runAction(ProgressTo(duration, 100));
    return true;
}






virtual bool init();
void onTouchEvent();
