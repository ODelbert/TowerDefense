#include "PListReader.h"

#if (CC_PLATFORM_MAC == CC_TARGET_PLATFORM || CC_PLATFORM_IOS == CC_TARGET_PLATFORM || CC_PLATFORM_LINUX == CC_TARGET_PLATFORM)
#   include <sys/types.h>
#   include <dirent.h>
#   include <unistd.h>
#else
// TODO:win32
#endif

#include <algorithm>
#include "CommonDef.h"
#include "Animation/AnimationManager.h"

USING_NS_CC;

const std::string s_enemyName[] = {
    "arachnomancer_miniSpider",
    "arachnomancer_spider",
    "arachnomancer",
    "bandersnatch",
    "bloodServant",
    "bloodsydianGnoll",
    "bloodsydianWarlock",
    "zealot",
    "dark_spitters",
    "drider",
    "ettin",
    "fungusRider_medium",
    "fungusRider_small",
    "fungusRider",
    "gloomy",
    "gnoll_blighter",
    "gnoll_burner",
    "gnoll_gnawer",
    "gnoll_reaver",
    "gollem",
    "grim_devourers",
    "harraser",
    "hyena",
    "knocker",
    "mantaray",
    "gnollBerzerker",
    "mountedAvenger",
    "ogre_mage",
    "perython",
    "rabbit",
    "razorboar",
    "redcap",
    "satyrHoplite",
    "satyr",
    
    
    "scourger",
    "scourger_shadow",
    "screecher_bat",
    "shadow_champion",
    "shadow_spawn",
    "son_of_mactans",
    "sword_spider",
    "tarantula",
    "theBeheader",
    "twilight_avenger",
    "twilight_bannerbearer",
    "twilight_evoker",
    "twilight_heretic",
    "webspitterSpider"
};

const std::string s_allyName[] = {
    "catapult",
    "ewok",
    "reinforce_A0",
    "reinforce_A1",
    "reinforce_A2",
    "reinforce_A3",
    "reinforce_B0",
    "reinforce_B1",
    "reinforce_B2",
    "reinforce_B3",
    "reinforce_C0",
    "reinforce_C1",
    "reinforce_C2",
    "reinforce_C3",
};

const std::string s_bossName[] = {
    "bajnimen",
    "ainyl",
    "boss_godieth",
    "bossHiena",
    "drow_queen",
    "spiderQueen"
};
#define ddfdfaf 0x2323232
const std::string s_heroName[] = {
    "archer_hero", // 精灵游侠
    "bravebark", // 远古树人
    "alleria", // 精灵游侠实习生，有一只小黑猫
    "arivan", // 元素魔导师
    "bolverk", // ??? 未知英雄
    "bruce", // 金刚狮
    "denas", // 皇家战士
    "durax", // 冰晶元素
    "regson", // 恶魔猎手
    "fallen_angel", // 堕天使
    "faustus", // 蓝龙
    "lynn", // 巫毒术士
    "xin", // 熊猫
    "phoenix", // 凤凰
    "catha", // 精灵仙子
    "razzAndRaggs", // 布偶术士
    "veznan", // 黑暗术士
    "wilburg", // 炸弹人
    "malik", // 未知英雄，好像是吸血女荡妇
};

const std::string s_towerName[] = {
    "archer_arcane",
    "archer_silver",
    "artillery_henge",
    "artillery_thrower",
    "artillery_tree",
    "mage_highElven",
    "mage_wild",
    "mage_tower",
    "forestKeeper",
    "bladeSinger"
};

static void convertToCamelCase(std::string &str, const std::string prefix)
{
    if (str[0] >= 'a' && str[0] <= 'z')
        str[0] -= 32;
    int index = 0;
    while ((index = str.find("_", index)) != std::string::npos) {
        if (str[index + 1] >= 'a' && str[index + 1] <= 'z')
            str[index + 1] -= 32;
        ++index;
    }
    
    std::string tmp = prefix;
    tmp += str;
    str = tmp;
}

