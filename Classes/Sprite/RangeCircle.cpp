#include "RangeCircle.h"

// rally_circle.png

RangeCircle* RangeCircle::create(RangeType rank, TowerType type)
{
    RangeCircle* ret = new RangeCircle;
    if (ret && ret->init(rank, type)) {
         ret->autorelease();
         return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool RangeCircle::init(RangeType rank, TowerType type)
{
    auto c1 = Sprite::createWithSpriteFrameName(TowerType_Barracks == type ? "rally_circle.png" : "range_circle.png");
    auto c2 = Sprite::createWithSpriteFrameName(TowerType_Barracks == type ? "rally_circle.png" : "range_circle.png");
    auto c3 = Sprite::createWithSpriteFrameName(TowerType_Barracks == type ? "rally_circle.png" : "range_circle.png");
    auto c4 = Sprite::createWithSpriteFrameName(TowerType_Barracks == type ? "rally_circle.png" : "range_circle.png");
    log("size rang = %f %f", c1->getContentSize().width, c1->getContentSize().height);
    c1->setAnchorPoint(Point(1,0));
    //c1->setScale(c1->getContentSize().width / static_cast<RangeRank>(rank));
    c2->setFlippedX(true);
    c2->setAnchorPoint(Point(0,0));
    //c2->setScale(c1->getContentSize().width / static_cast<RangeRank>(rank));
    c3->setFlippedX(true);
    c3->setFlippedY(true);
    c3->setAnchorPoint(Point(0,1));
    //c3->setScale(c1->getContentSize().width / static_cast<RangeRank>(rank));
    c4->setFlippedY(true);
    c4->setAnchorPoint(Point(1,1));
    //c4->setScale(c1->getContentSize().width / static_cast<RangeRank>(rank));
    addChild(c1);
    addChild(c2);
    addChild(c3);
    addChild(c4);
    return true;
}
