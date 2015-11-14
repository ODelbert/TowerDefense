//
//  ResourceManager.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/6.
//
//

#include "ResourceManager.h"
#include "CommonDef.h"




static const std::string BigImagePlist[] =
{
    // cat log | awk '{print $9}' | sed 's/png/plist\"\,/g' | sed 's/^/\"&/g'
    "bittering_content-hd.plist",
    "common_spritesheet_16_na-hd.plist",
    "common_spritesheet_16_na_2_IPAD2-hd.plist",
    "common_spritesheet_16_na_2_IPAD2_5-hd.plist",
    "common_spritesheet_32-hd.plist",
    "common_spritesheet_localized_32-hd.plist",
    "common_spritesheet_localized_32_cn-hd.plist",
    "credits_scene-hd.plist",
    "ending_scene-hd.plist",
    "faerie_content-hd.plist",
    "faerie_content_2-hd.plist",
    "fps_images.plist",
    "gui_menu_sprite_endless_32-hd.plist",
    "hulking_rage_content-hd.plist",
    "inaps_gemParticle_0001.plist",
    "ingame_gui-hd.plist",
    "mainmenu_spritesheet_32_1-hd.plist",
    "mainmenu_spritesheet_32_2-hd.plist",
    "map_spritesheet_16_a_3-hd.plist",
    "map_spritesheet_16_na-hd.plist",
    "map_spritesheet_32-hd.plist",
    "map_spritesheet_32_2-hd.plist",
    "map_spritesheet_32_3-hd.plist"
    "metropolis_content-hd.plist",
    "metropolis_content_2-hd.plist",
    "woods_content-hd.plist",
    "ingame_gui-hd.plist"
};

static const std::string ImageAnimationPlist[] =
{
    "elves_bittering_rancor_2_enemies-hd.plist",
    "elves_bittering_rancor_2_enemies-ipadhd.plist",
    "elves_bittering_rancor_2_enemies.plist",
    "elves_bittering_rancor_enemies-hd.plist",
    "elves_faerie_grove_enemies-hd.plist",
    "elves_faerie_grove_enemies_2-hd.plist",
    "elves_hulking_rage_2_enemies-hd.plist",
    "elves_hulking_rage_enemies-hd.plist",
    "elves_metropolis_enemies-hd.plist",
    "elves_metropolis_enemies_2-hd.plist",
    "elves_woods_2_enemies-hd.plist",
    "elves_woods_enemies-hd.plist"
};

static const std::string AnimationNamePlist[] =
{
    "ewok_animations.plist",
    "hyena_animations.plist",
    "knocker_animations.plist",
    
    "mactans_malicia_animations.plist",
    "malicia_animations.plist",
    
    "mantaray_animations.plist",
    "ogre_mage_animations.plist",
    "ogre_mage_aura_animations.plist",
    "ogre_mage_proy_animations.plist",
    "ogre_mage_shield_animations.plist",
    "perython_animations.plist",
    "perython_rockthrower_animations.plist",
    "arachnomancer_animations.plist",
    "arachnomancer_miniSpider_animations.plist",
    "arachnomancer_spider_animations.plist",
    "babyAshbite_animations.plist",
    "bandersnatch_animations.plist",
    "bandersnatch_spines_animations.plist",
    "bandersnatch_spines_blood_animations.plist",
    "bloodServant_animations.plist",
    "bloodsydianGnoll_animations.plist",
    "bloodsydianWarlock_animations.plist",
    "dark_spitters_animations.plist",
    "dark_spitters_proy_animations.plist",
    "drider_animations.plist",
    "elves_enemies_bittering_rancor_animations.plist",
    "elves_enemies_endless2_animations.plist",
    "elves_enemies_endless_animations.plist",
    "elves_enemies_faerie_grove_animations.plist",
    "elves_enemies_forgotten_animations.plist",
    "elves_enemies_hulking_rage_animations.plist",
    "elves_enemies_metropolis_animations.plist",
    "elves_enemies_woods_animations.plist",
    "ettin_animations.plist",
    "fungusRider_animations.plist",
    "fungusRider_medium_animations.plist",
    "fungusRider_small_animations.plist",
    "gloomy_animations.plist",
    "gnollBush_animations.plist",
    "gnoll_blighter_animations.plist",
    "gnoll_blighter_energy_animations.plist",
    "gnoll_blighter_proy_animations.plist",
    "gnoll_burner_animations.plist",
    "gnoll_burner_proy_animations.plist",
    "gnoll_gnawer_animations.plist",
    "gnoll_reaver_animations.plist",
    "gollem_animations.plist",
    "grim_devourers_animations.plist",
    "harraser_animations.plist",
    "razorboar_animations.plist",
    "redcap_animations.plist",
    "satyrHoplite_animations.plist",
    "satyr_animations.plist",
    "scourger_animations.plist",
    "scourger_shadow_animations.plist",
    "screecher_bat_animations.plist",
    "screecher_bat_stun_animations.plist",
    "shadow_champion_animations.plist",
    "shadow_spawn_animations.plist",
    "son_of_mactans_animations.plist",
    "son_of_mactans_particles_animations.plist",
    "spiderQueen_layer_animations.plist",
    "sword_spider_animations.plist",
    "tarantula_animations.plist",
    "theBeheader_animations.plist",
    "twilight_avenger_animations.plist",
    "twilight_avenger_effect_big_animations.plist",
    "twilight_avenger_effect_small_animations.plist",
    "twilight_avenger_explosion_animations.plist",
    "twilight_bannerbearer_animations.plist",
    "twilight_bannerbearer_aura_animations.plist",
    "twilight_bannerbearer_enemy_aura_animations.plist",
    "twilight_evoker_animations.plist",
    "twilight_heretic_animations.plist",
    "webspitterSpider_animations.plist",
    "webspitterSpider_web_animations.plist"
};




SINGLETON_IMPL(ResourceManager);

bool ResourceManager::initialize()
{
    for (int i = 0; i < sizeof(BigImagePlist)/sizeof(BigImagePlist[0]); ++i) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BigImagePlist[i]);
    }
    
    for (int i = 0; i < sizeof(ImageAnimationPlist)/sizeof(ImageAnimationPlist[0]); ++i) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ImageAnimationPlist[i]);
    }
    
    return true;
}
