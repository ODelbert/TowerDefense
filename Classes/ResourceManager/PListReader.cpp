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

static EnemyPlist::EnemySpriteInfo s_enemySpriteInfoNone;

SINGLETON_IMPL(PListReader)

EnemyPlist::EnemyPlist()
{
    m_infos.clear();
}

void EnemyPlist::addInfo(const EnemyPlist::EnemySpriteInfo &info)
{
    m_infos.insert(std::make_pair(info.spriteName, info));
}

const EnemyPlist::EnemySpriteInfo& EnemyPlist::getInfo(const std::string &name)
{
    std::map<std::string, EnemySpriteInfo>::iterator iter = m_infos.find(name);
    return iter != m_infos.end() ? iter->second : s_enemySpriteInfoNone;
}

EnemyPlist* PListReader::createEnemyPlist(const std::string &plistname)
{
    CCLOG("PListReader::createEnemyPlist filename %s", plistname.c_str());
    
    EnemyPlist *plist = new EnemyPlist();
    plist->autorelease();

    EnemyPlist::EnemySpriteInfo info;

    ValueMap plistDict = FileUtils::getInstance()->getValueMapFromFile(plistname);
    ValueMap enemyDict = plistDict["frames"].asValueMap();

    if (enemyDict.empty()) {
        CCLOG("PListReader::createEnemyPlist enemyDict is empty");
        return nullptr;
    }
    
    ValueMap::const_iterator iter = enemyDict.begin();
    
    int a, b, c, d;
    while (iter != enemyDict.end()) {
        a = b = c = d = 0;
        ValueMap infoEntry = iter->second.asValueMap();
        info.spriteName = iter->first;
        
        std::string spriteSize = infoEntry["spriteSize"].asString();
        sscanf(spriteSize.c_str(), "{%d, %d}", &a, &b);
        info.spriteSize.setSize(a, b);
        
        info.spriteTrimmed = infoEntry["spriteTrimmed"].asBool();
        
        std::string spriteColorRect = infoEntry["spriteColorRect"].asString();
        sscanf(spriteColorRect.c_str(), "{{%d, %d}, {%d, %d}}", &a, &b, &c, &d);
        info.spriteColorRect.setRect(a, b, c, d);
        
        std::string spriteOffset = infoEntry["spriteOffset"].asString();
        sscanf(spriteOffset.c_str(), "{%d, %d}", &a, &b);
        info.spriteOffet.set(a, b);
        
        std::string textureRect = infoEntry["textureRect"].asString();
        sscanf(textureRect.c_str(), "{{%d, %d}, {%d, %d}}", &a, &b, &c, &d);
        info.textureRect.setRect(a, b, c, d);
        
        info.textureRotated = infoEntry["textureRotated"].asBool();
        
        std::string spriteSourceSize = infoEntry["spriteSourceSize"].asString();
        sscanf(spriteSourceSize.c_str(), "{%d, %d}", &a, &b);
        info.spriteSourceSize.setSize(a, b);
        
        // CCLOG("spriteName %s\nspriteSize %s\nspriteColorRect %s\nspriteOffset %s\ntextureRect %s\nspriteSourceSize %s\n", \
              info.spriteName.c_str(), spriteSize.c_str(), \
              spriteColorRect.c_str(), spriteOffset.c_str(), \
              textureRect.c_str(), spriteSourceSize.c_str());
        
        plist->addInfo(info);
        
        iter++;
    }

    return plist;
}

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
            float offsetX = 59.f;
            float offsetY = 137.f;
            for (int k = 0; k < pathVec.size(); ++k) {
                ValueMap pos = pathVec[k].asValueMap();
                path.push_back(Vec2(pos["x"].asFloat() * MAP_WIDTH / TD_WIDTH + offsetX, pos["y"].asFloat() + offsetY));
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


#ifdef TD_DEBUG
#include "GameData.h"
void PListReader::generateEnemyPlist()
{
    auto root = Dictionary::create();
    //auto array = Array::create();
    //for (int i = 0; i < s_enemiesInfo / sizeof(s_enemiesInfo[0]); ++i) {
    //    auto dictInArray = Dictionary::create();
        
    //}
}
void PListReader::generateTowerPlist()
{
    auto root = Dictionary::create();
    auto string = String::create("string element value");
    root->setObject(string, "string element key");
    
    auto array = Array::create();
    
    auto dictInArray = Dictionary::create();
    dictInArray->setObject(String::create("string in dictInArray value 0"), "string in dictInArray key 0");
    dictInArray->setObject(String::create("string in dictInArray value 1"), "string in dictInArray key 1");
    array->addObject(dictInArray);
    
    array->addObject(String::create("string in array"));
    
    auto arrayInArray = Array::create();
    arrayInArray->addObject(String::create("string 0 in arrayInArray"));
    arrayInArray->addObject(String::create("string 1 in arrayInArray"));
    array->addObject(arrayInArray);
    
    root->setObject(array, "array");
    
    auto dictInDict = Dictionary::create();
    dictInDict->setObject(String::create("string in dictInDict value"), "string in dictInDict key");
    
    //add boolean to the plist
    auto booleanObject = Bool::create(true);
    dictInDict->setObject(booleanObject, "bool");
    
    //add interger to the plist
    auto intObject = Integer::create(1024);
    dictInDict->setObject(intObject, "integer");
    
    //add float to the plist
    auto floatObject = Float::create(1024.1024f);
    dictInDict->setObject(floatObject, "float");
    
    //add double to the plist
    auto doubleObject = Double::create(1024.123);
    dictInDict->setObject(doubleObject, "double");
    
    
    
    root->setObject(dictInDict, "dictInDict, Hello World");
    
    // end with /
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fullPath = writablePath + "text.plist";
    if(root->writeToFile(fullPath.c_str()))
        log("see the plist file at %s", fullPath.c_str());
    else
        log("write plist file failed");
}
#endif
