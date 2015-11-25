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
using namespace tinyxml2;


SINGLETON_IMPL(WaveManager);

void WaveManager::loadWave(int level, int difficulty)
{
    //ValueMap root = FileUtils::getInstance()->getValueMapFromFile("level1_waves_campaign.xml");
    

    std::string path = FileUtils::getInstance()->getWritablePath();
    std::string file = "level1_waves_campaign.xml";
    path += file;
    CCLOG("path = %s", path.c_str());
    XMLDocument *pDoc = new XMLDocument();
    XMLError errorId = pDoc->LoadFile("level1_waves_campaign.xml");
    
    if (errorId != 0) {
        //xml格式错误
        return;
    }
    
    XMLElement *rootEle = pDoc->RootElement();
    
    //获取第一个节点属性
    const XMLAttribute *attribute = rootEle->FirstAttribute();
    //打印节点属性名和值
    log("attribute_name = %s,attribute_value = %s", attribute->Name(), attribute->Value());

    XMLElement *wavesEle = rootEle->FirstChildElement("waves");
    XMLElement *cashEle = wavesEle->FirstChildElement("cash");
    
    
    if (cashEle) {
        log("keyEle Text= %s", cashEle->GetText());
    }
    
    XMLElement *waveEle = wavesEle->FirstChildElement("wave");
    
    while (waveEle) {
        XMLElement *ele = waveEle->FirstChildElement("interval");
        while (ele) {
            log("value %s text %s", ele->Value(), ele->GetText());
            if (0 == strcmp(ele->Value(), "interval")) {
                log("interval %s", ele->GetText());
            }
            else if (0 == strcmp(ele->Value(), "path_index")) {
                log("path_index %s", ele->GetText());
            }
            else if (0 == strcmp(ele->Value(), "spawns")) {
                XMLElement* spawn = ele->FirstChildElement("spawn");
                while (spawn) {
                    XMLElement *ee = spawn->FirstChildElement("creep");
                    while (ee) {
                        if (0 == strcmp(ee->Value(), "creep")) {
                            log("creep = %s", ee->GetText());
                        }
                        else if (0 == strcmp(ee->Value(), "max_same")) {
                            log("max_same = %s", ee->GetText());
                        }
                        else if (0 == strcmp(ee->Value(), "max")) {
                            log("max = %s", ee->GetText());
                        }
                        else if (0 == strcmp(ee->Value(), "interval")) {
                            log("interval = %s", ee->GetText());
                        }
                        else if (0 == strcmp(ee->Value(), "interval_next")) {
                            log("interval_next = %s", ee->GetText());
                        }
                        else {

                        }
                        
                        ee = ee->NextSiblingElement();
                    }
                    
                    spawn = spawn->NextSiblingElement();
                }
            }
            else {
                
            }
            
            ele = ele->NextSiblingElement();
        }
        
        
        
//        XMLElement *intervalEle = waveEle->FirstChildElement();
//        log("interval %s", intervalEle->GetText());
//        XMLElement *pathIndexEle = intervalEle->NextSiblingElement();
//        log("path %s", pathIndexEle->GetText());
//        
//        XMLAttribute* aaaa = waveEle->    ->FindAttribute("interval");
//        log("aaa = %s", aaaa->Value());
//        int a  = wavesEle->IntAttribute("interval");
//        int b= -1;
//        waveEle->QueryIntAttribute("interval", &b);
//        XMLElement *intervalEle = wavesEle->FirstChildElement("interval");
//        log("interval = %s", intervalEle->GetText());
//        XMLElement *pathIndexEle = wavesEle->FirstChildElement("path_index");
//        log("path index = %s", pathIndexEle->GetText());
//        waveEle = waveEle->NextSiblingElement();
        
        waveEle = waveEle->NextSiblingElement();
    }
    
    
    
//    XMLElement *arrayEle = keyEle->NextSiblingElement();
//    XMLElement *childEle = arrayEle->FirstChildElement();
//    while ( childEle ) {
//        log("childEle Text= %s", childEle->GetText());
//        childEle = childEle->NextSiblingElement();
//    }
    
    delete pDoc;

//    
//    auto doc =new tinyxml2::XMLDocument();
//    doc->Parse(FileUtils::getInstance()->getStringFromFile("level1_waves_campaign.xml.xml").c_str());
//    
//    auto root=doc->RootElement();
//    for (auto e=root->FirstChildElement(); e; e=e->NextSiblingElement()) {
//        std::string str;
//        for (auto attr=e->FirstAttribute(); attr; attr=attr->Next()) {
//            str+=attr->Name();
//            str+=":";
//            str+=attr->Value();
//            str+=",";
//        }
//        log("%s",str.c_str());
//    }
//    
        int a = 1;

}