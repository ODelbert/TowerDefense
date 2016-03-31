#include "Bullet.h"

Bullet::Bullet()
{
}

ParabalicTrace* ParabalicTrace::create(float duration, Vec2 start, Vec2 end, float height)
{
    ParabalicTrace* ret = new ParabalicTrace;
    if (ret && ret->init(duration, start, end, height)) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool ParabalicTrace::init(float duration, Vec2 start, Vec2 end, float height)
{
    m_duration = duration;
    m_startPos = start;
    m_endPos = end;
    m_height = height;
    return true;
}

virtual void update(float dt);

ArrowTrace* ArrowTrace::create(Sprite *arrow, Sprite *enemy, float sa, float ea, float speed)
{
    ArrowTrace* ret = new ArrowTrace;
    if (ret && ret->init(arrow, enemy, sa, ea, spped)) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool ArrowTrace::init(Sprite *arrow, Sprite *enemy, float sa, float ea, float speed)
{
    if (!arrow || !target) {
        return false;
    }

    m_startAngle = sa;
    m_angle = sa;
    m_endAngle = ea;
    m_speed = speed;
    m_enemy = enemy;
    m_isLost = false;
    m_xDelta = enemy->getPosition().x - _target->getPosition().x;
    startWithTarget(arrow);
    //TODO: fix image rotation

    if (0 == m_distance) {
        return false;
    }

    return true;
}

void ArrowTrace::update(float dt)
{
    if (!m_isLost) {

    }
    else {
        _target->setPosition(_target->getPosition().x + sin(m_angle) * dt, _target->getPosition().y + cos(m_angle) * dt);
        float xDelta = enemy->getPosition().x - _target->getPosition().x;
        float fulfillPrecent = 1 - xDelta / m_xDelta;
        m_angle = m_startAngle +  fulfillPrecent * (m_endAngle - m_startAngle);
        //TODO: fix image rotation
        if (_target->getPosition().distanceSquared(m_enemy->getPosition()) < 1.0) {
            // TODO:: enemy get hurt
            // TODO:: remove arrow
        }
    }
}

void ArrowTrace::targetLost(Vec2 lostPos)
{
    m_isLost = true;
    m_lostPos = lostPos;
    m_target = nullptr;
}