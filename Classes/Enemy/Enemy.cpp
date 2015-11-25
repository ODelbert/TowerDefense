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
    
    m_state = EnemyState_Invalid;
    m_buffs = 0;
    m_debuffs = 0;
    m_direction = Direction_Invalid;
    return true;
}

void Enemy::sendToBattle(const std::vector<Vec2> &waypoints)
{
    if (waypoints.size() <= 1) return;
    
    m_waypoints = waypoints;
    
    
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
    switch (m_state) {
        case EnemyState_WalkLeft:
        case EnemyState_WalkRight:
        case EnemyState_WalkDown:
        case EnemyState_WalkUp:
        {
            if (m_waypoints.empty()) {
                unschedule(schedule_selector(Enemy::moveToNext));
                getParent()->removeChild(this);
                return;
            }
//            
//            Vec2 pos = m_path[m_pathIndex];
//            Vec2 nextPos = m_path[m_pathIndex + 1];
//            
//            // 120, offset of path_x
//            // 100, offset of path_y
//            setPosition(Vec2(s_rate * (nextPos.x + 120), s_rate * (nextPos.y + 100) + 59));
//            
//            float angle = atan2f(nextPos.y - pos.y, nextPos.x - pos.x) * 180 / 3.14;
//            
//            if (angle > -45 && angle <= 45) {
//                // right
//                if (s_lastDir == ActionTag_WalkingRight) return;
//                s_lastDir = ActionTag_WalkingRight;
//                AnimationManager::getInstance()->runAction(m_runningEnemy, EnemyID_Redcap, EnemyAction_Redcap_WalkingRightLeft);
//            }
//            else if (angle > 45 && angle <= 135) {
//                // up
//                if (s_lastDir == ActionTag_WalkingUp) return;
//                s_lastDir = ActionTag_WalkingUp;
//                AnimationManager::getInstance()->runAction(m_runningEnemy, EnemyID_Redcap, EnemyAction_Redcap_WalkingUp);
//            }
//            else if (angle >=135 && angle <=225) {
//                // left
//                if (s_lastDir == ActionTag_WalkingLeft) return;
//                s_lastDir = ActionTag_WalkingLeft;
//                AnimationManager::getInstance()->runAction(m_runningEnemy, EnemyID_Redcap, EnemyAction_Redcap_WalkingRightLeft);
//                m_runningEnemy->setFlippedX(true);
//            }
//            else {
//                // down
//                if (s_lastDir == ActionTag_WalkingDown) return;
//                s_lastDir = ActionTag_WalkingDown;
//                AnimationManager::getInstance()->runAction(m_runningEnemy, EnemyID_Redcap, EnemyAction_Redcap_WalkingDown);
//            }
 
        }
            break;
        default:
            break;
    }
}