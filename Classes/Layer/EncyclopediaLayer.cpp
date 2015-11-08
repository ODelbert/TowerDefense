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
    
private:
    Sprite* m_leftBook;
    Sprite* m_rightBook;
    
};

class TowerBook : public Node
{
    
};

bool EnemyBook::init()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    m_leftBook = Sprite::createWithSpriteFrameName("encyclopedia_book_pg.png");
    m_leftBook->setFlippedX(true);
    addChild(m_leftBook);
    m_leftBook->setPosition(Vec2(0.25 * TD_WIDTH + origin.x, 0.5 * TD_HEIGHT  + origin.y));

    m_rightBook = Sprite::createWithSpriteFrameName("encyclopedia_book_pg.png");
    addChild(m_rightBook);
    m_rightBook->setPosition(Vec2(0.75 * TD_WIDTH + origin.x, 0.5 * TD_HEIGHT + origin.y));

    return true;
}

bool EncyclopediaLayer::init()
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    m_eBook = EnemyBook::create();
    addChild(m_eBook);
    return true;
}
