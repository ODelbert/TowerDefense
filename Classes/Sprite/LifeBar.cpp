#include "LifeBar.h"

#define IMG_LIFEBAR "menu_bottom_lifeBar.png"
#define IMG_LIFEBAR_BKG1 "menu_bottom_lifeBar_bg_0001.png"
#define IMG_LIFEBAR_BKG2 "menu_bottom_lifeBar_bg_0002.png"




//lifebar_bg_big.png        lifebar_big.png           lifebar_white_big.png
//lifebar_bg_med.png        lifebar_med.png           lifebar_white_med.png
//lifebar_bg_medBig.png     lifebar_medBig.png        lifebar_white_medBig.png
//lifebar_bg_small.png      lifebar_small.png         lifebar_white_small.png


#include "BuildBar.h"
#include "BattleField.h"
#include "GameManager.h"
#include "Event.h"
static const std::string s_surfixs[] =
{
    "small.png",
    "med.png",
    "medBig.png",
    "big.png",
};

LifeBar* LifeBar::create(Scale scale)
{
    LifeBar* ret = new LifeBar;
    if (ret && ret->init(scale)) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool LifeBar::init(Scale scale)
{
    m_bar = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifebar_" + s_surfixs[scale]));
    Sprite* bkg = Sprite::createWithSpriteFrameName("lifebar_bg_" + s_surfixs[scale]);
    if (!bkg) {
        return false;
    }

    bkg->addChild(m_bar);
    addChild(bkg);
    m_bar->setType(ProgressTimer::Type::BAR);
    m_bar->setPercentage(100);
    m_bar->setMidpoint(Vec2(0,0));
    m_bar->setPosition(bkg->getContentSize().width / 2, bkg->getContentSize().height / 2);

    return true;
}

void LifeBar::setPercentage(float precent)
{
    if (m_bar)
        m_bar->setPercentage(precent);
}

float LifeBar::getPercentage()
{
    if (m_bar)
        return m_bar->getPercentage();
}

