#include"Systems/Hero_ResourcesSystem.hpp"

namespace Hero
{

const char* Resources::name = "Resources System";

Resources::Resources()
{

}

Resources::~Resources()
{

}

void Resources::Init()
{
    ISystem::Init();
}

void Resources::Update()
{
    if(this->removeMeshes.size() > 0)
    {
        for(int i = 0; i < this->removeMeshes.size(); i++)
        {
            uint32_t index = this->removeMeshes[i];
            this->meshes[index].first = false;
            UnloadMesh(this->meshes[index].second);
        }
        this->removeMeshes.clear();
    }

    if(this->addMeshes.size() > 0)
    {
        uint32_t oldSize = this->meshes.size();
        uint32_t newSize = oldSize + this->addMeshes.size(); // substract amount of removed elements
        uint32_t firstFree = 0;

        this->meshes.resize(newSize);
        for(int i = 0; i < this->addMeshes.size(); i++)
        {
            Mesh mesh = LoadMesh(this->addMeshes[i].first);

            while(this->meshes[firstFree].first)
            {
                firstFree++;
            }
            *this->addMeshes[i].second = firstFree + 1;
            this->meshes[firstFree].first = true;
            this->meshes[firstFree].second = mesh;
        }
        this->addMeshes.clear();
    }

}

void Resources::Close()
{
    ISystem::Close();
}

void Resources::AddMesh(const std::string& path, uint32_t* ptrIndex)
{
    *ptrIndex = 0;
    this->addMeshes.push_back({path, ptrIndex});
}

void Resources::RemoveMesh(uint32_t index)
{
    this->removeMeshes.push_back(index - 1);
}

Mesh* Resources::GetMesh(uint32_t index)
{
    if(index == 0 || this->meshes[index - 1].first == false)
    {
        return nullptr;
    }
    else
    {
        return &this->meshes[index - 1].second;
    }
}

void Resources::AddTexture(const std::string& path, uint32_t* ptrIndex)
{
    *ptrIndex = 0;
    this->addTextures.push_back({path, ptrIndex});
}

void Resources::RemoveTexture(uint32_t index)
{
    this->removeTextures.push_back(index - 1);
}

Texture* Resources::GetTexture(uint32_t index)
{
    if(index == 0 || this->textures[index - 1].first == false)
    {
        return nullptr;
    }
    else
    {
        return &this->textures[index - 1].second;
    }
}

void Resources::AddShader(const std::string& path, uint32_t* ptrIndex)
{
    *ptrIndex = 0;
    this->addShaders.push_back({path, ptrIndex});
}

void Resources::RemoveShader(uint32_t index)
{
    this->removeShaders.push_back(index - 1);
}

Shader* Resources::GetShader(uint32_t index)
{
    if(index == 0 || this->shaders[index - 1].first == false)
    {
        return nullptr;
    }
    else
    {
        return &this->shaders[index - 1].second;
    }
}

}