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

int WaveEvent::getIndex() const
{
    return m_index;
}

void WaveEvent::setWaveData(int eId, int path, int subpath, int waveCount, int index)
{
    m_eId = eId;
    m_path = path;
    m_subPath = subpath;
    m_waveCount = waveCount;
    m_index = index;
}

TowerEvent::TowerEvent(Command cmd, int slotId, TowerID id, int tid)
   : TDEvent(TDEventType_Tower),
    m_command(cmd),
    m_slotId(slotId),
    m_towerId(id),
    m_technologyId(tid)
{}

EnemyEvent::EnemyEvent(Command cmd, EnemyID id, int tag, int waveIdx)
    : TDEvent(TDEventType_Enemy),
      m_command(cmd),
      m_id(id),
      m_tag(tag),
      m_waveIdx(waveIdx)
{}

BulletEvent::BulletEvent(Command cmd, int slotId, Vec2 destination)
    : TDEvent(TDEventType_Bullet),
      m_command(cmd),
      m_slotId(slotId),
      m_destination(destination)
{}
