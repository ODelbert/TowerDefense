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
#include "Base/Singleton.h"

USING_NS_CC;

struct EnemyInfo;
struct TowerInfo;
//enum TowerID;
class GameConfig : public Ref, public Singleton<GameConfig>
{
public:
    GameConfig();
    
    void initialize();
    static int upgradeGold(TowerID id, TowerLevel lv);
    static TowerInfo getTowerInfo(TowerID id, TowerLevel lv);
    static EnemyInfo getEnemyInfo(EnemyID id);

private:
    std::vector<EnemyInfo> m_enemyInfo;
//    std::vector<TowerInfo> m_towerInfo;
};


#endif /* defined(__TowerDefense__Configuration__) */
