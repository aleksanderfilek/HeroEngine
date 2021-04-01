#ifndef HERO_EVENT_HPP
#define HERO_EVENT_HPP

#include"H_defines.hpp"

#include<iostream>
#include<cstdlib>

namespace Hero
{

    class EventSystem
    {
    private:
        SDL_Event events;
    public:
        EventSystem();
        ~EventSystem();

        int Update();
    };

    typedef void (*EventFunction)(void* object, void *args, int argc);
    #define event(name) void name(void* object, void *args, int argc)
    #define EventFromClass(func) (Hero::EventFunction)&func

    class Event
    {
    private:    
        EventFunction* functions;
        unsigned int count;
    public:
        Event();
        ~Event();

        void Add(EventFunction function);
        void Clear();
        void Invoke(void* object, void *args, int argc);
    };
}

#endif