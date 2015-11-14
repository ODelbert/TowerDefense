//
//  EncyclopediaLayer.h
//  TowerDefense
//
//  Created by jowu on 15/11/7.
//
//

#ifndef __TowerDefense__EncyclopediaLayer__
#define __TowerDefense__EncyclopediaLayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class EnemyBook;
class TowerBook;

class EncyclopediaLayer : public Layer
{
public:
    CREATE_FUNC(EncyclopediaLayer);
    bool init();
    
    void close(Ref* sender);
    
private:
    EnemyBook* m_eBook;
    TowerBook* m_tBook;
};



#endif /* defined(__TowerDefense__EncyclopediaLayer__) */
