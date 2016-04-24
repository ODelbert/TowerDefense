//
//  Stage1.h
//  TowerDefense
//
//  Created by jowu on 15/11/16.
//
//

#ifndef __TowerDefense__Stage1__
#define __TowerDefense__Stage1__
#include "Sprite/LifeBar.h"
#include "BattleField.h"

class Stage1 : public BattleField
{
public:
    CREATE_FUNC(Stage1)
    virtual bool init();
    virtual void addTowerSlots();
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
private:
    LifeBar *m_bar;
};

#endif /* defined(__TowerDefense__Level1__) */
