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

void WayPoints::setPoints(const std::vector<Vec2>& points)
{
    if (m_points.empty()) {
        m_points.clear();
    }
    
    m_points = points;
}

Vec2 WayPoints::getcurPoint() const
{
    if (m_pathIndex >= m_points.size()) {
        return Vec2();
    }
    
    return m_points[m_pathIndex];
}

Direction WayPoints::getDirection() const
{
    return m_dir;
}

bool WayPoints::moveToNextPoint()
{
    if (m_pathIndex >= m_points.size()) {
        return false;
    }
    
    float angle = atan2f(m_points[m_pathIndex + 1].y - m_points[m_pathIndex].y, m_points[m_pathIndex + 1].x - m_points[m_pathIndex].x) * 180 / 3.14;
    
    if (angle > -45 && angle <= 45) {
        m_dir = Direction_Right;
    }
    else if (angle > 45 && angle <= 135) {
        m_dir = Direction_Up;
    }
    else if (angle >=135 && angle <=225) {
        m_dir = Direction_Left;
    }
    else {
        m_dir = Direction_Down;
    }
    
    ++m_pathIndex;
    return true;
}

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
    
    m_state = EnemyState_Invalid;
    m_buffs = 0;
    m_debuffs = 0;
    m_direction = Direction_Invalid;
    return true;
}

void Enemy::sendToBattle(const std::vector<Vec2> &waypoints)
{
    m_wayPoints.setPoints(waypoints);
    setPosition(m_wayPoints.getcurPoint());
    
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

void Enemy::moveToNext(float dt)
{
    Direction lastDir = m_wayPoints.getDirection();
    if (!m_wayPoints.moveToNextPoint()) {
        unschedule(schedule_selector(Enemy::moveToNext));
        getParent()->removeChild(this);
        return;
    }
    
    if (lastDir == m_wayPoints.getDirection()) {
        return;
    }
    
    switch (m_wayPoints.getDirection()) {
        case Direction_Down:
        {
            walkingDown();
        }
        break;
        case Direction_Up:
        {
            walkingUp();
        }
        break;
        case Direction_Left:
        {
            walkingLeft();
        }
        break;
        case Direction_Right:
        {
            walkingRight();
        }
        break;
        default:
        break;
    }
}