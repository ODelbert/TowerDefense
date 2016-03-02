#include "Event.h"
#include "Tower/Tower.h"
#include "Enemy/Enemy.h"

TDEvent::TDEvent(TDEventType type)
    : EventCustom("TDEvent"),
    m_eventType(type)
{}

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

TowerEvent::TowerEvent(int slotId, Command cmd)
   : TDEvent(TDEventType_Tower),
    m_slotId(slotId) {}

BulletEvent::BulletEvent(Bullet* bullet, TDEventType action)
    : TDEvent(action),
    m_bullet(bullet)
{}


