#include "PListReader.h"

USING_NS_CC;

static EnemyPlist::EnemySpriteInfo s_enemySpriteInfoNone;
PListReader* PListReader::s_instance = nullptr;


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

PListReader* PListReader::getInstance()
{
    if (s_instance == nullptr) {
        s_instance = new PListReader();
        s_instance->autorelease();
    }

    return s_instance;
}

void PListReader::destroy()
{
    if (s_instance) {
        CC_SAFE_DELETE(s_instance);
    }
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
