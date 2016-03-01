#ifndef SINGLETON_H
#define SINGLETON_H

#include "assert.h"

template<typename T>
class Singleton
{
public:
    static T* getInstance()
    {
        if (!s_instance) {
            s_instance = new T;
        }
        
        return s_instance;
    }
    
protected:
    Singleton() {}
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
    
private:
    static T* s_instance;
};

template<typename T> T* Singleton<T>::s_instance = NULL;

template <typename T>
class WeakSingleton
{
public:
    static T& inst()
    {
        assert(NULL != s_instance);

        return *s_instance;
    }

    static T* getInstance()
    {
        assert(NULL != s_instance);

        return s_instance;
    }

protected:
    WeakSingleton()
    {
         assert(NULL != s_instance);

         s_instance = reinterpret_cast<T*>(this);
    }

    ~WeakSingleton()
    {
        assert(NULL != s_instance);
        s_instance = NULL;
    }

private:
    static T* s_instance;
};

template<typename T> T* WeakSingleton<T>::s_instance = NULL;

#endif

