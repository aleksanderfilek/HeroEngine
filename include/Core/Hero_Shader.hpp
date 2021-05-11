#ifndef HERO_SHADER_CPP
#define HERO_SHADER_CPP

#include<string>
#include<vector>
#include<fstream>

#include"Hero_Config.hpp"
#include"Core/Hero_Utilities.hpp"

namespace Hero
{

struct Shader
{
    unsigned int glId;
    std::string name;
};

Shader* LoadShader(const std::string& path);
void UnloadShader(Shader* shader);
void BindShader(const Shader* shader);

namespace Extra
{

    Shader LoadShaderByCopy(const std::string& path);
    void UnloadShaderByCopy(Shader& shader);

}

}

#endif