#ifndef BULLET_H
#define BULLET_H

#include "cocos2d.h"
#include "CommonDef.h"
USING_NS_CC;

// Arrow   -----> archer
// Gun/Xray    -----> archer sliver instanst kill
// Canon/Stone -----> artilley
// MagicBall ----> mage


class Tower;
//class ParabalicTrace : public ActionInterval
//{
//public:
//    static ParabalicTrace* create(float duration, Vec2 start, Vec2 end, float height);
//    virtual bool init(float duration, Vec2 start, Vec2 end, float height);
//    virtual void update(float dt);
//
//private:
//    Vec2 m_startPos;
//    Vec2 m_endPos;
//    float m_duration;
//    float m_height;
//};
//
//class ArrowTrace : public ActionInterval
//{
//public:
//    static ArrowTrace* create(Sprite* arrow, Sprite* enenmy, float sa, float ea, float speed);
//    virtual bool init(Sprite* arrow, Sprite* enenmy, float sa, float ea, float speed);
//    virtual void update(float dt);
//    void targetLost();
//
//private:
//    float m_startAngle;
//    float m_endAngle;
//    float m_angle;
//    float m_speed;
//    Sprite* m_enemy;
//
//    float m_xDelta;
//    bool m_isLost;
//    Vec2 m_lostPos;
//};

class Bullet : public Node
{
public:
    CC_SYNTHESIZE(Vec2, m_destination, Destination)
    CC_SYNTHESIZE(int, m_damage, Damage)
    CC_SYNTHESIZE(WeaponType, m_weapon, Weapon)

    virtual void launch(int slotId) {}
    virtual void strike() {}
    
protected:
    explicit Bullet();

protected:
    Sprite* m_texture;
};

class BallBullet : public Bullet
{
public:
    static BallBullet* create();
    virtual bool init();
    virtual void launch(int slotId);
};

#endif // BULLET_H
