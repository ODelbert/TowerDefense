#include "LifeBar.h"

#define IMG_LIFEBAR "menu_bottom_lifeBar.png"
#define IMG_LIFEBAR_BKG1 "menu_bottom_lifeBar_bg_0001.png"
#define IMG_LIFEBAR_BKG2 "menu_bottom_lifeBar_bg_0002.png"

#include "BuildBar.h"
#include "BattleField.h"
#include "GameManager.h"
#include "Event.h"

LifeBar::LifeBar(Sprite* owner)
    : m_owner(owner) {

}

LifeBar* LifeBar::create(Sprite *owner)
{
    LifeBar* ret = new LifeBar(owner);
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool LifeBar::init()
{
    m_bar = ProgressTimer::create(Sprite::createWithSpriteFrameName(IMG_LIFEBAR_BKG2));
    Sprite* bkg = Sprite::createWithSpriteFrameName(IMG_LIFEBAR_BKG1);
    if (!bkg) {
        return false;
    }

    bkg->addChild(m_bar);
    addChild(bkg);
    m_bar->setType(ProgressTimer::Type::BAR);
    m_bar->setPosition(bkg->getContentSize().width / 2, bkg->getContentSize().height / 2);

    if (m_owner) {
        m_owner->addChild(this);
        return true;
    }
    else {
        return false;
    }
}

void LifeBar::setPercentage(float precent)
{
    m_bar->setPercentage(precent);
}

