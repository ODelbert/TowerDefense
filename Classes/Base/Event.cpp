#include "Event.h"
#include "Tower/Tower.h"
#include "Enemy/Enemy.h"

TDEvent::TDEvent(TDEventType action)
    : EventCustom("TDEvent"),
    m_action(action) {}

TDEventType TDEvent::getTDEventType()
{
    return m_action;
}

void TDEvent::setEventAction(TDEventType action)
{
    m_action = action;
}

WaveEvent::WaveEvent()
    : TDEvent(TDEventType_Wave) {}

int WaveEvent::getEnemyId() const
{
    return m_eId;
}

int WaveEvent::getPathIndex() const
{
    return m_path;
}

int WaveEvent::getSubPathIndex() const
{
    return m_subPath;
}

void WaveEvent::setWaveData(int eId, int path, int subpath)
{
    m_eId = eId;
    m_path = path;
    m_subPath = subpath;
}

TowerEvent::TowerEvent(Tower* tower, int slotId, TDEventType action)
   : TDEvent(action),
    m_tower(tower),
    m_slotId(slotId) {}

Tower* TowerEvent::getTower() const
{
    return m_tower;
}

int TowerEvent::getSlotId() const
{
    return m_slotId;
}

BulletEvent::BulletEvent(Bullet* bullet, TDEventType action)
    : TDEvent(action),
    m_bullet(bullet)
{}


