#include "PListReader.h"

#if (CC_PLATFORM_MAC == CC_TARGET_PLATFORM || CC_PLATFORM_IOS == CC_TARGET_PLATFORM || CC_PLATFORM_LINUX == CC_TARGET_PLATFORM)
#   include <sys/types.h>
#   include <dirent.h>
#   include <unistd.h>
#else
// TODO:win32
#endif

#include <stdio.h>

#include "CommonDef.h"
#include "Animation/AnimationManager.h"

USING_NS_CC;

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
                    AnimationManager::getInstance()->addAnimationIndex(id, i, name);
                    break;
                }
            }

            if (!normalAction) {
                AnimationManager::getInstance()->addAnimationIndex(id, s_actionId_ht_counter, name);
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
