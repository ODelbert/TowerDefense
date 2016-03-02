//
//  GameManager.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/22.
//
//

#include "cocos2d.h"
#include "GameManager.h"
#include "Singleton.h"


USING_NS_CC;


class Technology;
class DamageSystem;
class GameManager : public Ref, public Singleton<GameManager>
{
public:
    GameManager();
    
    CC_SYNTHESIZE(int, m_gold, Gold);
    
private:
    
};
