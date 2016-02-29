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
#include "Base/Event.h"

using namespace tinyxml2;

SINGLETON_IMPL(WaveManager);

struct EnemyName2ID
{
    char name[64];
    int id;
};

static EnemyName2ID s_name2Id[] = 
{
    { "ElvesEnemyArachnomancer", EnemyID_Arachnomancer },
    { "ElvesEnemyBandersnatch", EnemyID_Bandersnatch }, 
    { "ElvesEnemyBloodServant", EnemyID_BloodServant },
    { "ElvesEnemyBloodsydianWarlock", EnemyID_BloodsydianWarlock },
    { "ElvesEnemyBoomshrooms", 10000 }, 
    { "ElvesEnemyDarkSpitters", EnemyID_Dark_Spitters },
    { "ElvesEnemyDrider", EnemyID_Drider },
    { "ElvesEnemyEttin", EnemyID_Ettin },
    { "ElvesEnemyGloomy", EnemyID_Gloomy },
    { "ElvesEnemyGnollBlighter", EnemyID_Gnoll_Blighter },
    { "ElvesEnemyGnollBloodsydian", EnemyID_BloodsydianGnoll },
    { "ElvesEnemyGnollBurner", EnemyID_Gnoll_Burner },
    { "ElvesEnemyGnollGnawer", EnemyID_Gnoll_Gnawer }, 
    { "ElvesEnemyGnollReaver", EnemyID_Gnoll_Reaver },
    { "ElvesEnemyGrimDevourers" , EnemyID_Grim_Devourers},
    { "ElvesEnemyHyena", EnemyID_Hyena },
    { "ElvesEnemyMantaRay", EnemyID_Mantaray }, 
    { "ElvesEnemyMountedAvenger", 10000 },
    { "ElvesEnemyMunchshrooms", 10000}, 
    { "ElvesEnemyOgreMagi", EnemyID_Ogre_Mage },
    { "ElvesEnemyOgreMagiCustodyEttin", 999999 },
    { "ElvesEnemyOgreMagiCustodyGnollGnawer", 999999 },
    { "ElvesEnemyOgreMagiCustodyWarlock", 999999 }, 
    { "ElvesEnemyPerython", EnemyID_Perython }, 
    { "ElvesEnemyPerythonGnollGnawer", 99999999 },
    { "ElvesEnemyPerythonRockthrower", 99999999 },
    //  { "ElvesEnemyRabbit", EnemyID_Rabbit },
    { "ElvesEnemyRazorboar", EnemyID_Razorboar },
    { "ElvesEnemyRedcap", EnemyID_Redcap },
    { "ElvesEnemySatyrCutthroat", EnemyID_Satyr },
    { "ElvesEnemySatyrHoplite", EnemyID_Satyr },
    { "ElvesEnemyScreecherBat", EnemyID_Screecher_Bat }, 
    { "ElvesEnemyShadowChampion", EnemyID_Shadow_Champion }, 
    { "ElvesEnemyShadowsSpawns", EnemyID_Shadow_Spawn }, 
    { "ElvesEnemyShroomBreeder", 10000 }, 
    { "ElvesEnemySpiderArachnomancer", EnemyID_Arachnomancer_Spider },
    { "ElvesEnemySpiderSonOfMactans", EnemyID_Son_Of_Mactans },
    { "ElvesEnemySwordSpider", EnemyID_Sword_Spider }, 
    { "ElvesEnemyTwilightAvenger", EnemyID_Twilight_Avenger}, 
    { "ElvesEnemyTwilightElfHarasser", EnemyID_Harraser }, 
    { "ElvesEnemyTwilightEvoker", EnemyID_Twilight_Evoker},
    { "ElvesEnemyTwilightGolem", EnemyID_Gollem},
    { "ElvesEnemyTwilightHeretic", EnemyID_Twilight_Heretic },
    { "ElvesEnemyTwilightScourger", EnemyID_Scourger }, 
    { "ElvesEnemyWebspittingSpider", EnemyID_WebspitterSpider }, 
    { "EnemyBouncer", 10000 }, 
    { "EnemyDesertRaider", 10000 }
};

