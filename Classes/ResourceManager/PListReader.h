#ifndef PListReader_h
#define PListReader_h

#include "CommonDef.h"
#include "cocos2d.h"
#include <vector>
#include "Enemy/Enemy.h"

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

class PListReader : public cocos2d::Node
{
public:
    static PListReader* getInstance();
    static void destroy();

    EnemyPlist* createEnemyPlist(const std::string &plistname);

    AnimationPlist* createAnimationPlist(const std::string &plistname);

    WavePlist* createWavePlist(const std::string &plistname);
    
    void createAnimationWithPlist(const std::string &name);
    std::vector<std::vector<std::vector<cocos2d::Vec2> > > readPathPlist(int level);
    
    void createEnemyAnimationTableIndexer();
    void saveImageFromPlist(const std::string &plist);
    
#ifdef TD_DEBUG
    void generateEnemyPlist();
    void generateTowerPlist();
#endif
    
private:
    static PListReader* s_instance;
};


#endif /* PListReader_h */
