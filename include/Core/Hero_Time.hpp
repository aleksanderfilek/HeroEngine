#ifndef HERO_TIME_HPP
#define HERO_TIME_HPP

#include<stdint.h>

#include"Hero_Config.hpp"

namespace Hero
{
class Core;

class Time
{
private:
    static Time* instance;

    uint32_t startupTime;
    double deltaTime = 0.0;
    double timeScale = 1.0;
    double scaledTime = 0.0;
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