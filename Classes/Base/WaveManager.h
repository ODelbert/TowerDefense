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
#include "CommonDef.h"
#include "Base/Singleton.h"
USING_NS_CC;

struct SpawnInfo
{
    char id[24];
    uint maxSame;
    uint max;
    uint interval;
    uint intervalNext;
    uint path;
};

class WaveInfo : public Ref
{
public:
    CC_SYNTHESIZE(uint, m_waveInterval, WaveInterval)
    CC_SYNTHESIZE(uint, m_pathIndex, PathIndex)
    
    std::vector<SpawnInfo> spwans() { return m_spwans; }
    void addSpawn(const SpawnInfo& s) { m_spwans.push_back(s); }
private:
    std::vector<SpawnInfo> m_spwans;
};

class WaveManager : public Ref, public Singleton<WaveManager>
{
public:
    void start();
    void initialize(int level, int difficulty);
    std::vector<Vec2> getPath(int path, int subPath);
    int getPathCount();

    CC_SYNTHESIZE(uint, m_cash, Cash)
   
private:
    void nextEnemy(float dt);
    void nextWave(int interval);

private:
    std::vector<WaveInfo> m_waves;
    std::vector<std::vector<std::vector<Vec2> > > m_paths;
    int m_waveIndex;
    int m_spawnIndex;
    Sprite* m_runningEnemy;
    Scheduler* m_waveScheduler;
};

#define WM WaveManager::getInstance()

#endif /* defined(__TowerDefense__WaveManager__) */
