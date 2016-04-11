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
        VeryShort = 20,
        Short = 40,
        Normal = 60,
        Long = 80,
        Great = 100,
        Extreme = 120
    };

public:
    static RangeCircle* create(RangeType rangeType, TowerType towerType);
    virtual bool init(RangeType rangeType, TowerType towerType);

};

#endif // RANGECIRCLE_H
