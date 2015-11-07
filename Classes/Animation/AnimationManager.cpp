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


void TableIndexer::put(int key, int type, std::string str)
{
    for (int i = 0; i < m_table.size(); ++i) {
        if (key == m_table[i].key) {
            m_table[i].m_chains.push_back(TableData(type, str));
            return;
        }
    }
    
    TableHeader head;
    head.key = key;
    head.m_chains.push_back(TableData(type, str));
    m_table.push_back(head);
}

void TableIndexer::remove(int key, int type)
{
    std::vector<TableHeader>::iterator iter = m_table.begin();
    for (; iter != m_table.end(); ++iter) {
        if (key == iter->key) {
            m_table.erase(iter);
        }
    }
}

std::string TableIndexer::find(int key, int type)
{
    for (int i = 0; i < m_table.size(); ++i) {
        if (key == m_table[i].key) {
            for (int j = 0; j < m_table[i].m_chains.size(); ++j) {
                if (type == m_table[i].m_chains[j].type) {
                    return m_table[i].m_chains[j].name;
                }
            }
        }
    }
    
    return std::string();
}

std::vector<unsigned int> TableIndexer::find(int key)
{
    std::vector<unsigned int> hashes;
    for (int i = 0; i < m_table.size(); ++i) {
        if (key == m_table[i].key) {
            for (int j = 0; j < m_table[i].m_chains.size(); ++j) {
                hashes.push_back(HASH(key, m_table[i].m_chains[j].type));
            }
        }
    }
    
    return hashes;
}

void TableIndexer::show()
{
    for (int i = 0; i < m_table.size(); ++i) {
        for (int j = 0; j < m_table[i].m_chains.size(); ++j) {
            CCLOG("key %d type %d name %s", m_table[i].key, m_table[i].m_chains[j].type, m_table[i].m_chains[j].name.c_str());
        }
    }
}

AnimationManager::AnimationManager()
    : m_table(new TableIndexer)
{}

AnimationManager::~AnimationManager()
{
    if (m_table) {
        delete m_table;
        m_table = NULL;
    }
}

void AnimationManager::runAction(Sprite* target, int key, bool repeatForever)
{
    int type = 1; // tmp
    runAction(target, key, type, repeatForever);
}

void AnimationManager::runAction(Sprite* target, int key, int type, bool repeatForever)
{
    if (!target) {
        return;
    }
    std::vector<unsigned int> hashes = m_table->find(key);
    for (int i = 0; i < hashes.size(); ++i) {
        target->stopActionByTag(hashes[i]);
    }
    
    std::string actionName = m_table->find(key, type);
    m_table->show();
    CCLOG("actionName = %s", actionName.c_str());
    if (actionName.empty()) {
        return;
    }
    
    auto animation = AnimationCache::getInstance()->getAnimation(actionName);
    if (!animation) {
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
}

void AnimationManager::addAnimationIndex(int key, int actionType, const std::string& name)
{
    if (m_table) {
        m_table->put(key, actionType, name);
    }
}

void AnimationManager::removeAnimationIndex(int key, int actionType)
{
    if (m_table) {
        m_table->remove(key, actionType);
    }
}

std::string AnimationManager::findAnimation(int key, int actionType)
{
    if (m_table) {
        return m_table->find(key, actionType);
    }
}
void AnimationManager::showTable()
{
    if (m_table) {
        m_table->show();
    }
}

