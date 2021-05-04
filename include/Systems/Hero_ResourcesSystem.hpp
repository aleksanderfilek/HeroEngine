#ifndef HERO_RESOURCES_SYSTEM_HPP
#define HERo_RESOURCES_SYSTEM_HPP

#include<vector>
#include<string>

#include"Core/Hero_System.hpp"
#include"Core/Hero_Resources.hpp"

namespace Hero
{


class Resources : public ISystem
{
private:
    std::vector<std::pair<bool, Mesh>> meshes;
    std::vector<std::pair<bool, Texture>> textures;
    std::vector<std::pair<bool, Shader>> shaders;

    std::vector<std::pair<const std::string&, uint32_t*>> addMeshes;
    std::vector<uint32_t> removeMeshes;
    std::vector<std::pair<const std::string&, uint32_t*>> addTextures;
    std::vector<uint32_t> removeTextures;
    std::vector<std::pair<const std::string&, uint32_t*>> addShaders;
    std::vector<uint32_t> removeShaders;

public:
    Resources();
    ~Resources();

    void Init();
    void Update();
    void Close();

    static const char* name; 
    const char* GetName(){ return name; }

    void AddMesh(const std::string& path, uint32_t* ptrIndex);
    void AddTexture(const std::string& path, uint32_t* ptrIndex);
    void AddShader(const std::string& path, uint32_t* ptrIndex);

    void RemoveMesh(uint32_t index);
    void RemoveTexture(uint32_t index);
    void RemoveShader(uint32_t index);

    Mesh* GetMesh(uint32_t index);
    Texture* GetTexture(uint32_t index);
    Shader* GetShader(uint32_t index);

    void RebuildMesh();

    void Clear();
};

}

#endif