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

int WaveEvent::waveCount() const
{
    return m_waveCount;
}

void WaveEvent::setWaveData(int eId, int path, int subpath, int waveCount)
{
    m_eId = eId;
    m_path = path;
    m_subPath = subpath;
    m_waveCount = waveCount;
}

TowerEvent::TowerEvent(Command cmd, int slotId, TowerID id, int tid)
   : TDEvent(TDEventType_Tower),
    m_command(cmd),
    m_slotId(slotId),
    m_towerId(id),
    m_technologyId(tid)
{}

BulletEvent::BulletEvent(Bullet* bullet, TDEventType action)
    : TDEvent(action),
    m_bullet(bullet)
{}

EnemyEvent::EnemyEvent(Command cmd, EnemyID id)
    : TDEvent(TDEventType_Enemy),
      m_command(cmd),
      m_id(id)
{}
