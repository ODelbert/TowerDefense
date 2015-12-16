//
//  AnimationManager.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/7.
//
//

#include "AnimationManager.h"
#include "CommonDef.h"

SINGLETON_IMPL(AnimationManager)

AnimationManager::AnimationManager()
{}

AnimationManager::~AnimationManager()
{
}


void AnimationManager::runAction(Sprite* target, int key, bool repeatForever)
{
//    int type = 1; // tmp
//    runAction(target, key, type, repeatForever);
}

void AnimationManager::runAction(Sprite* target, int key, int type, bool repeatForever)
{
    /*
    if (!target) {
        return;
    }
    
    std::vector<unsigned int> hashes = m_table->find(key);
    for (int i = 0; i < hashes.size(); ++i) {
        target->stopActionByTag(hashes[i]);
    }
    
    std::string actionName = m_table->find(key, type);
    if (actionName.empty()) {
        CCLOG("AnimationManager::runAction cannot find animation by key %d type %d", key, type);
        return;
    }
    
    auto animation = AnimationCache::getInstance()->getAnimation(actionName);
    if (!animation) {
        CCLOG("AnimationManager::runAction cannot find anmation with name %s", actionName.c_str());
        return;
    }
    
    Action* action;
    if (repeatForever) {
        action = RepeatForever::create(Animate::create(animation));
    }
    else {
        action = Animate::create(animation);
    }

    action->setTag(HASH(key, type));
    target->runAction(action);
     */
}


