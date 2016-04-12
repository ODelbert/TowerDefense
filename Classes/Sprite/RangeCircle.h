#ifndef RANGECIRCLE_H
#define RANGECIRCLE_H

#include "cocos2d.h"
#include "commonDef.h"

USING_NS_CC;

class RangeCircle : public Node
{
public:
    enum RangeRank
    {
        VeryShort = 120,
        Short = 140,
        Normal = 160,
        Long = 180,
        Great = 210,
        Extreme = 260
    };

public:
    static RangeCircle* create(RangeType rangeType, TowerType towerType);
    virtual bool init(RangeType rangeType, TowerType towerType);

};

#endif // RANGECIRCLE_H
