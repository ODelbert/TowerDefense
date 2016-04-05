#include "RangeCircle.h"

// rally_circle.png

RangeCircle* RangeCircle::create(RangeRank rank, RangeType type)
{
    RangeCircle* ret = new RangeCircle;
    if (ret && ret->init(rank, type)) {
         ret->autorelease();
         return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool RangeCircle::init(RangeRank rank, RangeType type)
{
    auto c1 = Sprite::createWithSpriteFrameName("range_circle.png");
    auto c2 = Sprite::createWithSpriteFrameName("range_circle.png");
    auto c3 = Sprite::createWithSpriteFrameName("range_circle.png");
    auto c4 = Sprite::createWithSpriteFrameName("range_circle.png");
    c1->setAnchorPoint(Point(1,0));
    c2->setFlippedX(true);
    c2->setAnchorPoint(Point(0,0));
    c3->setFlippedX(true);
    c3->setFlippedY(true);
    c3->setAnchorPoint(Point(0,1));
    c4->setFlippedY(true);
    c4->setAnchorPoint(Point(1,1));
    addChild(c1);
    addChild(c2);
    addChild(c3);
    addChild(c4);
    return true;
}
