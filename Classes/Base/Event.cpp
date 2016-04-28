#include "Event.h"
#include "Tower/Tower.h"
#include "Enemy/Enemy.h"

TDEvent::TDEvent(TDEventType type)
    : EventCustom("TDEvent"),
    m_eventType(type)
{}

WaveEvent::WaveEvent(Command cmd, int eid, int path, int subpath, int waveIdx, int spawnIdx)
    : TDEvent(TDEventType_Wave),
      m_command(cmd),
      m_path(path),
      m_subPath(subPath),
      m_waveIdx(waveIdx),
      m_spawnIdx(spawnIdx)
{}

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
      m_waveIdx(waveIdx)
{}

BulletEvent::BulletEvent(Command cmd, int slotId, Vec2 destination)
    : TDEvent(TDEventType_Bullet),
      m_command(cmd),
      m_slotId(slotId),
      m_destination(destination)
{}
