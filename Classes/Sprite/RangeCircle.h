#ifndef RANGECIRCLE_H
#define RANGECIRCLE_H

#include "cocos2d.h"
USING_NS_CC;

class RangeCircle : public Node
{
public:
    enum RangeRank
    {
        VeryShort = 20,
        Short = 40,
        Normal = 60,
        Long = 80,
        VeryLong = 100,
        Extreme = 120
    };

    enum RangeType
    {
        Attack = 0,
        Defense
    };

public:
    static RangeCircle* create(RangeRank rank, RangeType type);
    virtual bool init(RangeRank rank, RangeType type);

};

#endif // RANGECIRCLE_H
