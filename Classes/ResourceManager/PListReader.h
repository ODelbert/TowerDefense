#ifndef PListReader_h
#define PListReader_h

#include "CommonDef.h"
#include "cocos2d.h"
#include <vector>
#include <string>
#include "Enemy/Enemy.h"
#include "Base/Singleton.h"

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

class PListReader : public cocos2d::Node, public Singleton<PListReader>
{
public:
    void generateAnimationPlist(const std::string &plistname, Dictionary* animationDict, Dictionary* includePlists);
    Dictionary* createAnimationPlist(std::string prefix, int from, int to);
    
    void createAnimationWithPlist(const std::string &name);
    std::vector<std::vector<std::vector<cocos2d::Vec2> > > readPathPlist(int level);
    
    void extractAnimationFromResource();
    bool saveImages();
    void getCompressedImgs();
private:
    void saveImageFromPlist(const std::string &plist);
    
    
private:
    static PListReader* s_instance;
    std::vector<std::string> m_plistFiles;
    std::function<void (RenderTexture*, const std::string&)> m_saveFileCallback;
};


#endif /* PListReader_h */
