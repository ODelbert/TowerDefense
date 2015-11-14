//
//  EncyclopediaLayer.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/7.
//
//

#include "EncyclopediaLayer.h"
#include "CommonDef.h"
#include "Enemy.h"

class EnemyBook : public Node
{
public:
    CREATE_FUNC(EnemyBook);
    bool init();
    void nextPage();
    void prePage();
private:
    void demonstrate();
private:
    Sprite* m_leftBook;
    Sprite* m_rightBook;
    Sprite* m_enemies[48];
    Sprite* m_pageIcon[3];
    Label* m_lifeLabel;
    Label* m_attackLabel;
    Label* m_defenseLabel;
    Label* m_resistLabel;
    Label* m_speedLabel;
    Label* m_foodLabel;
    Menu* m_menuPre;
    Menu* m_menuNext;
    
    Sprite* m_greyPre;
    Sprite* m_greyNext;
    
    int m_pageIndex;
    int m_choosenIndex;
    
};

class TowerBook : public Node
{
    
};

bool EnemyBook::init()
{
    m_pageIndex = 0;
    m_pageIndex = 0;
    Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_leftBook = Sprite::createWithSpriteFrameName("encyclopedia_book_pg.png");
    m_leftBook->setFlippedX(true);
    addChild(m_leftBook);
    m_leftBook->setPosition(Vec2(0.25 * TD_WIDTH + origin.x, 0.5 * TD_HEIGHT  + origin.y));

    m_rightBook = Sprite::createWithSpriteFrameName("encyclopedia_book_pg.png");
    addChild(m_rightBook);
    m_rightBook->setPosition(Vec2(0.75 * TD_WIDTH + origin.x, 0.5 * TD_HEIGHT + origin.y));

    auto titile = LabelTTF::create("黑暗势力", TD_FONT, 20);
    titile->setColor(Color3B(102, 51, 0));
    titile->setPosition(0.3 * TD_WIDTH, TD_HEIGHT - 80);
    m_leftBook->addChild(titile);
    
    static int s_gap = 5;
    static int s_len = 94;
    auto touchLitener = EventListenerTouchOneByOne::create();
    touchLitener->setSwallowTouches(true);
    auto onTouchEvent = [&](Touch* t, Event* e)->bool {
        if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()) && e->getCurrentTarget()->isVisible()) {
            m_enemies[m_choosenIndex]->setSpriteFrame("encyclopedia_creep_thumbs_frame_0001.png");
            
            CCLOG("touch sprite name %s", e->getCurrentTarget()->getName().c_str());
            Sprite* target = dynamic_cast<Sprite*>(e->getCurrentTarget());
            target->setSpriteFrame("encyclopedia_creep_thumbs_frame_0002.png");
            m_choosenIndex = target->getTag();
            demonstrate();
            return true;
        }
        
        return false;
        
#ifdef TD_DEBUG
        Vec2 nodePos = e->getCurrentTarget()->convertToNodeSpace(e->getCurrentTarget()->getPosition());
        Vec2 worldPos = e->getCurrentTarget()->convertToWorldSpace(e->getCurrentTarget()->getPosition());
        Vec2 touchNodePos = e->getCurrentTarget()->convertTouchToNodeSpace(t);
        
        CCLOG("touch world pos [%f %f] node pos [%f %f] target pos[%f %f] node pos [%f %f] world[%f %f]",
              t->getLocation().x, t->getLocation().y,
              touchNodePos.x, touchNodePos.y,
              e->getCurrentTarget()->getPosition().x, e->getCurrentTarget()->getPosition().y,
              nodePos.x, nodePos.y,
              worldPos.x, worldPos.y
              );
        CCLOG("touch sprite name %s", e->getCurrentTarget()->getName().c_str());
#endif
        return true;
    };
    
    touchLitener->onTouchBegan = onTouchEvent;
    for (int k = 0; k < 48; ++k) {
        m_enemies[k] = Sprite::createWithSpriteFrameName("encyclopedia_creep_thumbs_frame_0001.png");
        auto icon = Sprite::createWithSpriteFrameName(String::createWithFormat("encyclopedia_creep_thumbs_00%02d.png", k+1)->getCString());
        if (!m_enemies[k]) continue;
        m_enemies[k]->setName(String::createWithFormat("encyclopedia_creep_thumbs_00%02d.png", k + 1)->getCString());
        int posX = 180 + ((k % 16) % 4) * (s_gap + s_len);
        int posY = 470 - ((k % 16) / 4) * (s_gap + s_len);
        m_enemies[k]->setPosition(Vec2(posX, posY));
        m_enemies[k]->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchLitener->clone(), m_enemies[k]);
        m_leftBook->addChild(m_enemies[k]);
        m_enemies[k]->addChild(icon);
        m_enemies[k]->setTag(k);
        m_enemies[k]->setVisible(false);
        icon->setPosition(0.5 * m_enemies[k]->getContentSize().width, 0.5 * m_enemies[k]->getContentSize().height);
    }

    auto nextIconNormal = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0003.png");
    auto nextIconPressed = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0002.png");
    m_menuNext = Menu::create(MenuItemSprite::create(nextIconNormal, nextIconPressed, CC_CALLBACK_0(EnemyBook::nextPage, this)), NULL);
    m_menuNext->setPosition(480, 90);
    
    auto preIconNormal = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0003.png");
    auto preIconPressed = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0002.png");
    preIconNormal->setFlippedX(true);
    preIconPressed->setFlippedX(true);
    m_menuPre = Menu::create(MenuItemSprite::create(preIconNormal, preIconPressed, CC_CALLBACK_0(EnemyBook::prePage, this)), NULL);
    
    m_menuPre->setPosition(190, 90);
    for(int i = 0; i < 3; ++i) {
        m_pageIcon[i] = Sprite::createWithSpriteFrameName(String::createWithFormat("backPack_numbers_000%d.png", i + 1)->getCString());
        m_pageIcon[i]->setPosition(265 + 70 * i, 90);
        m_leftBook->addChild(m_pageIcon[i]);
    }
    
    addChild(m_menuNext);
    addChild(m_menuPre);
    
    m_greyPre = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0001.png");
    m_greyNext = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0001.png");
    m_greyPre->setFlippedX(true);
    addChild(m_greyPre);
    addChild(m_greyNext);
    m_greyPre->setPosition(190, 90);
    m_greyNext->setPosition(480, 90);
    
    auto closeMenu = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png"), Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0002.png"), [&](Ref *sender) {
        CCLOG("enemy book close -> un visible!");
        this->setVisible(false);
    }), NULL);
    
    m_rightBook->addChild(closeMenu);
    closeMenu->setPosition(432, TD_HEIGHT - 80);
    
    m_choosenIndex = 47;
    m_pageIndex = 0;
    demonstrate();

    return true;
}

