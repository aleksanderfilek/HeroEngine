#ifndef HERO_LEVEL_CORE_HPP
#define HERO_LEVEL_CORE_HPP

namespace Hero
{

class ILevel
{
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Close() = 0;
};

}

#endif