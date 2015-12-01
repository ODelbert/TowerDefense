//
//  WaveManager.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/22.
//
//

#include "WaveManager.h"
#include "CommonDef.h"
#include "tinyxml2/tinyxml2.h"
#include "PListReader.h"
#include "Enemy/Enemy.h"

using namespace tinyxml2;

SINGLETON_IMPL(WaveManager);

void WaveManager::initialize(int level, int difficulty)
{
    //ValueMap root = FileUtils::getInstance()->getValueMapFromFile("level1_waves_campaign.xml");
    std::string path = FileUtils::getInstance()->getWritablePath();
    std::string file = "level1_waves_campaign.xml";
    path += file;
    tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument;
    XMLError errorId = pDoc->LoadFile("level1_waves_campaign.xml");
    
    if (errorId != 0) {
         return;
    }
    
    XMLElement *rootEle = pDoc->RootElement();
    const XMLAttribute *attribute = rootEle->FirstAttribute();
    XMLElement *wavesEle = rootEle->FirstChildElement("waves");
    XMLElement *cashEle = wavesEle->FirstChildElement("cash");
    if (cashEle) {
        m_cash = atoi(cashEle->GetText());
    }
    
    XMLElement *waveEle = wavesEle->FirstChildElement("wave");
    while (waveEle) {
        WaveInfo waveInfo;
        XMLElement *ele = waveEle->FirstChildElement("interval");
        while (ele) {
            if (0 == strcmp(ele->Value(), "interval")) {
                waveInfo.setWaveInterval(atoi(ele->GetText()));
            }
            else if (0 == strcmp(ele->Value(), "path_index")) {
                waveInfo.setPathIndex(atoi(ele->GetText()));
            }
            else if (0 == strcmp(ele->Value(), "spawns")) {
                
                XMLElement* spawn = ele->FirstChildElement("spawn");
                while (spawn) {
                    SpawnInfo si;
                    XMLElement *ee = spawn->FirstChildElement("creep");
                    while (ee) {
                        if (0 == strcmp(ee->Value(), "creep")) {
                            strncpy(si.id, ee->GetText(), 24);
                        }
                        else if (0 == strcmp(ee->Value(), "max_same")) {
                            si.maxSame = atoi(ee->GetText());
                        }
                        else if (0 == strcmp(ee->Value(), "max")) {
                            char maxStr[10];
                            strncpy(maxStr, ee->GetText(), 10);
                            si.max = atoi(maxStr);
                        }
                        else if (0 == strcmp(ee->Value(), "interval")) {
                            si.interval = atoi(ee->GetText());
                        }
                        else if (0 == strcmp(ee->Value(), "interval_next")) {
                            si.intervalNext = atoi(ee->GetText());
                        }
                        else {

                        }
                        
                        ee = ee->NextSiblingElement();
                    }
                    
                    waveInfo.addSpawn(si);
                    spawn = spawn->NextSiblingElement();
                }
            }
            else {
                
            }
            
            ele = ele->NextSiblingElement();
        }

        m_waves.push_back(waveInfo);
        waveEle = waveEle->NextSiblingElement();
    }

    delete pDoc;
    
    
    m_paths = PListReader::getInstance()->readPathPlist(level);
}

void WaveManager::start()
{
    auto scheduleMain = Director::getInstance()->getScheduler();
    auto scheduleWave = new Scheduler();
    scheduleMain->scheduleUpdate(scheduleWave, 0, false);
    scheduleWave->schedule(schedule_selector(WaveManager::nextEnemy), this, 0.0f, CC_REPEAT_FOREVER, 0.0f, false);
    m_waveIndex = 0;
    m_spawnIndex = 0;
    
    
}

void WaveManager::nextEnemy(float dt)
{
    // TEST
    return;
    m_runningEnemy = Sprite::createWithSpriteFrameName("redcap_0001.png");
    return;
    if (m_waveIndex >= m_waves.size()) {
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WaveManager::nextEnemy), this);
        return;
    }

    if (m_spawnIndex < m_waves[m_waveIndex].spwans().size() - 1) {
        ++m_spawnIndex;
    }
    else {
        m_spawnIndex = 0;
        ++m_waveIndex;
    }
    
    if (m_waveIndex == m_waves.size()) return;
    log("=========%d=============push enemy with name [%s] to battle, path %d, next %d, max %d, max_same %d", m_waveIndex,
        m_waves[m_waveIndex].spwans()[m_spawnIndex].id,
        m_waves[m_waveIndex].spwans()[m_spawnIndex].path,
        m_waves[m_waveIndex].spwans()[m_spawnIndex].intervalNext,
        m_waves[m_waveIndex].spwans()[m_spawnIndex].max,
        m_waves[m_waveIndex].spwans()[m_spawnIndex].maxSame);
}

