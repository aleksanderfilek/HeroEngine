#ifndef HERO_MESH_CPP
#define HERO_MESH_CPP

#include<string>
#include<vector>
#include<fstream>

#include"Hero_Config.hpp"
#include"Core/Hero_Utilities.hpp"

namespace Hero
{

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

Mesh* LoadMesh(const std::string& path);
void UnloadMesh(Mesh* mesh);
void DrawMesh(const Mesh* mesh);
void GenerateMesh(Mesh* mesh);

namespace Extra
{
    Mesh LoadMeshByCopy(const std::string& path);
    void UnloadMeshByCopy(Mesh& mesh);
}

}

#endif