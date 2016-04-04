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
    void initialize();
    Animation* getAnimation(const std::string& name);
    void addAnimation(const std::string& name, const std::string& prefix, int toIndex, int formIndex);
    void removeAnimation(const std::string& name);
    void runAction(Sprite* target, const std::string& name, bool repeatForever = true);
    
    AnimationManager();
    virtual ~AnimationManager();
    
private:
    bool m_initd;
};

#define AM AnimationManager::getInstance()

#endif /* defined(__TowerDefense__AnimationManager__) */
