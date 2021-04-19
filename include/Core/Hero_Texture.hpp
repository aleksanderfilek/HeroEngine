#ifndef HERO_TEXTURE_HPP
#define HERO_TEXTURE_HPP

#include<iostream>
#include<string>
#include<cstdint>

#include"Core/Hero_Config.hpp"
#include"Core/Hero_Utilities.hpp"
#include"Core/Hero_Math.hpp"

namespace Hero
{

class Texture
{
private:
    unsigned int _glId;
    int2 _size;

public:
    enum class TextureFlag : std::uint8_t
    {
        Nearest = 0,
        Linear = 1,
        NoMipmap = 0,
        Mipmap =  128       
    };

    Texture(const std::string& path, std::uint8_t textureFlags = 
        (std::uint8_t)TextureFlag::Linear | (std::uint8_t)TextureFlag::Mipmap);
    ~Texture();

    void Bind();
    static void Unbind();

    int2 GetSize(){ return this->_size; }
    unsigned int GetGlID(){ return this->_glId; }
};

}

#endif