static EnemyID name2Id(const char* str)
{
    for (int i = 0; i < sizeof(s_name2Id)/sizeof(s_name2Id[0]); ++i) {
        if (0 == strncmp(str, s_name2Id[i].name, 64)) {
            return static_cast<EnemyID>(s_name2Id[i].id);
        }
    }
    
    return EnemyID_Invalid;
}

void WaveManager::initialize(int level, int difficulty)
{
    // FIXME:: 难度支持
    std::string path = FileUtils::getInstance()->getWritablePath();
    std::string file = "level1_waves_campaign.xml";
    path += file;
    tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument;
    XMLError errorId = pDoc->LoadFile(path.c_str());
    
    if (errorId != 0) {
         return;
    }
    
    XMLElement *rootEle = pDoc->RootElement();
    for (XMLElement* chd = rootEle->FirstChildElement(); chd; chd = chd->NextSiblingElement()) {
        if (0 == strcmp(chd->Name(), "cash")) {
            m_cash = atoi(chd->GetText());
        }
        else if (0 == strcmp(chd->Name(), "wave")){
            WaveInfo waveInfo;
            XMLElement *ele = chd->FirstChildElement("interval");
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
                            else if (0 == strcmp(ee->Value(), "path")) {
                                si.path = atoi(ee->GetText());
                            }
                            else {
                                
                            }
                            ee = ee->NextSiblingElement();
                        }
                        
                        if (si.max >= 2 && si.interval > 0) {
                            for (int i  = 0; i < si.max; ++i) {
                                waveInfo.addSpawn(si);
                            }
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
        }
    }
    
    delete pDoc;

    m_paths = PListReader::getInstance()->readPathPlist(level);
}

void WaveManager::start()
{
    auto scheduleMain = Director::getInstance()->getScheduler();
    auto scheduleWave = new Scheduler();
    scheduleMain->scheduleUpdate(scheduleWave, 0, false);
    scheduleWave->schedule(schedule_selector(WaveManager::nextEnemy), this, 1.0f, CC_REPEAT_FOREVER, 0.0f, false);
    m_waveIndex = 0;
    m_spawnIndex = 0;
}

// FIXME:: 定时触发
void WaveManager::nextEnemy(float dt)
{
//    if (xxx)　return;
    if (m_waveIndex >= m_waves.size()) {
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(WaveManager::nextEnemy), this);
        return;
    }
    
    log("=========%d=============push enemy with name [%s] to battle, path %d, interval %d intervalNext %d, max %d, max_same %d", m_waveIndex,
        m_waves[m_waveIndex].spwans()[m_spawnIndex].id,
        m_waves[m_waveIndex].spwans()[m_spawnIndex].path,
        m_waves[m_waveIndex].spwans()[m_spawnIndex].interval,
        m_waves[m_waveIndex].spwans()[m_spawnIndex].intervalNext,
        m_waves[m_waveIndex].spwans()[m_spawnIndex].max,
        m_waves[m_waveIndex].spwans()[m_spawnIndex].maxSame);

    WaveEvent event;
    event.setWaveData(name2Id(m_waves[m_waveIndex].spwans()[m_spawnIndex].id), m_waves[m_waveIndex].getPathIndex(), m_waves[m_waveIndex].spwans()[m_spawnIndex].path);

    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    if (m_spawnIndex < m_waves[m_waveIndex].spwans().size() - 1) {
        ++m_spawnIndex;
    }
    else {
        m_spawnIndex = 0;
        ++m_waveIndex;
    }
}

std::vector<Vec2> WaveManager::getPath(int path, int subPath)
{
    if (path >= m_paths.size() || subPath >= m_paths[path].size()) {
        return std::vector<Vec2>();
    }
    
    return m_paths[path][subPath];
}

int WaveManager::getPathCount()
{
    return m_paths.size();
}