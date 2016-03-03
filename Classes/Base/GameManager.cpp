//
//  GameManager.h
//  TowerDefense
//
//  Created by jowu on 15/11/22.
//
//



#include "GameManager.h"

GameManager::GameManager()
: m_gold(0)
{
    
}

void GameManager::dispatchEvent(TDEvent* event)
{
    Director::getInstance()->getEventDispatcher()->dispatchEvent(event);
}



