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
    namespace Engine
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

            return 0;
        }
    }
    void SendEvent()
    {

    }

Event::Event()
{
    this->functions = NULL;
    this->count = 0;
}

Event::~Event()
{
    this->Clear();
}

void Event::Add(EventFunction function)
{
    this->count++;
    this->functions = (EventFunction*)std::realloc(this->functions, this->count * sizeof(EventFunction*));
    this->functions[this->count-1] = function;
}

void Event::Clear()
{
    delete[] this->functions;
    this->functions = NULL;
    this->count = 0;
}

void Event::Invoke(void* object, void *args, int argc)
{
    for(int i = 0; i < this->count; i++)
    {
        this->functions[i](object, args, argc);
    }
}

} }