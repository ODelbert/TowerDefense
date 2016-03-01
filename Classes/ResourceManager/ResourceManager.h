//
//  ResourceManager.h
//  TowerDefense
//
//  Created by jowu on 15/11/6.
//
//

#ifndef __TowerDefense__ResourceManager__
#define __TowerDefense__ResourceManager__

#include "cocos2d.h"
#include "Base/Singleton.h"

USING_NS_CC;

class ResourceManager : public Ref, public Singleton<ResourceManager>
{
public:
    ResourceManager();
    bool initialize();
};

#endif /* defined(__TowerDefense__ResourceManager__) */
