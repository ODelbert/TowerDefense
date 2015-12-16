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

#define ANIMATION_HASH(type, key, act) (((type) << 20) | ((key) << 12) | (act))
#define ANIMATION_TYPE(hash) (((hash) & 0x00F00000) << 20)
#define ANIMATION_KEY(hash) (((hash) & 0x000FF000) << 12)
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

class AnimationManager : public Ref
{
    friend class PListReader;
public:
    static AnimationManager* getInstance();
    static void destroy();
    
    void addAnimation(int key, const std::string& name);
    void removeAnimation(int key);
    void runAction(Sprite* target, int key, bool repeatForever = true);
    void runAction(Sprite* target, int key, int act, bool repeatForever = true);

private:
    static AnimationManager* s_instance;
    
private:
    AnimationManager();
    virtual ~AnimationManager();
    
private:
    std::map<uint, std::string> m_key2Animate;
};

#endif /* defined(__TowerDefense__AnimationManager__) */
