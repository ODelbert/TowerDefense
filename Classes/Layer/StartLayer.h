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
    CREATE_FUNC(StartLayer)
    bool init();
    
private:
    void onStartBtnClick();
    void onCreditBtnClick();
    void onKeySoundBtnClick();
    void onBGMBtnClick();
    
private:
    Sprite* m_bkg;
    Sprite* m_logo;
    Sprite* m_logoBrillo;
    bool m_isKeySoundOn;
    bool m_isBGMOn;
};
#endif /* StartLayer_hpp */
