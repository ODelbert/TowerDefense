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
#include "Configuration/GameData.h"
#include "Sprite/LifeBar.h"

USING_NS_CC;

#define RADIAN_TO_DEGREE(x) (x) < 0 ? (360 + 57.2958*(x)) : (57.2958*(x))

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
    if (m_pathIndex >= m_points.size() - 1) {
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

float WayPoints::fulfilledPercent() const
{
    if (m_points.empty()) return 0;
    return m_pathIndex / m_points.size();
}

bool Enemy::initWithEnemyId(EnemyID id)
{
    EnemyInfo info = s_enemiesInfo[static_cast<int>(id - EnemyID_Gnoll_Reaver)];
    log("---->%d", id);
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
    m_texture = Sprite::createWithSpriteFrameName(m_name + "_0001.png");
    addChild(m_texture);
    m_lifeBar = LifeBar::create(m_texture);

    return true;
}

void Enemy::sendToBattle(const std::vector<Vec2> &waypoints)
{
    if (waypoints.empty()) {
        return;
    }
    
    m_state = EnemyState_WalkNext;
    m_wayPoints.setPoints(waypoints);
    setPosition(m_wayPoints.getcurPoint());
    moveToNext();
}

float Enemy::fulfilledPercent() const
{
    return m_wayPoints.fulfilledPercent();
}

void Enemy::idle()
{
    m_texture->runAction(Animate::create(AM->getAnimation((m_name + "_idle"))));
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_Idle);
}

void Enemy::walkingLeft()
{
    m_texture->setFlippedX(true);
    m_texture->runAction(Animate::create(AM->getAnimation((m_name + "_walkingRightLeft"))));
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_WalkingRightLeft);
}

void Enemy::walkingRight()
{
    m_texture->runAction(Animate::create(AM->getAnimation((m_name + "_walkingRightLeft"))));
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_WalkingRightLeft);
}

void Enemy::walkingDown()
{
    m_texture->runAction(Animate::create(AM->getAnimation((m_name + "_walkingDown"))));
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_WalkingDown);
}

void Enemy::walkingUp()
{
    m_texture->runAction(Animate::create(AM->getAnimation((m_name + "_walkingUp"))));
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_WalkingUp);
}

void Enemy::runningLeft()
{
    m_texture->setFlippedX(true);
    m_texture->runAction(Animate::create(AM->getAnimation((m_name + "_runningRightLeft"))));
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_RunningRightLeft);
}

void Enemy::runningRight()
{
    m_texture->runAction(Animate::create(AM->getAnimation((m_name + "_runningRightLeft"))));
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_RunningRightLeft);
}

void Enemy::runningDown()
{
    m_texture->runAction(Animate::create(AM->getAnimation((m_name + "_runningDown"))));
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_RunningDown);
}

void Enemy::runningUp()
{
    m_texture->runAction(Animate::create(AM->getAnimation((m_name + "_runningUp"))));
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_RunningUp);
}

void Enemy::death()
{
    m_texture->runAction(Animate::create(AM->getAnimation((m_name + "_death"))));
    //GM->removeEnemy(this);
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_Death);
}

void Enemy::spawn()
{
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_Spawn);
}

void Enemy::respawn()
{
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_Respawn);
}

void Enemy::shoot()
{
    m_texture->runAction(Animate::create(AM->getAnimation((m_name + "_shoot"))));
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_Shoot);
}

void Enemy::cast()
{
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_Cast);
}

void Enemy::speicialAttack()
{
    //AnimationManager::getInstance()->runAction(m_texture, AnimationType_Enemy, static_cast<int>(m_id), ActionEnemy_Special);
}

void Enemy::getHurt(int dmg)
{
    m_life -= dmg;
    if (m_life <= 0) {
        death();
    }

    m_lifeBar->setPercentage(m_life / m_maxLife);
}

void Enemy::updateState(float dt)
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

        runAction(Sequence::create(MoveTo::create(0.025 *(SpeedType_VeryFast - m_speed + 1), m_wayPoints.getcurPoint())
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