void EnemyBook::demonstrate()
{
    if (m_pageIndex == 0) {
        m_menuPre->setVisible(false);
        m_greyPre->setVisible(true);
        m_menuNext->setVisible(true);
        m_greyNext->setVisible(false);
    }
    else if (m_pageIndex == 2) {
        m_menuPre->setVisible(true);
        m_greyPre->setVisible(false);
        m_menuNext->setVisible(false);
        m_greyNext->setVisible(true);
    }
    else {
        m_menuPre->setVisible(true);
        m_menuNext->setVisible(true);
        m_greyPre->setVisible(false);
        m_greyNext->setVisible(false);
    }
    
    auto status = Sprite::createWithSpriteFrameName("encyclopedia_creep_infopanel.png");
    TD_SIZE(status);
    m_rightBook->addChild(status);
    status->setPosition(250, 150);
    
    auto photoFrame = Sprite::createWithSpriteFrameName("encyclopedia_big_frame_0001.png");
    auto photoImage = Sprite::create(String::createWithFormat("encyclopedia_creeps_00%02d-hd.png", m_choosenIndex + 1)->getCString());
    TD_SIZE(photoFrame);
    TD_SIZE(photoImage);
    photoImage->setScale(0.7, 0.7);
    m_rightBook->addChild(photoFrame);
    photoFrame->addChild(photoImage);
    photoImage->setPosition(0.5 * photoFrame->getContentSize().width, 0.5 * photoFrame->getContentSize().height);
    photoFrame->setPosition(250, 480);
    
    for (int i = 0; i < 48; ++i) {
        bool visible = i / 16 == m_pageIndex;
        m_enemies[i]->setVisible(visible);
    }
}

void EnemyBook::prePage()
{
    if (m_pageIndex > 0) {
        --m_pageIndex;
        demonstrate();
    }
}

void EnemyBook::nextPage()
{
    if (m_pageIndex < 2) {
        ++m_pageIndex;
        demonstrate();
    }
}

bool EncyclopediaLayer::init()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_na-hd.plist");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_32_2-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_na_i4-hd.plist");
    
    auto enemyBtnNormal = Sprite::createWithSpriteFrameName("encyclopedia_button_enemies_0001.png");
    auto enemyBtnPressed = Sprite::createWithSpriteFrameName("encyclopedia_button_enemies_0001.png");
    enemyBtnPressed->setScale(0.8);
    auto towerBtnNormal = Sprite::createWithSpriteFrameName("encyclopedia_button_towers_0001.png");
    auto towerBtnPressed = Sprite::createWithSpriteFrameName("encyclopedia_button_towers_0001.png");
    towerBtnPressed->setScale(0.8);
    
    auto enemyMenu = Menu::create(MenuItemSprite::create(enemyBtnNormal, enemyBtnPressed, [&](Ref *sender) {
        m_eBook->setVisible(true);
    }), nullptr);
    
    auto towerMenu = Menu::create(MenuItemSprite::create(towerBtnNormal, towerBtnPressed, [&](Ref *sender) {
        m_eBook->setVisible(true);
    }), nullptr);
    
    towerMenu->setPosition(Vec2(250, 300));
    enemyMenu->setPosition(Vec2(200+towerBtnNormal->getContentSize().width, 300));
    addChild(towerMenu);
    addChild(enemyMenu);
    
    auto menuTower = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_button_close_0001.png"), Sprite::createWithSpriteFrameName("encyclopedia_button_close_0001.png"), [](Ref *sender) {
        CCLOG("Encyclopedia book close!!");
    }), nullptr);
    
    auto menuClose = Menu::create(MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_button_close_0001.png"), Sprite::createWithSpriteFrameName("encyclopedia_button_close_0001.png"), [](Ref *sender) {
        CCLOG("Encyclopedia book close!!");
    }), nullptr);
    menuClose->setPosition(Vec2(TD_WIDTH - 150, TD_HEIGHT - 150));
    addChild(menuClose, -1);
    
    m_eBook = EnemyBook::create();
    addChild(m_eBook);
    return true;
}

void EncyclopediaLayer::close(Ref* sender)
{
    this->setVisible(true);
}
