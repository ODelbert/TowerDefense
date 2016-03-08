#include "Icon.h"
#include "Tower/Tower.h"
#include "Base/Event.h"
#include "Sprite/TowerSlot.h"
#include "Base/GameManager.h"

#define ICON_UPGRADE "main_icons_0005.png"
#define ICON_DISABLED_UPGRADE "main_icons_disabled_0005.png"
#define ICON_LOCK "main_icons_0014.png"
#define ICON_DISABLED_LOCK "main_icons_disabled_0005.png"
#define ICON_HARMMER "main_icons_0015.png"
#define ICON_DISABLED_HARMMER "main_icons_disabled_0015.png"
#define ICON_CONFRIM "main_icons_0019.png"
#define ICON_DISABLED_CONFRIM "main_icons_disabled_0019.png"
#define ICON_ARCHER "main_icons_0100.png"
#define ICON_DISABLED_ARCHER "main_icons_disabled_0100.png"
#define ICON_BARRACKS "main_icons_0101.png"
#define ICON_DISABLED_BARRACKS "main_icons_disabled_0101.png"
#define ICON_MAGE "main_icons_0102.png"
#define ICON_DISABLED_MAGE "main_icons_disabled_0102.png"
#define ICON_ARTILLERY "main_icons_0103.png"
#define ICON_DISABLED_ARTILLERY "main_icons_disabled_0103.png"
#define ICON_BLADESINGER "main_icons_0104.png"
#define ICON_DISABLED_BLADESINGER "main_icons_disabled_0104.png"
#define ICON_FORESTKEEPER "main_icons_0105.png"
#define ICON_DISABLED_FORESTKEEPER "main_icons_disabled_0105.png"
#define ICON_WILD "main_icons_0106.png"
#define ICON_DISABLED_WILD "main_icons_disabled_0106.png"
#define ICON_HIGHELF "main_icons_0107.png"
#define ICON_DISABLED_HIGHELF "main_icons_disabled_0107.png"
#define ICON_ARCANE "main_icons_0108.png"
#define ICON_DISABLED_ARCANE "main_icons_disabled_0108.png"
#define ICON_SILVER "main_icons_0109.png"
#define ICON_DISABLED_SILVER "main_icons_disabled_0109.png"
#define ICON_HENGE "main_icons_0110.png"
#define ICON_DISABLED_HENGE "main_icons_disabled_0110.png"
#define ICON_TREE "main_icons_0111.png"
#define ICON_DISABLED_TREE "main_icons_disabled_0111.png"

#define ICON_SELL "ico_sell_0001.png"
#define ICON_SELL_CONFIRM "ico_sell_0002.png"
#define ICON_CANNOT_SELL "ico_sell_disabled_0001.png"

#define ICON_WEAPON_MAGIC "toptip_icons_0010.png"

#define ICON_ARCANE_1 "special_icons_0101.png"
#define ICON_DISABLED_ARCANE_1 "special_icons_disabled_0101.png"
#define ICON_ARCANE_2 "special_icons_0100.png"
#define ICON_DISABLED_ARCANE_2 "special_icons_disabled_0100.png"
#define ICON_ARCANE_3 "xxx"
#define ICON_DISABLED_ARCANE_3 "xxx.png"

#define ICON_SILVER_1 "special_icons_0102.png"
#define ICON_DISABLED_SILVER_1 "special_icons_disabled_0102.png"
#define ICON_SILVER_2 "special_icons_0103.png"
#define ICON_DISABLED_SILVER_2 "special_icons_disabled_0103.png"
#define ICON_SILVER_3 "xxx.png"
#define ICON_DISABLED_SILVER_3 "xxx.png"

#define ICON_BLADESINGER_1 "special_icons_0104.png"
#define ICON_DISABLED_BLADESINGER_1 "special_icons_disabled_0104.png"
#define ICON_BLADESINGER_2 "special_icons_0105.png"
#define ICON_DISABLED_BLADESINGER_2 "special_icons_disabled_0105.png"
#define ICON_BLADESINGER_3 "special_icons_0106.png"
#define ICON_DISABLED_BLADESINGER_3 "special_icons_disabled_0106.png"

