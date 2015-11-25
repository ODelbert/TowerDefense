//
//  WaveManager.h
//  TowerDefense
//
//  Created by jowu on 15/11/22.
//
//

#ifndef __TowerDefense__WaveManager__
#define __TowerDefense__WaveManager__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;



class WaveManager : public Ref
{
public:
    static WaveManager* getInstance();
    static void destroy();
    
    void loadWave(int level, int difficulty);
    
private:
    static WaveManager* s_instance;
    
    
private:
    int m_cash;
    
};

#endif /* defined(__TowerDefense__WaveManager__) */
