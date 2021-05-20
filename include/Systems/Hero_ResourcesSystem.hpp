#ifndef HERO_RESOURCES_SYSTEM_HPP
#define HERO_RESOURCES_SYSTEM_HPP

#include<vector>
#include<string>
#include<fstream>

#include"Core/Hero_System.hpp"
#include"Core/Hero_Mesh.hpp"
#include"Core/Hero_Texture.hpp"
#include"Core/Hero_Shader.hpp"



namespace Hero
{

class Resources : public ISystem
{
private:
    std::vector<std::pair<bool, Mesh>> meshes;
    std::vector<std::string> addMeshes;
    std::vector<uint32_t> removeMeshes;

    std::vector<std::pair<bool, Shader>> shaders;
    std::vector<std::string> addShaders;
    std::vector<uint32_t> removeShaders;

    std::vector<std::pair<bool, Texture>> textures;
    std::vector<std::string> addTextures;
    std::vector<uint32_t> removeTextures;

public:
    Resources();
    ~Resources();

    void Init();
    void Update();
    void Close();

    static const char* name; 
    const char* GetName(){ return name; }

    std::uint8_t priority(){ return 10; }

    void AddMesh(const std::string& path);
    void RemoveMeshByName(const std::string& name);
    Mesh* GetMeshByName(const std::string& name);

    void AddShader(const std::string& path);
    void RemoveShaderByName(const std::string& name);
    Shader* GetShaderByName(const std::string& name);

    void AddTexture(const std::string& path);
    void RemoveTextureByName(const std::string& name);
    Texture* GetTextureByName(const std::string& name);

    // TODO: in future
    //void LoadFromFile(const std::string& path);

    void Clear();
};

//#define RegisterResourceType()

}

#endif