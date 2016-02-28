#include "EventListener.h"
#inlcude "EventHandler.h"

TDEventListener* TDEventListener::create()
{
    TDEventListener* ret = new TDEventListener;
    if (ret && ret->init(EventListener::Type::CUSTOM, EventHandler::onEvent))
    {
        ret->autorelease();
        return ret;
    }
    else {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}