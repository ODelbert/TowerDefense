#include "Tower.h"

class ArcherShooter : public Sprite
{
public:
   CREATE_FUNC(ArcherShooter);
   virtual bool init();

private:
    Direction m_dir;
    Node* m_texture;
};

class Archer : public Tower
{
public:
    static Archer* createArcherTower(TowerLevel level);
    virtual bool init();

    virtual void shoot();
    virtual void idel();

    virtual void updateState();
    
private:
    TowerLevel m_level;
    std::vector<ArcherShooter*> m_shooters;
};
