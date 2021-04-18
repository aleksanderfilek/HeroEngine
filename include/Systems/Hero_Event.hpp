#ifndef HERO_EVENT_HPP
#define HERO_EVENT_HPP

#include<cstdint>
#include<cstring>

#include"Core/Hero_Core.hpp"
#include"Core/Hero_System.hpp"
#include"Core/Hero_Config.hpp"

namespace Hero
{
/*
enum class EventType : std::uint8_t
{
    Quit = 0
};
*/

class Event: public ISystem
{
private:
    //bool states[1] = {0};

    SDL_Event events;

public:
    Event();
    ~Event();

    void Init();
    void Update();
    void Close();

    static const char* name; 
    const char* GetName(){ return name; }

    /*
    static void SendCoreEvent(); //wysyłanie eventu do rdzenia
    static void SendSDLEvent(); //wysyłanie eventu do SDL
    

    static inline bool EventStatus(EventType event)
        { return instance->states[(int)event]; }
    */
};

}

#endif