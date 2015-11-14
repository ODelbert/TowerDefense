//
//  StartLayer.hpp
//  TowerDefense
//
//  Created by bluesChen on 15/11/11.
//
//

#ifndef __TowerDefense__EncyclopediaLayer__
#define __TowerDefense__EncyclopediaLayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class StartLayer : public Layer
{
public:
    CREATE_FUNC(StartLayer);
    bool init();
private:
    Sprite* m_bkg;
    Sprite* m_logo;
};
#endif /* StartLayer_hpp */
