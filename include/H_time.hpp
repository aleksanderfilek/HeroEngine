#ifndef H_timer_HPP
#define H_timer_HPP

#include<SDL\SDL.h>

#include<stdint.h>

namespace Hero
{
class Time
{
private:
    static Time* instance;

    uint32_t startupTime;
    double deltaTime = 0;
    double timeScale = 1;
    double scaledTime = 0;
public:
    Time();
    ~Time();

    inline void SetDeltaTime(double value)
    { 
        deltaTime = value; 
        scaledTime = value * timeScale;
    }

    static double GetDeltaTime();
    static void SetScale(double value);
    static double GetScale();
};

}

#endif