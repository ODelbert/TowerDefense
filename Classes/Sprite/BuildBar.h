//
//  BuildBar.h
//  TowerDefense
//
//  Created by jowu on 16/3/27.
//
//

#ifndef BuildBar_hpp
#define BuildBar_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;
class BuildBar : public Node
{
public:
    CREATE_FUNC(BuildBar);
    virtual bool init();
    
    void build(int slotId, TowerID id);
    void finish(int slotId, TowerID id);
    
private:
    ProgressTimer* m_bar;
};

#endif /* BuildBar_h */
