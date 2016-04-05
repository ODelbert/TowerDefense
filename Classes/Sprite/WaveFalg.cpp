#include "WaveFalg.h"

WaveFlag* WaveFlag::create(WaveFlag::Type type, float duration)
{
    WaveFlag* ret = new WaveFlag;
    if (ret && ret->init(type, duration)) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool WaveFlag::init(Type type, float duration)
{
    m_circle = ProgressTimer::create(Sprite::createWithSpriteFrameName("waveFlag_0003.png"));
    m_circle->setType(ProgressTimer::Type::RADIAL);
    
    m_breathLed = Sprite::createWithSpriteFrameName(String::createWithFormat("waveFlag_000%d.png", static_cast<int>(type + 1))->getCString());
    m_selectedRing = Sprite::createWithSpriteFrameName("waveFlag_selected.png");
    m_selectedRing->setVisible(false);
    addChild(m_circle);
    addChild(m_breathLed);
    addChild(m_selectedRing);
    
    auto scaleAction = RepeatForever::create(Sequence::create(ScaleBy::create(1.0, 1.25), ScaleBy::create(1.0, 0.8), nullptr));
    m_breathLed->runAction(scaleAction);
    m_circle->runAction(Spawn::createWithTwoActions(scaleAction->clone(), Sequence::create(ProgressTo::create(duration, 100), CallFunc::create(CC_CALLBACK_0(WaveFlag::onTimeout, this)), nullptr)));
    
    return true;
}

void WaveFlag::onTimeout()
{
    removeFromParent();
    // TODO:: fix waves
}

void WaveFlag::onTouchEvent()
{
    if (TouchNode::Enabled == m_state) {
        // TODO:: show wave info
        m_selectedRing->setVisible(true);
    }
    else if (TouchNode::Selected == m_state) {
        // TODO:: start a wave
        // TODO:: gold bonus
        removeFromParent();
    }
}

