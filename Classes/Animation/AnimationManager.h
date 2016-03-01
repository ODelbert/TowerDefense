//
//  AnimationManager.h
//  TowerDefense
//
//  Created by jowu on 15/11/7.
//
//

#ifndef __TowerDefense__AnimationManager__
#define __TowerDefense__AnimationManager__

#include "cocos2d.h"
#include "PListReader.h"
#include "Base/Singleton.h"

USING_NS_CC;

#define ANIMATION_HASH(type, key, act) (((type) << 20) | ((key) << 12) | (act))
#define ANIMATION_TYPE(hash) (((hash) & 0x00F00000) >> 20)
#define ANIMATION_KEY(hash) (((hash) & 0x000FF000) >> 12)
#define ANIMATION_ACTION(hash) ((hash) & 0x00000FFF)

enum AnimationType
{
    AnimationType_Common            = 0,
    AnimationType_Manual            = 1,
    AnimationType_Enemy             = 2,
    AnimationType_Tower             = 3,
    AnimationType_Ally              = 4,
    AnimationType_Hero              = 5,
    AnimationType_Boss              = 6,
    AnimationType_Num               = 7
};

class AnimationManager : public Ref, public Singleton<AnimationManager>
{
    friend class PListReader;
public:
    void addAnimation(uint hash, const std::string& name);
    void removeAnimation(uint hash);
    void runAction(Sprite* target, uint hash, bool repeatForever = true);
    void runAction(Sprite* target, int type, int key, int action, bool repeatForever = true);
    
    AnimationManager();
    virtual ~AnimationManager();
    
private:
    std::map<uint, std::string> m_key2Animate;
};

#endif /* defined(__TowerDefense__AnimationManager__) */
