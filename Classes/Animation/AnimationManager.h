//
//  AnimationManager.h
//  TowerDefense
//
//  Created by jowu on 15/11/7.
//
//

#ifndef __TowerDefense__AnimationManager__
#define __TowerDefense__AnimationManager__

#include <stdio.h>
#include "PListReader.h"
#include "cocos2d.h"

USING_NS_CC;

class TableIndexer : public Ref
{
    class TableData
    {
    public:
        TableData(int type, std::string name):type(type), name(name) {}
        int type;
        
        std::string name;
    };
    
    class TableHeader
    {
        friend class TableIndexer;
        int key;
        std::vector<TableData> m_chains;
    };
#define HASH(key, type) ((key) << 16 | (type))
public:
    void put(int key, int type, std::string str);
    void remove(int key, int type);
    std::string find(int key, int type);
    std::vector<unsigned int> find(int key);
    void show();
private:
    std::vector<TableHeader> m_table;
};

class AnimationManager : public Ref
{
    friend class PListReader;
public:
    static AnimationManager* getInstance();
    static void destroy();
    
    void runAction(Sprite* target, int key, bool repeatForever = true);
    void runAction(Sprite* target, int key, int type, bool repeatForever = true);
    void showTable();
private:
    void addAnimationIndex(int key, int actionType, const std::string& name);
    void removeAnimationIndex(int key, int actionType);
    std::string findAnimation(int key, int actionType);

    
private:
    static AnimationManager* s_instance;
    
private:
    AnimationManager();
    virtual ~AnimationManager();
    
private:
    TableIndexer* m_table;
};

#endif /* defined(__TowerDefense__AnimationManager__) */
