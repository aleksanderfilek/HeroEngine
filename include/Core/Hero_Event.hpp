#ifndef HERO_EVENT_HPP
#define HERO_EVENT_HPP

#include<cstdlib>

namespace Hero
{

typedef void (*EventFunction)(void* object, void *args, int argc);
#define event(name) void name(void* object, void *args, int argc)
#define EventFromClass(func) (Hero::EventFunction)&func

class EventHandler
{
private:    
    EventFunction* functions;
    unsigned int count;
public:
    EventHandler();
    ~EventHandler();

    void Add(EventFunction function);
    void Clear();
    void Invoke(void* object, void *args, int argc);
};

}

#endif