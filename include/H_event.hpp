#ifndef HERO_EVENT_HPP
#define HERO_EVENT_HPP

#include<SDL2/SDL.h>

namespace Hero
{
namespace Event
{
    #ifdef ENGINE
        void Init();
        void Delete();
        int Update();
    #endif

    void SendEvent();
}
}

#endif