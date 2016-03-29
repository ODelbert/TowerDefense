#ifndef __TowerDefense__tower__
#define __TowerDefense__tower__
#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;

class TowerSlot;
class Shooter;

struct TowerInfo
{
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
    CC_SYNTHESIZE_READONLY(TowerID, m_id, Id)
    CC_SYNTHESIZE(TowerLevel, m_level, Level)
    CC_SYNTHESIZE(TowerType, m_type, Type)
    CC_SYNTHESIZE(std::string, m_name, Name)
    CC_SYNTHESIZE(int, m_damageMin, DamageMin)
    CC_SYNTHESIZE(int, m_damageMax, DamageMax)
    CC_SYNTHESIZE(int, m_fireRate, FireRate)
    CC_SYNTHESIZE(int, m_range, Range)
    CC_SYNTHESIZE(WeaponType, m_weapon, Weapon)

    CC_SYNTHESIZE(uint, m_costGold, CostGold)
    CC_SYNTHESIZE(uint, m_UpgradeGold, UpgradeGold)
    CC_SYNTHESIZE(uint, m_t1Gold, T1Gold)
    CC_SYNTHESIZE(uint, m_t2Gold, T2Gold)
    CC_SYNTHESIZE(uint, m_t3Gold, T3Gold)
    CC_SYNTHESIZE(TowerLevel, m_limitLevel, LimitLevel)

    virtual void shoot() {}
    virtual void updateState() {}
    virtual void detectNearBy();

    void initWithTowerId(TowerID id);
    int getTechnologyRank(int tid);
    void upgradeTechnology(int tid);

protected:
    Tower();

protected:
    Sprite* m_texture;
    std::vector<Shooter*> m_shooters;
    uint m_technologyMask;
};

#endif
