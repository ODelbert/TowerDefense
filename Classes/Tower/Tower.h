#include "cocos2d.h"
#include "CommonDef.h"

USING_NS_CC:

enum TowerLevel
{
    TowerLevel_1 = 1,
    TowerLevel_2 = 2,
    TowerLevel_3 = 3,
    TowerLevel_4 = 4,
};

class Shooter : public Node
{
public:
   void createShooter(TowerID id);
   virtual bool init();

private:
    Direction m_dir;
    Sprite* m_texture;
};

class TowerSlot;

class Tower : public Sprite
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

    void initWithTowerId(TowerID id);

    void isLimitTechnology() const;
    void setLimitTechnology(TowerLevel level);

private:
    TowerSlot* m_slot;
    TowerLevel m_maxLevel;
};
