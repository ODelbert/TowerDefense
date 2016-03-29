//
//  ResourceManager.cpp
//  TowerDefense
//
//  Created by jowu on 15/11/6.
//
//

#include "ResourceManager.h"
#include "CommonDef.h"
#include "PListReader.h"
#include "AnimationManager.h"

static const std::string BigImagePlist[] =
{
    // cat log | awk '{print $9}' | sed 's/png/plist\"\,/g' | sed 's/^/\"&/g'
    "bittering_content-hd.plist",
    "common_spritesheet_16_a_2-hd.plist",
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
    "map_spritesheet_32_3-hd.plist",
    "metropolis_content-hd.plist",
    "metropolis_content_2-hd.plist",
    "woods_content-hd.plist",
    "ingame_gui-hd.plist",    "elves_towers-hd.plist",
    "elves_towers_2-hd.plist"
    
};

static const std::string ImageAnimationPlist[] =
{
    
    // tower
    "elves_towers-hd.plist",
    "elves_towers_2-hd.plist",
    
    // enemy
    "elves_bittering_rancor_2_enemies-hd.plist",
    "elves_bittering_rancor_2_enemies-ipadhd.plist",
    "elves_bittering_rancor_2_enemies.plist",
    "elves_bittering_rancor_enemies-hd.plist",
    "elves_faerie_grove_enemies-hd.plist",
    "elves_faerie_grove_enemies_2-hd.plist",
    "elves_forgotten_enemies-hd.plist",
    "elves_hulking_rage_2_enemies-hd.plist",
    "elves_hulking_rage_enemies-hd.plist",
    "elves_metropolis_enemies-hd.plist",
    "elves_metropolis_enemies_2-hd.plist",
    "elves_woods_2_enemies-hd.plist",
    "elves_woods_enemies-hd.plist",
    
    // hero
    "elves_hero_alleria-hd.plist",
    "elves_hero_archer-hd.plist",
    "elves_hero_bolverk-hd.plist",
    "elves_hero_bravebark-hd.plist",
    "elves_hero_bravebark_2-hd.plist",
    "elves_hero_bruce-hd.plist",
    "elves_hero_denas-hd.plist",
    "elves_hero_durax-hd.plist",
    "elves_hero_eldritch-hd.plist",
    "elves_hero_elementalist-hd.plist",
    "elves_hero_fallenangel-hd.plist",
    "elves_hero_fallenangel_2-hd.plist",
    "elves_hero_faustus-hd.plist",
    "elves_hero_faustus_2-hd.plist",
    "elves_hero_gyro-hd.plist",
    "elves_hero_gyro_2-hd.plist",
    "elves_hero_gyro_3-hd.plist",
    "elves_hero_lynn-hd.plist",
    "elves_hero_panda-hd.plist",
    "elves_hero_panda_2-hd.plist",
    "elves_hero_phoenix-hd.plist",
    "elves_hero_phoenix_2-hd.plist",
    "elves_hero_pixie-hd.plist",
    "elves_hero_pixie_2-hd.plist",
    "elves_hero_rag-hd.plist",
    "elves_hero_veznan-hd.plist",
    "elves_hero_veznan_2-hd.plist",
    "gui_menu_sprite_heroic_32-hd.plist",
    
    // boss
    
    
    // others
    "gryphon_proy.plist",
};

