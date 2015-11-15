//
//  EnemyBase.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/7.
//
//

#include "cocos2d.h"
#include "CommonDef.h"
#include "Enemy.h"
#include "AnimationManager.h"

USING_NS_CC;

enum ActionCommon
{
    ActionCommon_Attack = 0,
    ActionCommon_WalkingDown,
    ActionCommon_WalkingRightLeft,
    ActionCommon_Idle,
    ActionCommon_WalkingUp,
    ActionCommon_Death,
    ActionCommon_Spawn,
    ActionCommon_Respawn,
    ActionCommon_Shoot,
    ActionCommon_Cast,
    ActionCommon_Special,
};


bool Enemy::initWithEnemyId(EnemyID id)
{
    EnemyInfo info ;//= EnemyData::getInstance()->qurey(id);
    m_id = id;
    m_name = info.name;
    m_damageMin = info.dmgMin;
    m_damageMax = info.dmgMax;
    m_maxLife = info.life;
    m_life = m_maxLife;
    m_weapon = static_cast<WeaponType>(info.weapon);
    m_armor = static_cast<ArmorType>(info.armor);
    m_speed = static_cast<SpeedType>(info.speed);
    
    return true;
}

void Enemy::idle()
{
    AnimationManager::getInstance()->runAction(this, static_cast<int>(m_id), ActionCommon_Idle);
}

void Enemy::walkingLeft()
{
    AnimationManager::getInstance()->runAction(this, static_cast<int>(m_id), ActionCommon_WalkingRightLeft);
}

void Enemy::walkingRight()
{
    setFlippedX(true);
    AnimationManager::getInstance()->runAction(this, static_cast<int>(m_id), ActionCommon_WalkingRightLeft);
}

void Enemy::walkingDown()
{
    AnimationManager::getInstance()->runAction(this, static_cast<int>(m_id), ActionCommon_WalkingDown);
}

void Enemy::walkingUp()
{
    AnimationManager::getInstance()->runAction(this, static_cast<int>(m_id), ActionCommon_WalkingUp);
}

void Enemy::death()
{
    AnimationManager::getInstance()->runAction(this, static_cast<int>(m_id), ActionCommon_Death);
}

void Enemy::spawn()
{
    AnimationManager::getInstance()->runAction(this, static_cast<int>(m_id), ActionCommon_Spawn);
}

void Enemy::respawn()
{
    AnimationManager::getInstance()->runAction(this, static_cast<int>(m_id), ActionCommon_Respawn);
}

void Enemy::shoot()
{
    AnimationManager::getInstance()->runAction(this, static_cast<int>(m_id), ActionCommon_Shoot);
}

void Enemy::cast()
{
    AnimationManager::getInstance()->runAction(this, static_cast<int>(m_id), ActionCommon_Cast);
}

void Enemy::speicialAttack()
{
    AnimationManager::getInstance()->runAction(this, static_cast<int>(m_id), ActionCommon_Special);
}