SINGLETON_IMPL(PListReader)
void PListReader::createAnimationWithPlist(const std::string &name)
{
    ValueMap root = FileUtils::getInstance()->getValueMapFromFile(name);
    if (root.empty()) {
        CCLOG("PListReader::createAnimationWithPlist failed to create with file [%s]", name.c_str());
        return;
    }
    
    ValueMap animationDict = root["animations"].asValueMap();
    ValueMap::const_iterator iter = animationDict.begin();
    while (iter != animationDict.end()) {
        ValueMap infoEntry = iter->second.asValueMap();
        Vector<SpriteFrame*> animFrames;
        int fromIndex = infoEntry["fromIndex"].asInt();
        int toIndex = infoEntry["toIndex"].asInt();
        std::string prefix = infoEntry["prefix"].asString();
        for (int i = fromIndex; i <= toIndex; ++i) {
            std::string format = prefix;
            if (100 > i) {
                format += "_00%02d.png";
            }
            else {
                format += "_0%03d.png";
            }
            
            auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat(format.c_str(),i)->getCString());
            if (frame) {
                animFrames.pushBack(frame);
            }
        }

        if (animFrames.empty()) {
            CCLOG("PListReader::createAnimationWithPlist animation %s with empty frames", iter->first.c_str());
        }
        
        // FIXME::tune parameter
        float animateRate = 0.002f * animFrames.size() < 0.05f ? 0.05f : 0.002f * animFrames.size();
        
        AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(animFrames, animateRate) , iter->first);
        ++iter;
    }
}

// path info
// 1d: path count
// 2d: subpath count
// 3d: path
std::vector<std::vector<std::vector<Vec2> > > PListReader::readPathPlist(int level)
{
    std::vector<std::vector<std::vector<Vec2> > > paths;
    std::string file = String::createWithFormat("level%d_paths.plist", level)->getCString();
    ValueMap root = FileUtils::getInstance()->getValueMapFromFile(String::createWithFormat("level%d_paths.plist", level)->getCString());
    ValueVector pathVec = root["paths"].asValueVector();
    for (int i = 0; i < pathVec.size(); ++i) {
        ValueMap subPathDict = pathVec[i].asValueMap();
        ValueVector subPathsVec = subPathDict["subpaths"].asValueVector();
        std::vector<std::vector<Vec2> > subPaths;
        for (int j = 0; j < subPathsVec.size(); ++j) {
            ValueVector pathVec = subPathsVec[j].asValueVector();
            std::vector<Vec2> path;
            const float s_offsetX = 12.f; // 基于地图的偏移
            const float s_offsetY = 73.f;
            const float s_scaleX = 1.15f; // 横向纵向比率
            const float s_scaleY = 1.13f;
            const float s_rangeOut = 20.0f; // 超出范围的路径去除
            for (int k = 0; k < pathVec.size(); ++k) {
                ValueMap posMap = pathVec[k].asValueMap();
                Vec2 pos;
                pos.x = posMap["x"].asFloat() * s_scaleX + s_offsetX;
                pos.y = posMap["y"].asFloat() * s_scaleY + s_offsetY;
                if (pos.x < -s_rangeOut || pos.x >= MAP_WIDTH + s_rangeOut || pos.y < s_rangeOut || pos.y >= MAP_HEIGHT + s_rangeOut) {
                    continue;
                }
                path.push_back(pos);
            }
            
            subPaths.push_back(path);
            
        }
        
        paths.push_back(subPaths);
    }
    
#ifdef TD_DEBUG
    for (int i = 0 ; i < paths.size(); ++i) {
        std::vector<std::vector<Vec2> > subpath = paths[i];
        for (int j = 0; j < subpath.size(); ++j) {
            std::vector<Vec2> path = subpath[j];
            for (int k = 0; k < path.size(); ++k) {
                CCLOG("PlistReader::readPath pathIndex[%d] subpathIndex [%d] at [%d] ====[%f %f]",
                      i, j, k, path[k].x, path[k].y);
            }
            
        }
    }
#endif
    
    return paths;
}

