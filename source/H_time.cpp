#include"H_time.hpp"

struct TimeData
{
    double deltaTime = 0;
    double timeScale = 1;
    double scaledTime = 0;
};

TimeData* timeData;

namespace Hero
{
namespace Time
{
    void Init()
    {
        timeData = new TimeData();
    }

    void Delete()
    {
        delete timeData;
    }

    void SetDeltaTime(double value)
    { 
        timeData->deltaTime = value;
        timeData->scaledTime = value * timeData->timeScale;
    }

    double GetDeltaTime()
    { 
        return timeData->scaledTime; 
    }

    void SetScale(double value)
    { 
        timeData->timeScale = value; 
        timeData->scaledTime = value * timeData->deltaTime;
    }

    double GetScale()
    { 
        return timeData->timeScale; 
    }
}
}