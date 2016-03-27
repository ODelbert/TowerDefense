//
//  AnimationManager.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/7.
//
//

#include "AnimationManager.h"
#include "CommonDef.h"
#include "tinyxml2/tinyxml2.h"

AnimationManager::AnimationManager()
{}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::initialize()
{
//    std::string path = FileUtils::getInstance()->getWritablePath();
//    std::string file = "animation.xml";
//    path += file;
//    tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument;
//    XMLError errorId = pDoc->LoadFile(path.c_str());
//    
//    if (errorId != 0) {
//        return;
//    }
//    
//    XMLElement *rootEle = pDoc->RootElement();
//    for (XMLElement* chd = rootEle->FirstChildElement(); chd; chd = chd->NextSiblingElement()) {
//        if (0 == strcmp(chd->Name(), "animations")){
//            XMLElement *ele = chd->FirstChildElement("animation");
//            while (ele) {
//                std::string prefix = ele->Attribute(const char *name)
//                ele = ele->NextSiblingElement();
//            }
//            
//            if (0 == strcmp(chd->Name(), "cash")) {
//                m_cash = atoi(chd->GetText());
//            }
//            else if (0 == strcmp(chd->Name(), "wave")){
//                WaveInfo waveInfo;
//                XMLElement *ele = chd->FirstChildElement("interval");
//                while (ele) {
//                    if (0 == strcmp(ele->Value(), "interval")) {
//                        waveInfo.setWaveInterval(atoi(ele->GetText()));
//                    }
//                    else if (0 == strcmp(ele->Value(), "path_index")) {
//                        waveInfo.setPathIndex(atoi(ele->GetText()));
//                    }
//                    else if (0 == strcmp(ele->Value(), "spawns")) {
//                        
//                        XMLElement* spawn = ele->FirstChildElement("spawn");
//                        while (spawn) {
//                            SpawnInfo si;
//                            XMLElement *ee = spawn->FirstChildElement("creep");
//                            while (ee) {
//                                if (0 == strcmp(ee->Value(), "creep")) {
//                                    strncpy(si.id, ee->GetText(), 24);
//                                }
//                                else if (0 == strcmp(ee->Value(), "max_same")) {
//                                    si.maxSame = atoi(ee->GetText());
//                                }
//                                else if (0 == strcmp(ee->Value(), "max")) {
//                                    char maxStr[10];
//                                    strncpy(maxStr, ee->GetText(), 10);
//                                    si.max = atoi(maxStr);
//                                }
//                                else if (0 == strcmp(ee->Value(), "interval")) {
//                                    si.interval = atoi(ee->GetText());
//                                }
//                                else if (0 == strcmp(ee->Value(), "interval_next")) {
//                                    si.intervalNext = atoi(ee->GetText());
//                                }
//                                else if (0 == strcmp(ee->Value(), "path")) {
//                                    si.path = atoi(ee->GetText());
//                                }
//                                else {
//                                    
//                                }
//                                ee = ee->NextSiblingElement();
//                            }
//                            
//                            if (si.max >= 2 && si.interval > 0) {
//                                for (int i  = 0; i < si.max; ++i) {
//                                    waveInfo.addSpawn(si);
//                                }
//                            }
//                            waveInfo.addSpawn(si);
//                            spawn = spawn->NextSiblingElement();
//                        }
//                    }
//                    else {
//                        
//                    }
//                    
//                    ele = ele->NextSiblingElement();

}

void AnimationManager::addAnimation(const std::string& name, const std::string& prefix, int toIndex, int formIndex)
{
    
}

void AnimationManager::removeAnimation(const std::string& name)
{
    
}

void AnimationManager::runAction(Sprite* target, const std::string& name, bool repeatForever)
{
    auto animation = AnimationCache::getInstance()->getAnimation(name);
    if (animation) {
        target->stopAllActions();
        Action* action;
        if (repeatForever) {
            action = RepeatForever::create(Animate::create(animation));
        }
        else {
            action = Animate::create(animation);
        }
        
        target->runAction(action);
    }
    else {
        log("WARN:animation with name %s not find!!!, check the frame is loaded?", name.c_str());
    }
}


