#ifndef __TowerDefense__tower__
#define __TowerDefense__tower__
#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;

class TowerSlot;
class Shooter;

struct TowerInfo
{
    int seq;
    int id;
    int level;
    char name[24];
    int dmgMin;
    int dmgMax;
    int range; // pix
    int fireRate; // attack rate pre second
    int weapon;
    int gold;
    int upgradeGold;
};

class Tower : public Node
{
public:
    CC_SYNTHESIZE_READONLY(TowerID, m_id, Id);
    CC_SYNTHESIZE(TowerLevel, m_level, Level);
    CC_SYNTHESIZE(TowerType, m_type, Type);
    CC_SYNTHESIZE(std::string, m_name, Name);
    CC_SYNTHESIZE(int, m_damageMin, DamageMin);
    CC_SYNTHESIZE(int, m_damageMax, DamageMax);
    CC_SYNTHESIZE(int, m_fireRate, FireRate);
    CC_SYNTHESIZE(int, m_range, Range);
    CC_SYNTHESIZE(WeaponType, m_weapon, Weapon);

    CC_SYNTHESIZE(uint, m_costGold, CostGold);
    CC_SYNTHESIZE(uint, m_upgradeGold, UpgradeGold);
    CC_SYNTHESIZE(TowerLevel, m_limitLevel, LimitLevel);

    virtual void shoot() {}
    virtual void upgrade(int tid = -1) {}
    virtual void updateState() {}
    virtual int sell();
    virtual void showTowerInfo();
    virtual void detectNearBy();

    void initWithTowerId(TowerID id, TowerLevel level);

protected:
    Sprite* m_texture;
    std::vector<Shooter*> m_shooters;
};

#endif
