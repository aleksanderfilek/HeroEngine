#include"H_event.hpp"

struct EventData
{
    SDL_Event events;
};

EventData* eventData;

namespace Hero
{
namespace Event
{
    void Init()
    {
        eventData = new EventData();
    }

    void Delete()
    {
        delete eventData;
    }

    int Update()
    {
        while(SDL_PollEvent(&eventData->events) != 0){
            switch (eventData->events.type)
            {
            case SDL_QUIT:
                return -1;
                break;
            case SDL_WINDOWEVENT:
                if(eventData->events.window.event == SDL_WINDOWEVENT_RESIZED){
                    
                }
                break;
            }
        }
    }

    void SendEvent()
    {

    }
}
}