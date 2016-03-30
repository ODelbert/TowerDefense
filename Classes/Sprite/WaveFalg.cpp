
#include "WaveFalg.h"

static WaveFlag* create(Type type, float duration)
{
    WaveFlag* ret = new WaveFlag;
    if (ret && ret->init(type, duration)) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool WaveFalg::init(Type type, float duration)
{
    m_circle = ProgressTimer::create(Sprite::create("TODO.png"));
    m_breathLed = Sprite::createWithSpriteFrameName("TODO.png")
    addChild(m_circle);
    addChild(m_breathLed);

    m_circle->runAction(Sequence::create(ProgressTo(duration, 100), CallFunc::create(CC_CALLBACK_0(WaveFalg::onTouchEvent, this))));
    return true;
}

void WaveFalg::onTouchEvent()
{

    if (state == State::enabled) {
        // TODO:: show wave info
    }
    else if (state == State::selected) {
        // TODO:: start a wave
        // TODO:: gold bonus
        removeFromParent();
    }
}

