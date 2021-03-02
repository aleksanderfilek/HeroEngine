#include"H_event.hpp"



namespace Hero
{

    EventSystem::EventSystem()
    {

    }

    EventSystem::~EventSystem()
    {

    }

    int EventSystem::Update()
    {
        while(SDL_PollEvent(&this->events) != 0)
        {
            switch (this->events.type)
            {
            case SDL_QUIT:
                return -1;
                break;
            }
        }

        return 0;
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

} 