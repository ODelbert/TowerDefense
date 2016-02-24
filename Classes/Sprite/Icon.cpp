#include "Icon.h"
#include "Tower/Tower.h"


// Tower upgrade icons
#define ICON_UPGRADE "main_icons_0005.png"
#define ICON_LOCK "main_icons_0005.png"
#define ICON_UPGRADE "main_icons_00014.png"
#define ICON_HARMMER "main_icons_00015.png"
#define ICON_CONFRIM "main_icons_0019.png"
#define ICON_ARCHER "main_icons_0100.png"
#define ICON_BARRACKS "main_icons_0101.png"
#define ICON_MAGE "main_icons_0102.png"
#define ICON_ARTILLERY "main_icons_103.png"
#define ICON_BLADESINGER "main_icons_104.png"
#define ICON_FORESTKEEPER "main_icons_105.png"
#define ICON_WILD "main_icons_106.png"
#define ICON_HIGHELF "main_icons_107.png"
#define ICON_ARCANE "main_icons_108.png"
#define ICON_SILVER "main_icons_0109.png"
#define ICON_HENGE "main_icons_0110.png"
#define ICON_TREE "main_icons_0111.png"

// tool tip icon
#define ICON_WEAPON_MAGIC "toptip_icons_0010.png"


#define ALERT_CREEP "creepAlert.png"
//creepAlertArrow.png
//DefenseFlag.png
//gui_ring.png
//"heart_0001.png"
//"hud_background.png" // 状态栏
//
//"hud_buttons_0001.png" // 暂停
//"hud_buttons_0002.png" // 恢复
//
//""
//
//ain_icons_0020.png 确认 灰色  0
//
//
//
//main_icons_0112   特定关卡
//
//main_icons_0113   特定关卡   幼龙
//main_icons_0114   特定关卡   龙 火焰

struct Location
{
    float x;
    float y;
};

static Location s_location[4] =
{
    { -0.3535, 0.3535 },
    { 0.3535, 0.3535 },
    { 0.3535, -0.3535 },
    { -0.3535, -0.3535 }
};


upgradeIcon* upgradeIcon::create(const std::string& name)
{
    upgradeIcon* ret = new upgradeIcon;
    if (ret && ret->init(name)) {
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool upgradeIcon::init(const std::string& name)
{
    m_texture = Sprite::createWithSpriteFrameName(name);
    if (!m_texture) return false;
    
    addChild(m_texture);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = CC_CALLBACK_2(upgradeIcon::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

bool upgradeIcon::onTouchBegan(Touch* touch, Event* event)
{
    if (m_state == Disabled) return false;

    // icon for towers
    auto towerSlot = getParent();
    if (towerSlot != nullptr) {
        auto tower = towerSlot->getParent();
        if (tower) {
            Tower* t = static_cast<Tower*>(tower);
            if (Selected == m_state) {
		m_state = Confrim;
		m_texture->setTexture(ICON_CONFRIM);
		// FIXME:: sound support
            }
            else if (Confrim == m_state) {
                t->upgrade(m_tid);
            }
            else {
	    }
        }
    }
    
    return true;
}
