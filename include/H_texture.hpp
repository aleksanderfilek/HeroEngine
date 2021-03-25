#ifndef HERO_TEXTURE_HPP
#define HERO_TEXTURE_HPP

#include"H_defines.hpp"

#include<string>
#include<iostream>

#include"H_math.hpp"
#include"H_stdlib.hpp"

namespace Hero
{
    class Texture
    {
    private:
        unsigned int glId;
        int2 size;

        static unsigned int bindedTexturesCount;
    public:
        Texture();
        Texture(const std::string& path);
        ~Texture();

        void Load(const std::string& path);
        void Bind();
        static void Unbind();

        int2 GetSize();
        unsigned int GetGlID();
    };
}

#endif