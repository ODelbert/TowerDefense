//
//  ResourceManager.h
//  TowerDefense
//
//  Created by jowu on 15/11/6.
//
//

#ifndef __TowerDefense__ResourceManager__
#define __TowerDefense__ResourceManager__

#include <stdio.h>

#include "cocos2d.h"
USING_NS_CC;

class ResourceManager : public Ref
{
public:
    static ResourceManager* getInstance();
    static void destroy();
    bool initialize();
private:
    static ResourceManager* s_instance;
};

#endif /* defined(__TowerDefense__ResourceManager__) */
