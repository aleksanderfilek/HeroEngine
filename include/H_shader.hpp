#ifndef HERO_SHADER_HPP
#define HERO_SHADER_HPP

#include"H_stdlib.hpp"

#include"glew.h"

namespace Hero{
    typedef unsigned int ShaderId;

    class ShaderManager
    {
    private:
        unsigned int allocatedElements;
        char** name;
        unsigned int* glId;
    public:
        ShaderManager(unsigned int size);
        ~ShaderManager();

        ShaderId LoadShader(const char* path);
        void DeleteShader(ShaderId id);
        void BindShader(ShaderId id);
        int GetShaderId(const char* path);
        unsigned int GetUniformLocation(ShaderId id, const char* uniformName);

    };
}
#endif