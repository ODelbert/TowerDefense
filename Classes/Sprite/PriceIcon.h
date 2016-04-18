#ifndef PRICEICON_H
#define PRICEICON_H

#include "cocos2d.h"
USING_NS_CC;

class PriceIcon : public Node
{
public:
    static PriceIcon* create(int gold);
    virtual bool init();

    CC_SYNTHESIZE(int, m_gold, Gold)

private:
    Sprite* m_texture;
};


class NumberIcon
{

};

#endif // PRICEICON_H
