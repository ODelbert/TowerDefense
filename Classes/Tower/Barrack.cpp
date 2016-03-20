
#include "Barrack.h"

Barrack* Barrack::create(TowerLevel level)
{
    Barrack* ret = new Barrack;
    if (ret && ret->init(level)) {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Barrack::init(TowerLevel level)
{
    switch (level) {
        case TowerLevel_1:
            initWithTowerId(TowerID_Barrack_Lv1, level);
            break;
        case TowerLevel_2:
            initWithTowerId(TowerID_Barrack_Lv2, level);
            break;
        case TowerLevel_3:
            initWithTowerId(TowerID_Barrack_Lv3, level);
            break;
        default:
            break;
    }
    
    return true;
}

bool ForesetKeeperHub::init()
{
    return true;
}

bool BladeSingerHall::init()
{
    return true;
}