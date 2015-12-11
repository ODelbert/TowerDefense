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
#include "Animation/AnimationManager.h"

USING_NS_CC;

#define RADIAN_TO_DEGREE(x) (x) < 0 ? (360 + 57.2958*(x)) : (57.2958*(x))

enum ActionCommon
{
    ActionCommon_Attack = 0,
    ActionCommon_WalkingDown,
    ActionCommon_WalkingRightLeft,
	ActionCommon_WalkingUp,
    ActionCommon_Idle,
    ActionCommon_RunningDown,
    ActionCommon_RunningRightLeft,
	ActionCommon_RunningUp,
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
    if (m_pathIndex == 0) {
        return Direction_Invalid;
    }
    
    return m_dir;
}

bool WayPoints::moveToNextPoint()
{
    if (m_pathIndex >= m_points.size()) {
        return false;
    }
    
    float angle = RADIAN_TO_DEGREE(atan2f(m_points[m_pathIndex + 1].y - m_points[m_pathIndex].y, m_points[m_pathIndex + 1].x - m_points[m_pathIndex].x));
    if (angle > 315 && angle <= 45) {
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
    m_texture = Sprite::createWithSpriteFrameName("redcap_0001.png");
    addChild(m_texture);
    return true;
}

void Enemy::sendToBattle(const std::vector<Vec2> &waypoints)
{
    if (waypoints.empty()) {
        return;
    }
    
    m_wayPoints.setPoints(waypoints);
    setPosition(m_wayPoints.getcurPoint());
    moveToNext();
}

void Enemy::idle()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_Idle);
}

void Enemy::walkingLeft()
{
    m_texture->setFlippedX(true);
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_WalkingRightLeft);
}

void Enemy::walkingRight()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_WalkingRightLeft);
}

void Enemy::walkingDown()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_WalkingDown);
}

void Enemy::walkingUp()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_WalkingUp);
}

void Enemy::runningLeft()
{
    m_texture->setFlippedX(true);
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_WalkingRightLeft);
}

void Enemy::runningRight()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_WalkingRightLeft);
}

void Enemy::runningDown()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_WalkingDown);
}

void Enemy::runningUp()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_WalkingUp);
}

void Enemy::death()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_Death);
}

void Enemy::spawn()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_Spawn);
}

void Enemy::respawn()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_Respawn);
}

void Enemy::shoot()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_Shoot);
}

void Enemy::cast()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_Cast);
}

void Enemy::speicialAttack()
{
    AnimationManager::getInstance()->runAction(m_texture, static_cast<int>(m_id), ActionCommon_Special);
}

void Enemy::update(float dt)
{
	switch (m_state) {
	case EnemyState_Appear:
		spawn();
	break;
	case EnemyState_WalkNext:
	case EnemyState_RunningNext:
		moveToNext();
	break;
	case EnemyState_Dead:
		death();
	break;
	case EnemyState_AttackLeft:
		m_texture->setFlippedX(true);
	case EnemyState_AttackRight:
		attack();
	break;
	case EnemyState_CastSpellLeft:
		m_texture->setFlippedX(true);
	case EnemyState_CastSpellRight:
		cast();
	break;
	case EnemyState_SpeicalAttackLeft: {
		m_texture->setFlippedX(true);
		speicialAttack();
	}
	break;
	case EnemyState_SpeicalAttackRight:
		speicialAttack();
	break;
	case EnmeyState_Num:
	break;
	default:
		break;
	}
}

void Enemy::moveToNext()
{
	if (EnemyState_WalkNext == m_state || EnemyState_RunningNext == m_state) {
		Direction dir = m_wayPoints.getDirection();
		Vec2 pos = m_wayPoints.getcurPoint();
		if (!m_wayPoints.moveToNextPoint()) {
			getParent()->removeChild(this);
			return;
		}

		runAction(Sequence::create(MoveTo::create(pos.getDistance(m_wayPoints.getcurPoint()) / SPEED_RATE(m_speed), m_wayPoints.getcurPoint())
								   , CallFuncN::create(CC_CALLBACK_0(Enemy::moveToNext, this))
								   , NULL));

		if (dir == m_wayPoints.getDirection()) {
			return;
		}
		switch (m_wayPoints.getDirection()) {
			case Direction_Down:
			{
				EnemyState_WalkNext == m_state ? walkingDown() : runningDown();
			}
			break;
			case Direction_Up:
			{
				EnemyState_WalkNext == m_state ? walkingUp() : runningUp();
			}
			break;
			case Direction_Left:
			{
				EnemyState_WalkNext == m_state ? walkingLeft() : runningLeft();
			}
			break;
			case Direction_Right:
			{
				EnemyState_WalkNext == m_state ? walkingRight() : runningRight();
			}
			break;
			default:
			break;
		}
	}
}