void PListReader::extractAnimationFromResource()
{
    typedef struct _Tag
    {
        AnimationType type;
        std::string prefix;
        std::vector<std::string> actions;
        
        void show() {
            std::string str = prefix;
            str += "----";
            for (int i = 0; i < actions.size(); ++i) {
                str += actions[i];
                str += "/";
            }
            
            log("tag info : %s", str.c_str());
        }
    } Tag;
    
    std::vector<Tag> tags;
    
    std::vector<std::string> enemyTag;
    std::vector<std::string> towerTag;
    std::vector<std::string> heroTag;
    std::vector<std::string> bossTag;
    std::vector<std::string> allyTag;

    static int s_enemyCounter = 0;
    static int s_towerCounter = 0;
    static int s_heroCounter = 0;
    static int s_bossCounter = 0;
    static int s_allyCounter = 0;
    auto addBasicTowerAnimation = [&] {
        AnimationType type = AnimationType_Num;
        Tag archer;
        Tag barrack;
        Tag mage;
        Tag stun;
        archer.type = AnimationType_Tower;
        archer.prefix = "archer";
        barrack.type = AnimationType_Tower;
        barrack.prefix = "barrack";
        mage.type = AnimationType_Tower;
        mage.prefix = "mage";
        stun.type = AnimationType_Tower;
        stun.prefix = "artillery";
        ValueMap root = FileUtils::getInstance()->getValueMapFromFile("elves_towers_animations.plist");
        if (root.empty()) {
            return ;
        }
        
        ValueMap animationDict = root["animations"].asValueMap();
        if (animationDict.empty()) {
            return;
        }
        
        ValueMap::const_iterator iter = animationDict.begin();
        while (iter != animationDict.end()) {
            std::string animationName = iter->first;
            if (std::string::npos != animationName.find("archer")) {
                archer.actions.push_back(animationName);
            }
            else if (std::string::npos != animationName.find("barrack")) {
                barrack.actions.push_back(animationName);
            }
            else if (std::string::npos != animationName.find("mage")) {
                mage.actions.push_back(animationName);
            }
            else if (std::string::npos != animationName.find("stun")) {
                stun.actions.push_back(animationName);
            }
            else {
                
            }
            
            ++iter;
        }
        
        tags.push_back(archer);
        tags.push_back(barrack);
        tags.push_back(mage);
        tags.push_back(stun);
    };
    
    auto checkAnimationType = [&](const std::string& path) {
        if (path == "arachnomancer_animations.plist") {
            int a = 1;
        }
        AnimationType type = AnimationType_Num;
        ValueMap root = FileUtils::getInstance()->getValueMapFromFile(path);
        if (root.empty()) {
            CCLOG("PListReader::extractAnimationFromResource failed to checkAnimationType with file [%s]", path.c_str());
            return ;
        }

        ValueMap animationDict = root["animations"].asValueMap();
        if (animationDict.empty()) {
            log("animationDict size = 0");
            return;
        }
        ValueMap::const_iterator iter = animationDict.begin();
        
        std::string animationName = iter->first;
        ValueMap actionDict = iter->second.asValueMap();
        std::string prefix = actionDict["prefix"].asString();
        
        
        // 判断这个前缀是否已经存储过一次
        Tag* pTag = nullptr;
        bool exist = false;
        
        for (int i = 0; i < tags.size(); ++i) {
            if (std::string::npos != prefix.find(tags[i].prefix)) {
                exist = true;
                pTag = &tags[i];
                break;
            }
        }
        
        if (!exist) {
            // 判断这个前缀属于哪个类别
            do {
                Tag newTag;
                bool found = false;
                for (int i = 0; i < TD_LEN(s_enemyName); ++i) {
                    if (std::string::npos != prefix.find(s_enemyName[i])) {
                        found = true;
                        newTag.type = AnimationType_Enemy;
                        newTag.prefix = s_enemyName[i];
                        tags.push_back(newTag);
                        break;
                    }
                }
                
                for (int i = 0; i < TD_LEN(s_towerName); ++i) {
                    if (std::string::npos != prefix.find(s_towerName[i])) {
                        found = true;
                        newTag.type = AnimationType_Tower;
                        newTag.prefix = s_towerName[i];
                        tags.push_back(newTag);
                        break;
                    }
                }
                
                for (int i = 0; i < TD_LEN(s_heroName); ++i) {
                    if (std::string::npos != prefix.find(s_heroName[i])) {
                        found = true;
                        newTag.type = AnimationType_Hero;
                        newTag.prefix = s_heroName[i];
                        tags.push_back(newTag);
                        break;
                    }
                }
                
                for (int i = 0; i < TD_LEN(s_bossName); ++i) {
                    if (std::string::npos != prefix.find(s_bossName[i])) {
                        found = true;
                        newTag.type = AnimationType_Boss;
                        newTag.prefix = s_bossName[i];
                        tags.push_back(newTag);
                        break;
                    }
                }
                
                for (int i = 0; i < TD_LEN(s_allyName); ++i) {
                    if (std::string::npos != prefix.find(s_allyName[i])) {
                        found = true;
                        newTag.type = AnimationType_Ally;
                        newTag.prefix = s_allyName[i];
                        tags.push_back(newTag);
                        break;
                    }
                }
                
                if (!found) {
                    log("%s is not handle yet!!", path.c_str());
                    return;
                }
                else {
                    pTag = &tags[tags.size() - 1];
                }

            } while (0);
        }

        while (iter != animationDict.end()) {
            std::string action = iter->first;
            ValueMap actionDict = iter->second.asValueMap();
            prefix = actionDict["prefix"].asString();
            pTag->actions.push_back(action);
#if 0 //  测试过滤字符
            if (name.find("boss") != std::string::npos ||
                name.find("Boss") != std::string::npos) {
                retType = AnimationType_Boss;

                bossTag.push_back(prefix);
                break;
            }
            else if (name.find("hero") != std::string::npos) {
                retType = AnimationType_Hero;

                heroTag.push_back(prefix);
                break;
            }
            else {
                int idx = name.find_last_of('_');
                if ("walkingRightLeft" == name.substr(idx + 1)) {
                    retType = AnimationType_Enemy;
                    enemyTag.push_back(prefix);
                    break;
                }
                else if ("running" == name.substr(idx + 1)) {
                    retType = AnimationType_Ally;

                    allyTag.push_back(prefix);
                    break;
                    
                }
            }
#endif
            ++iter;
            

        }
        
    };
    

#if (CC_PLATFORM_MAC == CC_TARGET_PLATFORM || CC_PLATFORM_IOS == CC_TARGET_PLATFORM || CC_PLATFORM_LINUX == CC_TARGET_PLATFORM)
    DIR *dir;
    struct dirent *ptr;
    dir = opendir(".");
    
    while (NULL != (ptr = readdir(dir)))
    {
        if (strstr(ptr->d_name, "animation")) {
            checkAnimationType(ptr->d_name);
        }
    }
    closedir(dir);
    
    // FIXME: 没有根据固定规则过滤出来的动画，如下Animation为Common/Manual级别
    // FIXME: 增加这些动画的Demo
    // FIXME: 可能需要增加一类动画： ActionEffect
    /*
     animation[babyAshbite_animations.plist] 未知生物动画
     animation[boss_drow_queen_portals_animations.plist] 未知Layer动画
     animation[boss_gnoll_animations.plist] // boss hita 相关Layer的动画
     animation[crystalArcane_extras_animations.plist] 未知动画
     animation[crystalSerpent_animations.plist] 未知动画
     animation[elves_hero_malik_animations.plist] 未知动画
     animation[elves_inapps_animations.plist] ＝＝＝＝＝＝＝＝＝＝ app内部的几个动画 ＝＝＝＝＝＝＝＝＝＝＝＝＝
     animation[elves_towers_animations.plist] ＝＝＝＝＝＝＝＝＝＝ Tower基础元素动画 ＝＝＝＝＝＝＝＝＝＝＝＝＝
     animation[faerie_dragons_animations.plist] 未知动画
     animation[faerie_grove_content_animations.plist]  一种植物
     animation[galahadriansBastion_layer_animations.plist] 未知
     animation[gnollBush_animations.plist] // 场景中的元素，好像是奴隶，待测试验证
     animation[mactans_malicia_animations.plist] 未知
     animation[malicia_animations.plist] // 蛛网，待测试验证
     animation[mercenary_draw_animations.plist] 未知动画
     animation[metropolis_content_animations.plist] 未知动画
     animation[metropolis_crystalUnstable_animations.plist] 未知动画
     animation[metropolis_special_teleport_animations.plist] 未知动画
     animation[paralyzingTree_animations.plist]  枯树
     animation[paralyzingTree_particle0_animations.plist] 枯树
     animation[paralyzingTree_particle1_animations.plist] 枯树
     animation[paralyzingTree_particle2_animations.plist] 枯树
     animation[paralyzingTree_particle_animations.plist] 枯树
     animation[paralyzingTree_stun_animations.plist] 枯树
     animation[pixie_animations.plist]  抢手，好像属于哪关的，可以当作ally
     animation[power_lightning_animations.plist]   闪电特效，很重要的特效。
     animation[roadRunner_animations.plist]  未知生物
     animation[snare_endless_animations.plist] 未知动画
     animation[splashScene.animations.plist] 未知动画
     animation[stage10_pork_animations.plist]   暂时无视
     animation[stage10_redRidingHood_animations.plist] 暂时无视
     animation[stage10_wolf_animations.plist] 暂时无视
     animation[stage15_bossDecal_demon_animations.plist] 暂时无视
     animation[stage15_mactans_animations.plist] 暂时 无视
     animation[stage15_malicia_animations.plist] 暂时无视
     animation[stage15_shield_animations.plist] 暂时无视
     animation[stage19_drizztdourden_animations.plist] 暂时无视
     animation[stage19_gnoll_drizztdourden_animations.plist] 暂时无视
     animation[stage6_animations.plist] 暂时无视
     animation[stage8_pixie_animations.plist] 暂时无视
     */
    
    // 有两类情况，强制拆开一下
    do {
        std::vector<_Tag>::iterator it = tags.begin();
        Tag big, medium, small;
        Tag arachnomancer, arachnomancer_mini, arachnomancer_spider;
        big.type = AnimationType_Enemy;
        big.prefix = "fungusRider";
        medium.prefix = "fungusRider_medium";
        medium.type = AnimationType_Enemy;
        small.prefix = "fungusRider_small";
        small.type = AnimationType_Enemy;
        
        arachnomancer.type = AnimationType_Enemy;
        arachnomancer.prefix = "arachnomancer";
        arachnomancer_mini.prefix = "arachnomancer_mini";
        arachnomancer_mini.type = AnimationType_Enemy;
        arachnomancer_spider.prefix = "arachnomancer_spider";
        arachnomancer_spider.type = AnimationType_Enemy;
        while (it != tags.end()) {
            if (it->prefix == "fungusRider") {
                for (int j = 0; j < it->actions.size(); ++j) {
                    if (std::string::npos != it->actions[j].find("fungusRider_small")) {
                        small.actions.push_back(it->actions[j]);
                    }
                    else if (std::string::npos != it->actions[j].find("fungusRider_medium")) {
                        medium.actions.push_back(it->actions[j]);
                    }
                    else {
                        big.actions.push_back(it->actions[j]);
                    }
                }
                
                tags.erase(it);
            }
            else if (it->prefix == "arachnomancer") {
                for (int j = 0; j < it->actions.size(); ++j) {
                    if (std::string::npos != it->actions[j].find("arachnomancer_miniSpider")) {
                        arachnomancer_mini.actions.push_back(it->actions[j]);
                    }
                    else if (std::string::npos != it->actions[j].find("arachnomancer_spider")) {
                        arachnomancer_spider.actions.push_back(it->actions[j]);
                    }
                    else {
                        arachnomancer.actions.push_back(it->actions[j]);
                    }
                }
                
                tags.erase(it);
            }
            else {
                ++it;
            }
            
        }
        
        tags.push_back(big);
        tags.push_back(medium);
        tags.push_back(small);
        tags.push_back(arachnomancer);
        tags.push_back(arachnomancer_mini);
        tags.push_back(arachnomancer_spider);
    } while (0);
    
    // elves_towers_animations.plist 比较特别，这里单独处理
    addBasicTowerAnimation();
    
    log("enemy");
    for (int i = 0; i < enemyTag.size(); ++i) {
        log("\"%s\", ", enemyTag[i].c_str());
    }
    log("tower");
    for (int i = 0; i < towerTag.size(); ++i) {
        log("\"%s\", ", towerTag[i].c_str());
    }
    log("ally");
    for (int i = 0; i < allyTag.size(); ++i) {
        log("\"%s\", ", allyTag[i].c_str());
    }
    log("boss");
    for (int i = 0; i < bossTag.size(); ++i) {
        log("\"%s\", ", bossTag[i].c_str());
    }
    log("hero");
    for (int i = 0; i < heroTag.size(); ++i) {
        log("\"%s\", ", heroTag[i].c_str());
    }
    
    
    for (int i = 0; i < tags.size(); ++i) {
        Tag t = tags[i];
        log("%s", t.prefix.c_str());
        for (int j = 0; j < t.actions.size(); ++j)
            log("       Action[%d]:[%s]", j , t.actions[j].c_str());
    }
    
    // tower
    int towerId = 0;
    for (int i = 0; i < tags.size(); ++i) {
        Tag t = tags[i];
        if (t.type != AnimationType_Tower) continue;
        std::string id = tags[i].prefix;
        convertToCamelCase(id, "TowerID_");
        log("%s = %d,", id.c_str(), towerId);
        for (int j = 0; j < t.actions.size(); ++j) {
            std::string str = t.actions[j];
            convertToCamelCase(str, "#define AnimationTower_");
            //log("towerID [%d] Action[%d]:[%s] , hash [%x]", towerId, j , t.actions[j].c_str(), ANIMATION_HASH(AnimationType_Tower, towerId, j));
            log("%s 0x%x", str.c_str(), ANIMATION_HASH(AnimationType_Tower, towerId, j));
            
        }
        ++towerId;
    }
    
    // enemy
    int enemyId = 0;
    for (int i = 0; i < tags.size(); ++i) {
        Tag t = tags[i];
        if (t.type != AnimationType_Enemy) continue;
        std::string id = tags[i].prefix;
        convertToCamelCase(id, "EnemyID_");
        log("%s = %d,", id.c_str(), enemyId);
        for (int j = 0; j < t.actions.size(); ++j) {
            std::string str = t.actions[j];
            convertToCamelCase(str, "#define AnimationEnemy_");
            //log("towerID [%d] Action[%d]:[%s] , hash [%x]", towerId, j , t.actions[j].c_str(), ANIMATION_HASH(AnimationType_Tower, towerId, j));
            log("%s 0x%x", str.c_str(), ANIMATION_HASH(AnimationType_Enemy, enemyId, j));
            
        }
        ++enemyId;
    }
    
    // ally
    int allyId = 0;
    for (int i = 0; i < tags.size(); ++i) {
        Tag t = tags[i];
        if (t.type != AnimationType_Ally) continue;
        std::string id = tags[i].prefix;
        convertToCamelCase(id, "AllyID_");
        log("%s = %d,", id.c_str(), allyId);
        for (int j = 0; j < t.actions.size(); ++j) {
            std::string str = t.actions[j];
            convertToCamelCase(str, "#define AnimationAlly_");
            //log("towerID [%d] Action[%d]:[%s] , hash [%x]", towerId, j , t.actions[j].c_str(), ANIMATION_HASH(AnimationType_Tower, towerId, j));
            log("%s 0x%x", str.c_str(), ANIMATION_HASH(AnimationType_Ally, allyId, j));
        }
        ++allyId;
    }
    
    // hero
    int heroId = 0;
    for (int i = 0; i < tags.size(); ++i) {
        Tag t = tags[i];
        if (t.type != AnimationType_Hero) continue;
        std::string id = tags[i].prefix;
        convertToCamelCase(id, "HeroID_");
        log("%s = %d,", id.c_str(), heroId);
        for (int j = 0; j < t.actions.size(); ++j) {
            std::string str = t.actions[j];
            convertToCamelCase(str, "#define AnimationHero_");
            //log("towerID [%d] Action[%d]:[%s] , hash [%x]", towerId, j , t.actions[j].c_str(), ANIMATION_HASH(AnimationType_Tower, towerId, j));
            log("%s 0x%x", str.c_str(), ANIMATION_HASH(AnimationType_Hero, heroId, j));
        }
        ++heroId;
    }
    
    // boss
    int bossId = 0;
    for (int i = 0; i < tags.size(); ++i) {
        Tag t = tags[i];
        if (t.type != AnimationType_Boss) continue;
        std::string id = tags[i].prefix;
        convertToCamelCase(id, "BossID_");
        log("%s = %d,", id.c_str(), bossId);
        for (int j = 0; j < t.actions.size(); ++j) {
            std::string str = t.actions[j];
            convertToCamelCase(str, "#define AnimationBoss_");
            //log("towerID [%d] Action[%d]:[%s] , hash [%x]", towerId, j , t.actions[j].c_str(), ANIMATION_HASH(AnimationType_Tower, towerId, j));
            log("%s 0x%x", str.c_str(), ANIMATION_HASH(AnimationType_Boss, bossId, j));
        }
        
        ++bossId;
    }

    int enemyID = 0;

#else
    // TODO:: add win32 file traverse impelement
#endif

}

