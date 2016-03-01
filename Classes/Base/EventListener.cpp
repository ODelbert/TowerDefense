#include "EventListener.h"

TDEventListener* TDEventListener::create(const std::function<void(TDEvent*)>& callback)
{
    TDEventListener* ret = new TDEventListener;
    if (ret && ret->init("TDEvent", callback))
    {
        ret->autorelease();
        return ret;
    }
    else {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool TDEventListener::init(const ListenerID& listenerId, const std::function<void(TDEvent*)>& callback)
{
    bool ret = false;
    
    _onTDEvent = callback;
    
    auto listener = [this](Event* event){
        if (_onTDEvent != nullptr)
        {
            _onTDEvent(static_cast<TDEvent*>(event));
        }
    };
    
    if (EventListener::init(EventListener::Type::CUSTOM, listenerId, listener))
    {
        ret = true;
    }
    return ret;
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