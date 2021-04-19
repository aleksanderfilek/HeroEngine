#include"Core/Hero_Core.hpp"

namespace Hero
{

Core* Core::instance = nullptr;

Core::Core()
{
    DEBUG_CODE( std::cout<<"[Core] - Initializing"<<std::endl; )

    Core::instance = this;
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

    while (this->_running)
    {
        timer = SDL_GetTicks();

        for(ISystem* sys: this->_systems)
        {
            sys->Update();
        }

        deltaTime = (double)(SDL_GetTicks() - timer)/1000.0;

    }


    std::vector<ISystem*>::iterator i = this->_systems.end();
    while (i != this->_systems.begin())
    {
        --i;
        (*i)->Close();
    } 
}

}