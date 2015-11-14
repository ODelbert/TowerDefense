#ifndef COMMONDEF_H
#define COMMONDEF_H

//#define TD_TEST
//#define TD_DEBUG

#define TD_WIDTH 1136
#define TD_HEIGHT 640

#define TD_FONT "Arial"
#define LOGF CCLOG(__PRETTY_FUNCTION__);

#define TD_SIZE(x) CCLOG("%s size = %f %f", #x, x->getContentSize().width, x->getContentSize().height);

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