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
    // mesh 
    uint32_t removedCount = this->removeMeshes.size();

    if(this->removeMeshes.size() > 0)
    {
        for(int i = 0; i < this->removeMeshes.size(); i++)
        {
            uint32_t index = this->removeMeshes[i];
            this->meshes[index].first = false;
            Extra::UnloadMeshByCopy(this->meshes[index].second);
        }
        this->removeMeshes.clear();
    }

    if(this->addMeshes.size() > 0)
    {
        uint32_t oldSize = this->meshes.size();
        uint32_t newSize = oldSize + this->addMeshes.size() - removedCount;
        uint32_t firstAvailable = 0;

        this->meshes.resize(newSize);
        for(int i = 0; i < this->addMeshes.size(); i++)
        {
            Mesh mesh = Extra::LoadMeshByCopy(this->addMeshes[i].first);

            while(this->meshes[firstAvailable].first)
            {
                firstAvailable++;
            }
            *this->addMeshes[i].second = firstAvailable + 1;
            this->meshes[firstAvailable].first = true;
            this->meshes[firstAvailable].second = mesh;
        }
        this->addMeshes.clear();
    }

    // texture
    removedCount = this->removeTextures.size();

    if(this->removeTextures.size() > 0)
    {
        for(int i = 0; i < this->removeTextures.size(); i++)
        {
            uint32_t index = this->removeTextures[i];
            this->textures[index].first = false;
            //UnloadMesh(this->textures[index].second);
        }
        this->removeTextures.clear();
    }

    if(this->addTextures.size() > 0)
    {
        uint32_t oldSize = this->textures.size();
        uint32_t newSize = oldSize + this->addTextures.size() - removedCount;
        uint32_t firstAvailable = 0;

        this->textures.resize(newSize);
        for(int i = 0; i < this->addTextures.size(); i++)
        {
            //Texture texture = LoadMesh(this->addTextures[i].first);

            while(this->textures[firstAvailable].first)
            {
                firstAvailable++;
            }
            *this->addTextures[i].second = firstAvailable + 1;
            this->textures[firstAvailable].first = true;
            //this->textures[firstAvailable].second = texture;
        }
        this->addTextures.clear();
    }

    // shader
    removedCount = this->removeShaders.size();

    if(this->removeShaders.size() > 0)
    {
        for(int i = 0; i < this->removeShaders.size(); i++)
        {
            uint32_t index = this->removeShaders[i];
            this->shaders[index].first = false;
            //UnloadMesh(this->shaders[index].second);
        }
        this->removeMeshes.clear();
    }

    if(this->addShaders.size() > 0)
    {
        uint32_t oldSize = this->shaders.size();
        uint32_t newSize = oldSize + this->addShaders.size() - removedCount;
        uint32_t firstAvailable = 0;

        this->shaders.resize(newSize);
        for(int i = 0; i < this->addShaders.size(); i++)
        {
            //Shader shader = LoadMesh(this->addShaders[i].first);

            while(this->shaders[firstAvailable].first)
            {
                firstAvailable++;
            }
            *this->addShaders[i].second = firstAvailable + 1;
            this->shaders[firstAvailable].first = true;
            //this->shaders[firstAvailable].second = shader;
        }
        this->addShaders.clear();
    }

}

void Resources::Close()
{
    ISystem::Close();
    this->Clear();
}

void Resources::AddMesh(const std::string& path, uint32_t* ptrIndex)
{
    *ptrIndex = 0;
    this->addMeshes.push_back({path, ptrIndex});
}

void Resources::RemoveMesh(uint32_t index)
{
    if(index <= this->meshes.size() && this->meshes[index - 1].first)
    {
        this->removeMeshes.push_back(index - 1);
    }
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
    if(index <= this->textures.size() && this->textures[index - 1].first)
    {
        this->removeTextures.push_back(index - 1);
    }
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
    if(index <= this->shaders.size() && this->shaders[index - 1].first)
    {
        this->removeShaders.push_back(index - 1);
    }
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

void Resources::Clear()
{
    this->meshes.clear();
    this->textures.clear();
    this->shaders.clear();
}

}