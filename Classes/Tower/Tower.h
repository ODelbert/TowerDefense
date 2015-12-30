#ifndef __TowerDefense__tower__
#define __TowerDefense__tower__
#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC;

class TowerSlot;
class Shooter;

class Tower : public Node
{
public:
    struct TowerData
    {
        int maxDamage;
        int minDagamge;
        int range; // pix
        int fireRate; // attack rate pre second
        int weapon;
    };
public:

    CC_SYNTHESIZE_READONLY(TowerID, m_id, Id);
    CC_SYNTHESIZE(std::string, m_name, name);
    CC_SYNTHESIZE(int, m_damageMin, damageMin);
    CC_SYNTHESIZE(int, m_damageMax, damageMax);
    CC_SYNTHESIZE(int, m_fireRate, fireRate);
    CC_SYNTHESIZE(int, m_range, range);
    CC_SYNTHESIZE(WeaponType, m_weapon, weapon);

    CC_SYNTHESIZE(uint, m_costGold, costGold);
    CC_SYNTHESIZE(uint, m_upgradeGold, upgradeGold);
    
    virtual void shoot() {}
    virtual void upgrade() {};
    virtual void updateState() {};
    virtual int sell();
    virtual void showTowerInfo();
    virtual void detectNearBy();

    void initWithTowerId(TowerID id, TowerLevel level);

    bool isLimitTechnology() const;
    void setLimitTechnology(TowerLevel level);

private:
    Sprite* m_texture;
    TowerLevel m_level;
    TowerLevel m_limitLevel;
    std::vector<Shooter*> m_shooters;
};

#endif
