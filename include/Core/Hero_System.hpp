#ifndef HERO_SYSTEM_H
#define HERO_SYSTEM_H

namespace Hero
{

class ISystem
{
public:
    ISystem(){}
    virtual ~ISystem(){};

    virtual void Init() = 0;
    virtual void Update(double  deltaTime) = 0;
    virtual void Close() = 0;

    virtual const char* name() = 0;
};

}

#endif