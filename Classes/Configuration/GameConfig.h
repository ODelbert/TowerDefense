//
//  GameConfig.h
//  TowerDefense
//
//  Created by jowu on 15/11/15.
//
//

#ifndef __TowerDefense__Configuration__
#define __TowerDefense__Configuration__

#include <vector>
#include "cocos2d.h"
#include "PListReader.h"

USING_NS_CC;

//struct TowerInfo;
//enum TowerID;
class GameConfig : public Ref
{
public:
    static GameConfig* getInstance();
    static void destroy();
    
    void initialize();
    EnemyInfo getEnemyInfo(EnemyID id);
//    TowerInfo getTowerInfo(TowerID id);
    
private:
    static GameConfig* s_instance;
    
private:
    std::vector<EnemyInfo> m_enemyInfo;
//    std::vector<TowerInfo> m_towerInfo;
};


#endif /* defined(__TowerDefense__Configuration__) */
