//
//  AnimationManager.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/7.
//
//

#include "AnimationManager.h"
#include "CommonDef.h"

AnimationManager::AnimationManager()
{}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::addAnimation(uint key, const std::string& name)
{
    m_key2Animate[key] = name;
}

void AnimationManager::removeAnimation(uint key)
{
    m_key2Animate.erase(key);
}

Animation* AnimationManager::getAnimation(uint hash)
{
    std::map<uint, std::string>::const_iterator iter = m_key2Animate.find(hash);
    if (iter != m_key2Animate.end()) {
        std::string name = iter->second;
        return AnimationCache::getInstance()->getAnimation(name);
    }

    return nullptr;
}

void AnimationManager::runAction(Sprite* target, uint hash, bool repeatForever)
{
    std::map<uint, std::string>::const_iterator iter = m_key2Animate.find(hash);
    if (iter != m_key2Animate.end()) {
        std::string name = iter->second;
        //
        //    std::string name = m_key2Animate[key];
        //    if (!name.empty()) {
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
    else {
        log("animation with hash %x, not found, do you have input the right value???", hash);
    }
}

void AnimationManager::runAction(Sprite* target, int type, int key, int action, bool repeatForever)
{
    runAction(target, ANIMATION_HASH(type, key, action), repeatForever);
}


