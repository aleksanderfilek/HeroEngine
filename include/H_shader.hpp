#ifndef HERO_SHADER_HPP
#define HERO_SHADER_HPP

#include<GL\glew.h>

#include<string.h>
#include<cstdlib>
#include<iostream>
#include<fstream>

#include"H_stdlib.hpp"

namespace Hero{
    class Shader
    {
    private:
        unsigned int glID;
    public:
        ~Shader();

        void Load(const std::string& path);
        void Bind();
        unsigned int GetGlID();
        unsigned int GetUniformLocation(const char* uniformName);
    };
}
#endif