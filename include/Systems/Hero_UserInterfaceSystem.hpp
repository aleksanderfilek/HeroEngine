#ifndef HERO_USERINTERFACE_SYSTEM_HPP
#define HERO_USERINTERFACE_SYSTEM_HPP

#include"Core/Hero_System.hpp"
#include"HeroUI.hpp"

namespace Hero
{

class UserInterface : public ISystem
{
private:
public:
    UserInterface();
    ~UserInterface();

    void Init();
    void Update();
    void Close();

    static const char* name; 
    const char* GetName(){ return name; }
};

}

#endif