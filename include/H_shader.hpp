#ifndef HERO_SHADER_HPP
#define HERO_SHADER_HPP

#include<GL\glew.h>

#include<string.h>
#include<cstdlib>
#include<iostream>
#include<fstream>

namespace Hero{
    typedef unsigned int ShaderId;

    class ShaderManager
    {
    private:
        unsigned int allocatedElements;
        char** name;
        unsigned int* glId;
    public:
        ShaderManager(unsigned int size = 0);
        ~ShaderManager();

        ShaderId LoadShader(const char* path);
        void DeleteShader(ShaderId id);
        void BindShader(ShaderId id);
        int GetShaderId(const char* path);
        unsigned int GetUniformLocation(ShaderId id, const char* uniformName);

    };
}
#endif