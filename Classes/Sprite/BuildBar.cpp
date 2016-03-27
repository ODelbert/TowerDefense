//
//  BuildBar.cpp
//  TowerDefense
//
//  Created by jowu on 16/3/27.
//
//

#include "BuildBar.h"
#include "BattleField.h"
#include "GameManager.h"
#include "Event.h"

bool BuildBar::init()
{
    m_bar = ProgressTimer::create(Sprite::createWithSpriteFrameName("buildbar.png"));
    Sprite* bkg = Sprite::createWithSpriteFrameName("buildbar_bg.png");
    bkg->addChild(m_bar);
    addChild(bkg);
    m_bar->setType(ProgressTimer::Type::BAR);
    m_bar->setPosition(bkg->getContentSize().width / 2, bkg->getContentSize().height / 2);
    return true;
}

void BuildBar::build(int slotId, TowerID id)
{
    m_bar->runAction(Sequence::create(
                         ProgressTo::create(1, 100),
                         CallFunc::create(std::bind(&BuildBar::finish, this, slotId, id) ),
                         nullptr));
}

void BuildBar::finish(int slotId, TowerID id)
{
    TowerEvent event(TowerEvent::Command::UpgradeTower, slotId, static_cast<TowerID>(id));
    GM->dispatchEvent(&event);

    removeFromParent();

}


