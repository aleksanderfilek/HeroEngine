#ifndef HERO_USERINTERFACE_SYSTEM_HPP
#define HERO_USERINTERFACE_SYSTEM_HPP

#include"Core/Hero_System.hpp"
#include"Core/Hero_Mesh.hpp"
#include"Core/Hero_Shader.hpp"

namespace Hero
{

class UserInterface : public ISystem
{
private:
    Mesh* mesh;
    Shader *shader;

public:
    UserInterface();
    ~UserInterface();

    void Init();
    void Update();
    void Close();

    static const char* name; 
    const char* GetName(){ return name; }

    std::uint8_t priority(){ return 254; }


};

}

#endif