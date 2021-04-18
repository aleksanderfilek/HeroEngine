#include"Core/Hero_Time.hpp"

namespace Hero
{
    Time* Time::instance = nullptr;

    Time::Time()
    {
        instance = this;
        startupTime = SDL_GetTicks();
    }

    Time::~Time()
    {
        
    }

    double Time::GetDeltaTime()
    { 
        return instance->scaledTime; 
    }

    void Time::SetScale(double value)
    { 
        instance->timeScale = value; 
        instance->scaledTime = value * instance->deltaTime;
    }

    double Time::GetScale()
    { 
        return instance->timeScale; 
    }

}