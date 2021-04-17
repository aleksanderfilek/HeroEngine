#include"Core/Hero_Core.hpp"

namespace Hero
{

Core::Core()
{
    DEBUG_CODE( std::cout<<"[Core] - Initializing"<<std::endl; )
}

Core::~Core()
{
    DEBUG_CODE( std::cout<<"[Core] - Closing"<<std::endl; )

    for(ISystem* sys: this->_systems)
    {
        delete sys;
    }
    this->_systems.clear();
}

void Core::Start()
{
    DEBUG_CODE( std::cout<<"[Core] - Starting"<<std::endl; )

    this->_running = true;

    for(ISystem* sys: this->_systems)
    {
        sys->Init();
    }

    std::uint32_t timer;
    double deltaTime = 0.0;

    double time = 0.0;

    while (this->_running)
    {
        timer = SDL_GetTicks();

        for(ISystem* sys: this->_systems)
        {
            sys->Update(deltaTime);
        }

        time += deltaTime;
        if(time > 1.0)
        {
            this->Close();
        }

        deltaTime = (double)(SDL_GetTicks() - timer)/1000.0;

    }

    for(ISystem* sys: this->_systems)
    {
        sys->Close();
    }
}

void Core::Close()
{
    this->_running = false;
}

}