#ifndef HERO_EVENT_HPP
#define HERO_EVENT_HPP

#include<SDL\SDL.h>

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