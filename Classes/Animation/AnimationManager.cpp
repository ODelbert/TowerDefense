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

using namespace tinyxml2;

AnimationManager::AnimationManager()
{}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::initialize()
{
    std::string path = FileUtils::getInstance()->getWritablePath();
    std::string file = "animation.xml";
    path += file;
    XMLDocument *pDoc = new XMLDocument;
    XMLError errorId = pDoc->LoadFile(path.c_str());

    if (errorId != 0) {
        return;
    }
    
    XMLElement *rootEle = pDoc->RootElement();
    for (XMLElement* animation = rootEle->FirstChildElement(); animation; animation = animation->NextSiblingElement()) {
        int toIndex = -1;
        int fromIndex = -1;
        std::string descript;
        std::string prefix;
        for (XMLElement* child = animation->FirstChildElement(); child; child = child->NextSiblingElement()) {
            if (0 == strcmp(child->Name(), "fromIndex")) {
                fromIndex = atoi(child->GetText());
            }
            else if (0 == strcmp(child->Name(), "toIndex")){
                toIndex = atoi(child->GetText());
            }
            else if (0 == strcmp(child->Name(), "prefix")){

                prefix = child->GetText();
            }
            else if (0 == strcmp(child->Name(), "descript")){
                descript = child->GetText();
            }
            else {
                
            }
        }
        
        log("desc %s prefix %s  fromInex %d toIndex %d", descript.c_str(), prefix.c_str(), fromIndex, toIndex);
        addAnimation(descript, prefix, toIndex, fromIndex);
    }
}

Animation* AnimationManager::getAnimation(const std::string& name)
{
    return AnimationCache::getInstance()->getAnimation(name);
}

void AnimationManager::addAnimation(const std::string& descript, const std::string& prefix, int toIndex, int fromIndex)
{
    if (fromIndex < 0 || toIndex < 0 || fromIndex > toIndex) return;
    Vector<SpriteFrame*> animFrames;
    for (int i = fromIndex; i <= toIndex; ++i) {
        std::string format = prefix;
        if (100 > i) {
            format += "_00%02d.png";
        }
        else {
            format += "_0%03d.png";
        }

        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat(format.c_str(),i)->getCString());
        if (frame) {
            animFrames.pushBack(frame);
        }
    }

    if (animFrames.empty()) {
        CCLOG("AnimationManager::addAnimation animation %s, frame not load!", descript.c_str());
        return;
    }

    // FIXME::tune parameter
    float animateRate = 0.002f * animFrames.size() < 0.05f ? 0.05f : 0.002f * animFrames.size();
    AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(animFrames, animateRate) , descript);
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


