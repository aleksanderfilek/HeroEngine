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
}

#endif