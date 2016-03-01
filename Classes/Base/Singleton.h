#ifndef SINGLETON_H
#define SINGLETON_H

#include "assert.h"

template <typename T>
class WeakSingleton
{
public:
    static T& inst()
    {
        assert(NULL != instance);

        return *instance;
    }

    static T* getInstance()
    {
        assert(NULL != instance);

        return instance;
    }

protected:
    WeakSingleton()
    {
         assert(NULL != instance);

         instance = reinterpret_cast<T*>(this);
    }

    ~WeakSingleton()
    {
        assert(NULL != instance);
        instance = NULL;
    }

private:
    static T* instance;
};

template<typename T> T* WeakSingleton<T>::instance = NULL;

#endif