void PListReader::createEnemyAnimationTableIndexer()
{
    static const std::string s_actionType[] =
    {
        "attack",
        "walkingDown",
        "walkingRightLeft",
        "idle",
        "walkingUp",
        "death",
        "spawn",
        "respawn",
        "shoot",
        "cast",
        "special"
    };
    
    static int s_enemyId_ht_counter = 0;
    static int s_actionId_ht_counter = 0;
    
    auto isEnemyPlistFile = [](const std::string& path)->bool {
        ValueMap root = FileUtils::getInstance()->getValueMapFromFile(path);
        if (root.empty()) {
            CCLOG("PListReader::lookupActionTypes failed to create with file [%s]", path.c_str());
            return false;
        }

        ValueMap animationDict = root["animations"].asValueMap();
        ValueMap::const_iterator iter = animationDict.begin();
        while (iter != animationDict.end()) {
            std::string name = iter->first;
            if (name.find("boss") != std::string::npos ||
                name.find("Boss") != std::string::npos ||
                name.find("hero") != std::string::npos ||
                name.find("rabbit") != std::string::npos) {
                return false;
            }
            
            int idx = name.find_last_of('_');
            //CCLOG("%s", name.substr(idx + 1).c_str());
            if ("walkingRightLeft" == name.substr(idx + 1)) {
                return true;
            }
            
            ++iter;
        }

        return false;
    };

    auto addAnimation = [](int id, const std::string& path) {
        ValueMap root = FileUtils::getInstance()->getValueMapFromFile(path);
        if (root.empty()) {
            CCLOG("PListReader::lookupActionTypes failed to create with file [%s]", path.c_str());
            return;
        }

        ValueMap animationDict = root["animations"].asValueMap();
        if (animationDict.empty()) {
            return;
        }

        ValueMap::const_iterator iter = animationDict.begin();
        ValueMap firstEntry = iter->second.asValueMap();
        std::string enemyName = firstEntry["prefix"].asString();
        while (iter != animationDict.end()) {
            std::string enumName = iter->first;

            bool exist = false;
            std::string name = iter->first;
            std::string actionName;
            if (name.find(enemyName) == std::string::npos) {
                actionName = name.substr(name.find_last_of("_") + 1);
            }
            else {
                actionName  = name.substr(enemyName.size() + 1);
            }

            bool normalAction = false;
            int actionId = 0;
            int i = 0;
            for (;i < sizeof(s_actionType) / sizeof(s_actionType[0]); ++i) {
                if (s_actionType[i] == actionName) {
                    // CCLog("%s exist", actionName.c_str());
                    actionId = (id << 16) | i;
                    normalAction = true;
                    //AnimationManager::getInstance()->addAnimationIndex(id, i, name);
                    break;
                }
            }

            if (!normalAction) {
                //AnimationManager::getInstance()->addAnimationIndex(id, s_actionId_ht_counter, name);
            }
            
#ifdef TD_TEST
            convertToCamelCase(enumName, "EnemyAction_");
            //CCLOG("#define %s %d path %s", enumName.c_str(), normalAction ? i : s_actionId_ht_counter, path.c_str());
#endif
            
            ++iter;
        }
    };

#if (CC_PLATFORM_MAC == CC_TARGET_PLATFORM || CC_PLATFORM_IOS == CC_TARGET_PLATFORM || CC_PLATFORM_LINUX == CC_TARGET_PLATFORM)
    DIR *dir;
    struct dirent *ptr;
    dir = opendir(".");
    
    while (NULL != (ptr = readdir(dir)))
    {
        if (strstr(ptr->d_name, "animations.plist")) {
            // CCLOG("d_name: %s\n", ptr->d_name);
            if (isEnemyPlistFile(ptr->d_name)) {
                std::string path(ptr->d_name);
                std::string enmeyName = path.substr(0, path.find("_animations"));
                convertToCamelCase(enmeyName, "EnemyID_");
                ++s_enemyId_ht_counter;
                CCLog("%s = %d", enmeyName.c_str(), s_enemyId_ht_counter);
                addAnimation(s_enemyId_ht_counter, ptr->d_name);
            }
        }
    }
    closedir(dir);
#if 0
    AnimationManager::getInstance()->showTable();
#endif

#else
    // TODO:: add win32 file traverse impelement
#endif
}

