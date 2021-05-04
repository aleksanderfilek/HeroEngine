#ifndef HERO_RESOURCES_HPP
#define HERO_RESOURCES_HPP

#include<iostream>
#include<string>
#include<fstream>
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

struct Shader
{
    unsigned int glId;
    std::string name;
};

Shader* LoadShader(const std::string& path);
void UnloadShader(Shader* shader);
void BindShader(const Shader* shader);

enum BufferType : uint8_t
{
    single = 1,
    vec2 = 2,
    vec3 = 3
};

struct meshBufferF
{
    BufferType type;
    float* array;
    uint32_t length;
};

struct meshBufferI
{
    uint32_t* array;
    uint32_t length;
};

struct Mesh
{
    std::string name;

    uint32_t VAO, VBO, EBO;
    std::vector<meshBufferF> buffers;

    meshBufferI indices;
};

Mesh* LoadMeshRef(const std::string& path);
Mesh LoadMesh(const std::string& path);
void UnloadMeshRef(Mesh* mesh);
void UnloadMesh(Mesh& mesh);
void DrawMesh(const Mesh* mesh);
void GenerateMesh(Mesh* mesh);

}

#endif