#define ICON_FORESTKEEPER_1 "special_icons_0107.png"
#define ICON_DISABLED_FORESTKEEPER_1 "special_icons_disabled_0107.png"
#define ICON_FORESTKEEPER_2 "special_icons_0109.png"
#define ICON_DISABLED_FORESTKEEPER_2 "special_icons_disabled_0109.png"
#define ICON_FORESTKEEPER_3 "special_icons_0110.png"
#define ICON_DISABLED_FORESTKEEPER_3 "special_icons_disabled_0110.png"

#define ICON_HENGE_1 "special_icons_0111.png"
#define ICON_DISABLED_HENGE_1 "special_icons_disabled_0111.png"
#define ICON_HENGE_2 "special_icons_0112.png"
#define ICON_DISABLED_HENGE_2 "special_icons_disabled_0112.png"
#define ICON_HENGE_3 "xxx.png"
#define ICON_DISABLED_HENGE_3 "xxx.png"

#define ICON_TREE_1 "special_icons_0113.png"
#define ICON_DISABLED_TREE_1 "special_icons_disabled_0113.png"
#define ICON_TREE_2 "special_icons_0114.png"
#define ICON_DISABLED_TREE_2 "special_icons_disabled_0114.png"
#define ICON_TREE_3 "xxx.png"
#define ICON_DISABLED_TREE_3 "xxx.png"

#define ICON_WILD_1 "special_icons_0115.png"
#define ICON_DISABLED_WILD_1 "special_icons_disabled_0115.png"
#define ICON_WILD_2 "special_icons_0116.png"
#define ICON_DISABLED_WILD_2 "special_icons_disabled_0116.png"
#define ICON_WILD_3 "xxx.png"
#define ICON_DISABLED_WILD_3 "xxx.png"

#define ICON_HIGHELF_1 "special_icons_0117.png"
#define ICON_DISABLED_HIGHELF_1 "special_icons_disabled_0117.png"
#define ICON_HIGHELF_2 "special_icons_0118.png"
#define ICON_DISABLED_HIGHELF_2 "special_icons_disabled_0118.png"
#define ICON_HIGHELF_3 "xxx.png"
#define ICON_DISABLED_HIGHELF_3 "xxx.png"

#define ICON_CONFRIM "main_icons_0111.png"