void PListReader::saveImageFromPlist(const std::string &plist)
{
    // force add sprite frame
    Size winSize = Director::getInstance()->getWinSize();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
    ValueMap root = FileUtils::getInstance()->getValueMapFromFile(plist);
    ValueMap::const_iterator itr = root.begin();
    while (itr != root.end()) {
        ++itr;
    }
    
    if (root.empty()) {
        return;
    }
    
    std::string folderName = plist.substr(0, plist.find_last_of("."));
    FileUtils::getInstance()->createDirectory(FileUtils::getInstance()->getWritablePath() + folderName);
    ValueMap frames = root["frames"].asValueMap();
    ValueMap::const_iterator iter = frames.begin();
    while (iter != frames.end()) {
        Sprite* sprite = Sprite::createWithSpriteFrameName(iter->first);
        if (!sprite) {
            return;
        }
        
        auto render = RenderTexture::create(winSize.width, winSize.height);
        if (!render) {
            return;
        }
        
        sprite->setPosition(winSize.width / 2, winSize.height / 2);
        render->begin();
        sprite->visit();
        render->end();
#if 0 // 需要cocos2d-x保存路径方法， CCRenderTexture::saveImage
        render->saveToFile(iter->first, folderName, Image::Format::PNG);
#else
        render->saveToFile(iter->first, Image::Format::PNG);
#endif
        CCLOG("save %s to %s", iter->first.c_str(), FileUtils::getInstance()->getWritablePath().c_str());
        ++iter;
    }
}

