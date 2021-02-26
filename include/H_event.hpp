#ifndef HERO_EVENT_HPP
#define HERO_EVENT_HPP

#include"SDL.h"

namespace Hero
{
namespace Event
{
    namespace Engine{
        void Init();
        void Delete();
        int Update();
    }

    void SendEvent();
}
}

#endif