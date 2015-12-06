#ifndef COMMONDEF_H
#define COMMONDEF_H

//#define TD_TEST
//#define TD_DEBUG

#define TD_WIDTH 1136
#define TD_HEIGHT 640

#define MAP_WIDTH 1200
#define MAP_HEIGHT 1000

#define TD_FONT "Arial"

#define LOGF CCLOG(__FUNCTION__); // __PRETTY_FUNCTION__

#define SPEED_RATE(x) ((x) / 500)
#define TD_SIZE(x) CCLOG("%s size = %f %f", #x, x->getContentSize().width, x->getContentSize().height);
#define TD_POS(x) CCLOG("%s pos = %f %f", #x, x->getPosition().x, x->getPosition().y);

typedef unsigned int uint;
#define SINGLETON_IMPL(class) \
class* class::s_instance = nullptr; \
class* class::getInstance() \
{ \
    if (!s_instance) { \
        s_instance = new class; \
    } \
    return s_instance; \
} \
void class::destroy() \
{ \
    if (s_instance) { \
        delete s_instance; \
        s_instance = nullptr; \
    } \
} \

#endif /* COMMONDEF_H */