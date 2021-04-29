#ifndef HERO_RESOURCES_SYSTEM_HPP
#define HERo_RESOURCES_SYSTEM_HPP

#include"Core/Hero_System.hpp"

namespace Hero
{


class Resources : public ISystem
{
public:
    Resources();
    ~Resources();

    void Init();
    void Update();
    void Close();

    static const char* name; 
    const char* GetName(){ return name; }
};

}

#endif