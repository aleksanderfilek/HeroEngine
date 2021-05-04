#include"Systems/Hero_EventSystem.hpp"

namespace Hero
{

const char* Event::name = "Event System";
//Event* Event::instance = nullptr;

Event::Event()
{
    //Event::instance = this;
}

Event::~Event()
{

}

void Event::Init()
{
    ISystem::Init();
}

void Event::Update()
{
    //std::memset(this->states, false, sizeof(this->states));

    while(SDL_PollEvent(&this->events) != 0)
    {
        switch (this->events.type)
        {
        case SDL_QUIT:
            Core::Get()->Close();
            //this->states[0] = true;
            break;
        }
    }
}

void Event::Close()
{
    ISystem::Close();
}

}