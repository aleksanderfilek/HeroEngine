#ifndef HERO_LEVEL_SYSTEM_HPP
#define HERO_LEVEL_SYSTEM_HPP

#include"Core/Hero_Core.hpp"
#include"Core/Hero_System.hpp"
#include"Core/Hero_Config.hpp"
#include"Core/Hero_Level.hpp"

namespace Hero
{

class Level: public ISystem
{
private:
    ILevel* currentLevel;
    ILevel* nextLevel;

    void CheckLevel();
public:
    Level(ILevel* startLevel);
    ~Level();

    void Init();
    void Update();
    void Close();

    void SetNextLevel(ILevel* nextLevel);

    static const char* name; 
    const char* GetName(){ return name; }

};

}

#endif