static std::string GetTechnologyIcon(TowerID id, bool enabled, int tid)
{
    switch (id) {
        case TowerID_Archer_Arcane:
        {
            switch (tid) {
                case 0:
                    return enabled ? ICON_ARCANE_1 : ICON_DISABLED_ARCANE_1;
                case 1:
                    return enabled ? ICON_ARCANE_2 : ICON_DISABLED_ARCANE_2;
                case 2:
                    return enabled ? ICON_ARCANE_3 : ICON_DISABLED_ARCANE_3;
                default:
                    break;
            }
        }
            break;
        case TowerID_Archer_Silver:
        {
            switch (tid) {
                case 0:
                    return enabled ? ICON_SILVER_1 : ICON_DISABLED_SILVER_1;
                case 1:
                    return enabled ? ICON_SILVER_2 : ICON_DISABLED_SILVER_2;
                case 2:
                    return enabled ? ICON_SILVER_3 : ICON_DISABLED_SILVER_3;
                default:
                    break;
            }
        }
            break;
        case TowerID_BladeSinger:
        {
            switch (tid) {
                case 0:
                    return enabled ? ICON_BLADESINGER_1 : ICON_DISABLED_BLADESINGER_1;
                case 1:
                    return enabled ? ICON_BLADESINGER_2 : ICON_DISABLED_BLADESINGER_2;
                case 2:
                    return enabled ? ICON_BLADESINGER_3 : ICON_DISABLED_BLADESINGER_3;
                default:
                    break;
            }
        }
            break;
        case TowerID_ForestKeeper:
        {
            switch (tid) {
                case 0:
                    return enabled ? ICON_FORESTKEEPER_1 : ICON_DISABLED_FORESTKEEPER_1;
                case 1:
                    return enabled ? ICON_FORESTKEEPER_2 : ICON_DISABLED_FORESTKEEPER_2;
                case 2:
                    return enabled ? ICON_FORESTKEEPER_3 : ICON_DISABLED_FORESTKEEPER_3;
                default:
                    break;
            }
        }
            break;
        case TowerID_Mage_Wild:
        {
            switch (tid) {
                case 0:
                    return enabled ? ICON_WILD_1 : ICON_DISABLED_WILD_1;
                case 1:
                    return enabled ? ICON_WILD_2 : ICON_DISABLED_WILD_2;
                case 2:
                    return enabled ? ICON_WILD_3 : ICON_DISABLED_WILD_3;
                default:
                    break;
            }
        }
            break;
        case TowerID_Mage_HighElven:
        {
            switch (tid) {
                case 0:
                    return enabled ? ICON_HIGHELF_1 : ICON_DISABLED_HIGHELF_1;
                case 1:
                    return enabled ? ICON_HIGHELF_2 : ICON_DISABLED_HIGHELF_2;
                case 2:
                    return enabled ? ICON_HIGHELF_3 : ICON_DISABLED_HIGHELF_3;
                default:
                    break;
            }
        }
            break;
        case TowerID_Artillery_Henge:
        {
            switch (tid) {
                case 0:
                    return enabled ? ICON_HENGE_1 : ICON_DISABLED_HENGE_1;
                case 1:
                    return enabled ? ICON_HENGE_2 : ICON_DISABLED_HENGE_2;
                case 2:
                    return enabled ? ICON_HENGE_3 : ICON_DISABLED_HENGE_3;
                default:
                    break;
            }
        }
            break;
        case TowerID_Artillery_Tree:
        {
            switch (tid) {
                case 0:
                    return enabled ? ICON_TREE_1 : ICON_DISABLED_TREE_1;
                case 1:
                    return enabled ? ICON_TREE_2 : ICON_DISABLED_TREE_2;
                case 2:
                    return enabled ? ICON_TREE_3 : ICON_DISABLED_TREE_3;
                default:
                    break;
            }
        }
            break;

        default:
            break;
    }
    
    return "";
}

