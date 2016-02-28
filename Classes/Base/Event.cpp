#include "Event.h"
#include "Tower/Tower.h"
#include "Enemy/Enemy.h"

TDEvent::TDEvent(const std::string& listnerId, EventActionType action)
    : EventCustom(listnerId),
    m_action(action) {}

EventActionType TDEvent::getEventActionType()
{
    return m_action;
}

void TDEvent::setEventAction(EventActionType type)
{
    
}

WaveEvent::WaveEvent()
    : TDEvent(EVENT_WAVE, EventActionType_Wave) {}

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

TowerEvent::TowerEvent(Tower* tower, int slotId)
   : TDEvent(EVENT_TOWER, EventActionType_INVALID),
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

