#ifndef COMMONDEF_H
#define COMMONDEF_H

#include <string>
#include <map>
#include <stdio.h>



#define TD_TEST
#define TD_DEBUG

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