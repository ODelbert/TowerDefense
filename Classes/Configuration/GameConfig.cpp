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


SINGLETON_IMPL(GameConfig);

void GameConfig::initialize()
{

}

static TowerInfo getTowerInfo(TowerID id, TowerLevel level)
{
    for (int i = 0; i < TD_LEN(s_enemiesInfo); ++i) {
        if (s_towersInfo[i].id == id && s_towersInfo[i].level == level)
            return s_towersInfo[i];
    }

    return TowerInfo();
}

static EnemyInfo getEnemyInfo(EnemyID id)
{
    for (int i = 0; i < TD_LEN(s_enemiesInfo); ++i) {
        if (s_enemiesInfo[i].id == id)
            return s_enemiesInfo[i];
    }

    return EnemyInfo();
}
