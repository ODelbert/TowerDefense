//
//  Configuration.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/15.
//
//

#include "CommonDef.h"
#include "GameConfig.h"
#include "GameData.h"
#include "ResourceManager/PListReader.h"

GameConfig::GameConfig()
{
    
}

void GameConfig::initialize()
{

}

int GameConfig::upgradeGold(TowerID id, TowerLevel lv)
{
    return getTowerInfo(id, lv).upgradeGold;
}

TowerInfo GameConfig::getTowerInfo(TowerID id, TowerLevel level)
{
    for (int i = 0; i < TD_LEN(s_enemiesInfo); ++i) {
        if (s_towersInfo[i].id == id && s_towersInfo[i].level == level)
            return s_towersInfo[i];
    }

    return TowerInfo();
}

EnemyInfo GameConfig::getEnemyInfo(EnemyID id)
{
    for (int i = 0; i < TD_LEN(s_enemiesInfo); ++i) {
        if (s_enemiesInfo[i].id == id)
            return s_enemiesInfo[i];
    }

    return EnemyInfo();
}