static const std::string AnimationNamePlist[] =
{
    // tower
    "elves_towers_animations.plist",
    "tower_rock_thrower_entwood_animations.plist",
    "archer_arcane_shooter_animations.plist",
    "archer_silver_shooter_animations.plist",
    "tower_archer_arcane_animations.plist",
    "tower_archer_silver_animations.plist",
    
    "mage_highElven_balls_animations.plist",
    "mage_highElven_balls_proy_animations.plist",
    "mage_highElven_energyBall_animations.plist",
    "mage_highElven_proyBig_animations.plist",
    "mage_highElven_proy_animations.plist",
    "mage_highElven_shooter_animations.plist",
    "mage_tower_shooter_animations.plist",
    "mage_towers_animations.plist",
    "mage_wild_creepFx_animations.plist",
    "mage_wild_explosion_animations.plist",
    "mage_wild_proy_animations.plist",
    "mage_wild_ray_animations.plist",
    "mage_wild_shooter_animations.plist",
    
    "artillery_henge_bear_animations.plist",
    "artillery_henge_druid1_animations.plist",
    "artillery_henge_effects_animations.plist",
    "artillery_thrower_animations.plist",
    "artillery_thrower_lvl2_animations.plist",
    "artillery_thrower_lvl3_animations.plist",
    "artillery_tree_scorched_animations.plist",
    
    "soldiers_blade_singer_animations.plist",
    "soldiers_forest_keeper_animations.plist",
    "forestKeeper_roots_animations.plist",
    "forestKeeper_roots2_animations.plist",
    
    // enemy
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
    "webspitterSpider_web_animations.plist",
    "mountedAvenger_animations.plist",
    "shadow_champion_animations.plist",
    "shadow_spawn_animations.plist",
    "bandersnatch_spines_blood_animations.plist",
    "bandersnatch_spines_animations.plist",
    "rabbit_animations.plist",
    
    // hero
    "archer_hero_animations.plist",
    "bravebark_hero_animations.plist",
    "bravebark_hero_effects_animations.plist",
    "bravebark_hero_mignon_animations.plist",
    "denas_hero_guard_animations.plist",
    "elves_hero_alleria_animations.plist",
    "elves_hero_alleria_wildcat_animations.plist",
    "elves_hero_arivan_animations.plist",
    "elves_hero_arivan_lightning_animations.plist",
    "elves_hero_bolverk_animations.plist",
    "elves_hero_bruce_animations.plist",
    "elves_hero_bruce_ultimate_animations.plist",
    "elves_hero_bruce_ultimate_twister_animations.plist",
    "elves_hero_denas_animations.plist",
    "elves_hero_durax_animations.plist",
    "elves_hero_eldritch_animations.plist",
    "elves_hero_fallen_angel_animations.plist",
    "elves_hero_faustus_animations.plist",
    "elves_hero_faustus_extra_animations.plist",
    "elves_hero_gyro_animations.plist",
    "elves_hero_lynn_animations.plist",
    "elves_hero_malik_animations.plist",
    "elves_hero_panda_animations.plist",
    "elves_hero_panda_shadow_animations.plist",
    "elves_hero_panda_teleport_animations.plist",
    "elves_hero_phoenix_animations.plist",
    "elves_hero_pixie_animations.plist",
    "elves_hero_rag_animations.plist",
    "elves_hero_rag_polymorph_animations.plist",
    "elves_hero_veznan_animations.plist",
    "elves_hero_veznan_shackles_big_animations.plist",
    "elves_hero_veznan_shackles_small_animations.plist",
    "elves_hero_veznan_soulBurn_animations.plist",
    "elves_hero_veznan_soulBurn_big_animations.plist",
    "elves_hero_veznan_soulBurn_small_animations.plist",
    "fallen_angel_hero_infernal_base_decal_animations.plist",
    "fallen_angel_hero_infernal_base_fireIn_animations.plist",
    "fallen_angel_hero_infernal_decal_animations.plist",
    "fallen_angel_hero_infernal_fx_animations.plist",
    "fallen_angel_hero_reapers_harvest_decal_animations.plist",
    "fallen_angel_hero_soul_eater_ball_animations.plist",
    "fallen_angel_hero_soul_eater_decal_animations.plist",
    "fallen_angel_hero_soul_eater_explosion_animations.plist",
    "fallen_angel_hero_ultimate_angel_animations.plist",
    "lynn_hero_despair_fx_above_animations.plist",
    "lynn_hero_despair_fx_decal_animations.plist",
    "lynn_hero_ultimate_fx_above_animations.plist",
    "lynn_hero_ultimate_fx_decal_animations.plist",
    "lynn_hero_ultimate_fx_over_animations.plist",
    "lynn_hero_weakening_fx_above_animations.plist",
    "lynn_hero_weakening_fx_decal_animations.plist",
    
    // boss
    "bajnimen_boss_animations.plist",
    "bossHiena_animations.plist",
    "boss_ainyl_animations.plist",
    "boss_ainyl_block_decal_animations.plist",
    "boss_ainyl_block_end_animations.plist",
    "boss_ainyl_block_fx_animations.plist",
    "boss_ainyl_shield_big_animations.plist",
    "boss_ainyl_shield_small_animations.plist",
    "boss_drow_queen_animations.plist",
    "boss_drow_queen_portals_animations.plist",
    "boss_drow_queen_zealot_animations.plist",
    "boss_gnoll_animations.plist",
    "boss_godieth_acidPool_animations.plist",
    "boss_godieth_acidPool_bubble_animations.plist",
    "boss_godieth_acidPool_splash_animations.plist",
    "boss_godieth_animations.plist",
    "boss_godieth_spit_animations.plist",
    "boss_spider_animations.plist",
    "boss_spider_net_animations.plist",
    "miniboss_gnoll_animations.plist",
    "stage15_bossDecal_demon_animations.plist"
    
};

ResourceManager::ResourceManager()
{
    
}

bool ResourceManager::initialize()
{
    for (int i = 0; i < sizeof(BigImagePlist)/sizeof(BigImagePlist[0]); ++i) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BigImagePlist[i]);
    }
    
    for (int i = 0; i < sizeof(ImageAnimationPlist)/sizeof(ImageAnimationPlist[0]); ++i) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ImageAnimationPlist[i]);
    }
    
#ifndef TD_TEST
    PListReader::getInstance()->extractAnimationFromResource();
    

    
    for (int i = 0; i < sizeof(AnimationNamePlist)/sizeof(AnimationNamePlist[0]); ++i) {
        PListReader::getInstance()->createAnimationWithPlist(AnimationNamePlist[i]);
    }
#endif
    
    AM->initialize();
    
    return true;
}
