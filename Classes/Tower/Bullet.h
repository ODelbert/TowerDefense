#ifndef BULLET_H
#define BULLET_H

#include "cocos2d.h"
USING_NS_CC;

// Arrow   -----> archer
// Gun/Xray    -----> archer sliver instanst kill
// Canon/Stone -----> artilley
// MagicBall ----> mage

/*
 *
 *
 * startAngle 【float】
endAngle 【float】
speed 【float】
weight [float 阻力系数]
target [sprite]
startpos [vec]

     def create(target, startAngle, endAngle, speed, weight, startPos):
          s_distance = distance(target->getPosition(), startPos)
          m_angle = angle




     def update(float dt):
          distance = distance(target->getPosition(), startPos)
          precent = distance / s_distance
          angle = startAngle + (endAngle - startAngle) * precent
          rotateAngle = angle - m_angle
          // FIXME: set rotation !!
          m_angle = angle


 * /

class BulletAction : public ActionInterval
{
public:
    enum ActionType
    {
        ray, // xray
        track, // trackable
        curve, // para-curve
    };



};

class Bullet : public Node
{
public:
    Bullet();

    void setTarget(Sprite* target);

private:
    Sprite* m_texture;
};

#endif // BULLET_H