UpgradeIcon* UpgradeIcon::create(TowerID id, bool enabled)
{
    UpgradeIcon* ret = new UpgradeIcon();
    if (ret && ret->init(id, enabled)) {
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool UpgradeIcon::init(TowerID id, bool enabled)
{
    m_id = id;
    m_enabled = enabled;

    switch (id) {
    case TowerID_Archer_Lv1:
    {
        m_enabledImage = Sprite::createWithSpriteFrameName(ICON_ARCHER);
        m_disabledImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_ARCHER);
    }
        break;
    case TowerID_Barrack_Lv1:
    {
        m_enabledImage = Sprite::createWithSpriteFrameName(ICON_ARCHER);
        m_disabledImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_ARCHER);
    }
        break;
    case TowerID_Mage_Lv1:
    {
        m_enabledImage = Sprite::createWithSpriteFrameName(ICON_MAGE);
        m_disabledImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_MAGE);
    }
        break;
    case TowerID_Artillery_Lv1:
    {
        m_enabledImage = Sprite::createWithSpriteFrameName(ICON_ARTILLERY);
        m_disabledImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_ARTILLERY);
    }
        break;
    case TowerID_Archer_Arcane:
    {
        m_enabledImage = Sprite::createWithSpriteFrameName(ICON_ARTILLERY);
        m_disabledImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_ARTILLERY);
        return enabled ? ICON_ARCANE : ICON_DISABLED_ARCANE;
    }
        break;
    case TowerID_Archer_Silver:
    {
        m_enabledImage = Sprite::createWithSpriteFrameName(ICON_ARTILLERY);
        m_disabledImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_ARTILLERY);
        return enabled ? ICON_SILVER : ICON_DISABLED_SILVER;
    }
        break;
    case TowerID_BladeSinger:
    {
        m_enabledImage = Sprite::createWithSpriteFrameName(ICON_BLADESINGER);
        m_disabledImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_BLADESINGER);
    }
        break;
    case TowerID_ForestKeeper:
    {
        m_enabledImage = Sprite::createWithSpriteFrameName(ICON_FORESTKEEPER);
        m_disabledImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_FORESTKEEPER);
    }
        break;
    case TowerID_Mage_Wild:
    {
        m_enabledImage = Sprite::createWithSpriteFrameName(ICON_WILD);
        m_disabledImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_WILD);
    }
        break;
    case TowerID_Mage_HighElven:
    {
        m_enabledImage = Sprite::createWithSpriteFrameName(ICON_HIGHELF);
        m_disabledImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_HIGHELF);
    }
        break;
    case TowerID_Artillery_Henge:
    {
        m_enabledImage = Sprite::createWithSpriteFrameName(ICON_HENGE);
        m_disabledImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_HENGE);
    }
        break;
    case TowerID_Artillery_Tree:
    {
        m_enabledImage = Sprite::createWithSpriteFrameName(ICON_TREE);
        m_disabledImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_TREE);
        return enabled ? ICON_TREE : ICON_DISABLED_TREE;
    }
        break;
    default:
        break;
    }

    m_confrimImage = Sprite::createWithSpriteFrameName(ICON_CONFRIM);
    m_disabledConfrimImage = Sprite::createWithSpriteFrameName(ICON_DISABLED_CONFRIM);
    if (!m_enabledImage || !m_disabledImage || !m_confrimImage || !m_disabledConfrimImage) {
        return false;
    }

    initTouchListeners();
    setTouchCallback(CC_CALLBACK_0(UpgradeIcon::onTouchEvent, this));
    auto towerFrame = Sprite::createWithSpriteFrameName("main_icons_over.png");
    addChild(towerFrame);
    addChild(m_confrimImage);
    addChild(m_disabledConfrimImage);
    addChild(m_enabledImage);
    addChild(m_disabledImage);
    
    lightenIcon(enabled ? m_enabledImage : m_disabledImage);

    return true;
}

void UpgradeIcon::onTouchEvent()
{
    switch (m_state) {
    case Enabled:
        {
            m_state = Selected;
            lightenIcon(GM->enoughGold(GM->getUpgradeFund(m_id)) ? m_confrimImage : m_disabledConfrimImage);
        }
        break;
    case Selected:
        {
            if (!getParent() || !getParent()->getParent()) return;
            TowerSlot* towerSlot = static_cast<TowerSlot*>(getParent()->getParent());
            if (towerSlot != nullptr) {
                auto tower = towerSlot->getTower();
                if (tower) {
                    Tower* t = static_cast<Tower*>(tower);
                    TowerEvent evt(TowerEvent::Command::UpgradeTower, towerSlot->getSlotId(), tower->getId(), tower->getLevel());

                    // add new tower in next frame
                    GM->dispatchEvent(&evt);
                    GM->setGold(GM->getGold() - GM->getUpgradeFund(m_id));
                    t->removeFromParent();
                }
                else {
                    
                }
            }
        }
        break;
    case Disabled:
    default:
        {}
        break;
    }
}

void UpgradeIcon::lightenIcon(Sprite* sprite)
{
    if (!m_enabledImage || !m_disabledImage || !m_confrimImage || !m_disabledConfrimImage) {
        return;
    }
    m_confrimImage->setVisible(false);
    m_disabledConfrimImage->setVisible(false);
    m_enabledImage->setVisible(false);
    m_disabledImage->setVisible(false);

    if (sprite) {
        sprite->setVisible(true);
    }
}

SellIcon* SellIcon::create()
{
    SellIcon* ret = new SellIcon;
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool SellIcon::init()
{
    return true;
}

TechnologyIcon* TechnologyIcon::create(TowerID id, int tid)
{
    TechnologyIcon* ret = new TechnologyIcon;
    if (ret && ret->init(id, tid)) {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool TechnologyIcon::init(TowerID id, int tid)
{
    return true;
}
