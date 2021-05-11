#ifndef HERO_TEXTURE_CPP
#define HERO_TEXTURE_CPP

#include<string>
#include<vector>

#include"Hero_Config.hpp"
#include"Core/Hero_Utilities.hpp"
#include"Core/Hero_Math.hpp"

namespace Hero
{

enum TextureFlag : uint8_t
{
    Nearest = 0,
    Linear = 1,
    NoMipmap = 0,
    Mipmap =  128       
};

struct Texture
{
    unsigned int glId;
    int2 size;
    std::string name;
};

Texture* LoadTexture(const std::string& path, uint8_t textureFlags = 
        (uint8_t)TextureFlag::Linear | (uint8_t)TextureFlag::Mipmap);
void UnloadTexture(Texture* texture);
void BindTexture(const Texture* texture);
void UnbindTexture();

namespace Extra
{   

    Texture LoadTextureByCopy(const std::string& path, uint8_t textureFlags = 
        (uint8_t)TextureFlag::Linear | (uint8_t)TextureFlag::Mipmap);
    void UnloadTextureByCopy(Texture& texture);

}

}


#endif