void PListReader::generateAnimationPlist(const std::string &plistname, Dictionary* animationDict, Dictionary* includePlists)
{
    if (!animationDict) {
        return;
    }
    auto root = Dictionary::create();
    root->setObject(animationDict, "animations");
    
    if (includePlists == nullptr) {
        root->setObject(Dictionary::create(), "includes");
    }
    else {
        root->setObject(includePlists, "includes");
    }
    
    // end with /
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fullPath = writablePath + plistname + ".plist";
    if(root->writeToFile(fullPath.c_str()))
        log("see the plist file at %s", fullPath.c_str());
    else
        log("write plist file failed");
    
}

Dictionary* PListReader::createAnimationPlist(std::string prefix, int from, int to)
{
    //int lastSplit = animateName.find_last_of("_");
    //std::string prefixName = animateName;
    //if (lastSplit > 0) {
    //    prefixName = animateName.substr(0, lastSplit);
    //}
    auto dictInDict = Dictionary::create();
    
    //add prefixName to the plist
    auto prefixNameObj = String::create(prefix);
    dictInDict->setObject(prefixNameObj, "prefix");
    
    //add toIndex to the plist
    auto toIndexObj = Integer::create(to);
    dictInDict->setObject(toIndexObj, "toIndex");
    
    //add toIndex to the plist
    auto fromIndexObj = Integer::create(from);
    dictInDict->setObject(fromIndexObj, "fromIndex");
    return dictInDict;
}
