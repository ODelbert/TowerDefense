#include "LifeBar.h"

#define IMG_LIFEBAR "menu_bottom_lifeBar.png"
#define IMG_LIFEBAR_BKG1 "menu_bottom_lifeBar_bg_0001.png"
#define IMG_LIFEBAR_BKG2 "menu_bottom_lifeBar_bg_0002.png"

#include "BuildBar.h"
#include "BattleField.h"
#include "GameManager.h"
#include "Event.h"

bool BuildBar::init()
{
    m_bar = ProgressTimer::create(Sprite::createWithSpriteFrameName(IMG_LIFEBAR_BKG2));
    Sprite* bkg = Sprite::createWithSpriteFrameName(IMG_LIFEBAR_BKG1);
    bkg->addChild(m_bar);
    addChild(bkg);
    m_bar->setType(ProgressTimer::Type::BAR);
    m_bar->setPosition(bkg->getContentSize().width / 2, bkg->getContentSize().height / 2);
    return true;
}

void BuildBar::setPercentage(float precent)
{
    m_bar->setPercentage(precent);
}

void BuildBar::finish(int slotId, TowerID id)
{
    TowerEvent event(TowerEvent::Command::UpgradeTower, slotId, static_cast<TowerID>(id));
    GM->dispatchEvent(&event);

    removeFromParent();
}
