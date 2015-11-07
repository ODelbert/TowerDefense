#ifndef PListReader_h
#define PListReader_h

#include "CommonDef.h"
#include "cocos2d.h"
#include "uthash.h"
#include <vector>



class TableIndexer : public cocos2d::Ref
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
        int id;
        std::vector<TableData> m_chains;
    };
#define HASH(id, type) ((id) << 16 | (type))
public:
    void put(int id, int type, std::string str);
    void remove(int id, int type);
    std::string find(int id, int type);
    void show();
private:
    std::vector<TableHeader> m_table;
};

class EnemyPlist : public cocos2d::Ref
{
public:
    struct EnemySpriteInfo
    {
        std::string   spriteName;
        cocos2d::Size spriteSize;
        bool          spriteTrimmed;
        cocos2d::Rect spriteColorRect;
        cocos2d::Vec2 spriteOffet;
        cocos2d::Rect textureRect;
        bool          textureRotated;
        cocos2d::Size spriteSourceSize;
    };

    EnemyPlist();

    void addInfo(const EnemySpriteInfo &info);

    const EnemySpriteInfo& getInfo(const std::string &name);

private:
    std::map<std::string, EnemySpriteInfo> m_infos;
};

class AnimationPlist : public cocos2d::Ref
{
public:
    struct AnimationSpriteInfo
    {
        std::string name;
        std::string prefix;
        int fromIndex;
        int toIndex;
    };
};

class WavePlist : public cocos2d::Ref
{
public:
};

struct EnemyInfo
{
    char name[24];
    int dmgMin;
    int dmgMax;
    int life;
    int weapon;
    int armor;
    int resist;
    int speed;
    int food;
    int flyable;
};

class PListReader : public cocos2d::Ref
{
public:
    static PListReader* getInstance();
    static void destroy();

    EnemyPlist* createEnemyPlist(const std::string &plistname);

    AnimationPlist* createAnimationPlist(const std::string &plistname);

    WavePlist* createWavePlist(const std::string &plistname);
    
    void createAnimationWithPlist(const std::string &name);
    std::vector<std::vector<std::vector<cocos2d::Vec2> > > readPathPlist(int level);
    EnemyInfo readEnemyInfoPlist(const std::string& name);
    
    void createEnemyAnimationTableIndexer();

private:
    PListReader();
    virtual ~PListReader();
    
private:
    static PListReader* s_instance;
    
private:
    TableIndexer* m_table;
};


#endif /* PListReader_h */
