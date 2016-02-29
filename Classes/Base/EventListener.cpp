#include "EventListener.h"


TDEventListener* TDEventListener::create()
{
    TDEventListener* ret = new TDEventListener;
    if (ret && ret->init(EventListener::Type::CUSTOM, "TDEvent", nullptr))
    {
        ret->autorelease();
        return ret;
    }
    else {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

TDEventListener::TDEventListener()
    : onWaveEvent(nullptr),
    onTowerEvent(nullptr),
    onBulletEvent(nullptr)
{}

bool TDEventListener::checkAvailable()
{
    return true;
}

EventListener* TDEventListener::clone()
{
    return nullptr;
}