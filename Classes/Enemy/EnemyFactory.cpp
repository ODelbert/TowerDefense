//
//  EnemyFactory.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/30.
//
//

#include "EnemyFactory.h"
#include "CommonEnemy.h"
#include "TalentedEnemy.h"
#include "FlyingEnemy.h"
#include "RunningEnemy.h"

#define ENEMY_FACTORY_CREATE(monster) \
    case EnemyID_##monster: \
        return monster::create(); \
        break; \

Enemy* EnemyFactory::create(EnemyID id)
{
    switch (id) {
        ENEMY_FACTORY_CREATE(Bandersnatch)
        ENEMY_FACTORY_CREATE(BloodServant)
        ENEMY_FACTORY_CREATE(BloodsydianGnoll)
        ENEMY_FACTORY_CREATE(BloodsydianWarlock)
        ENEMY_FACTORY_CREATE(Zealot)
        ENEMY_FACTORY_CREATE(Dark_Spitters)
        ENEMY_FACTORY_CREATE(Drider)
        ENEMY_FACTORY_CREATE(Ettin)
        ENEMY_FACTORY_CREATE(Gloomy)
        ENEMY_FACTORY_CREATE(Gnoll_Blighter)
        ENEMY_FACTORY_CREATE(Gnoll_Burner)
        ENEMY_FACTORY_CREATE(Gnoll_Gnawer)
        ENEMY_FACTORY_CREATE(Gnoll_Reaver)
        ENEMY_FACTORY_CREATE(Gollem)
        ENEMY_FACTORY_CREATE(Grim_Devourers)
        ENEMY_FACTORY_CREATE(Harraser)
        ENEMY_FACTORY_CREATE(Hyena)
        ENEMY_FACTORY_CREATE(Mantaray)
        ENEMY_FACTORY_CREATE(MountedAvenger)
        ENEMY_FACTORY_CREATE(Ogre_Mage)
        ENEMY_FACTORY_CREATE(Perython)
        ENEMY_FACTORY_CREATE(Razorboar)
        ENEMY_FACTORY_CREATE(Redcap)
        ENEMY_FACTORY_CREATE(Satyr)
        ENEMY_FACTORY_CREATE(Scourger)
        ENEMY_FACTORY_CREATE(Screecher_Bat)
        ENEMY_FACTORY_CREATE(Shadow_Champion)
        ENEMY_FACTORY_CREATE(Shadow_Spawn)
        ENEMY_FACTORY_CREATE(Son_Of_Mactans)
        ENEMY_FACTORY_CREATE(Sword_Spider)
        ENEMY_FACTORY_CREATE(Twilight_Avenger)
        ENEMY_FACTORY_CREATE(Twilight_Evoker)
        ENEMY_FACTORY_CREATE(Twilight_Heretic)
        ENEMY_FACTORY_CREATE(WebspitterSpider)
        ENEMY_FACTORY_CREATE(FungusRider)
        ENEMY_FACTORY_CREATE(FungusRider_Medium)
        ENEMY_FACTORY_CREATE(FungusRider_Small)
        ENEMY_FACTORY_CREATE(Arachnomancer)
        ENEMY_FACTORY_CREATE(Arachnomancer_Spider)
        default:
            break;
    }

    return NULL;
}