
    auto waveListener = EventListenerCustom::create("WaveEvent", [=](EventCustom* event){
        typedef struct _WaveEventData {
            int id;
            int path;
            int subPath;
        } WaveEventData;
        
        WaveEventData* info = static_cast<WaveEventData*>(event->getUserData());

        auto enmey = EnemyFactory::create(static_cast<EnemyID>(info->id));
        enmey->sendToBattle(WaveManager::getInstance()->getPath(info->path, info->subPath));
        m_mapSprite->addChild(enmey);
    });