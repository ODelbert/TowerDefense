#ifndef PListReader_h
#define PListReader_h

#include "CommonDef.h"
#include "cocos2d.h"

class EnemyPlist
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

class AnimationPlist
{
    
};

class WavePlist
{
    
};

class PListReader : public cocos2d::Node
{
public:
    static PListReader* getInstance();
    static void destroy();

    EnemyPlist* createEnemyPlist(const std::string &plistname);

    AnimationPlist* createAnimationPlist(const std::string &plistname);

    WavePlist* createWavePlist(const std::string &plistname);

private:
    static PListReader* s_instance;
};


#endif /* PListReader_h */
