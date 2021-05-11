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
            Mesh mesh = Extra::LoadMeshByCopy(this->addMeshes[i]);

            while(this->meshes[firstAvailable].first)
            {
                firstAvailable++;
            }
            this->meshes[firstAvailable].first = true;
            this->meshes[firstAvailable].second = mesh;
        }
        this->addMeshes.clear();
    }

    //shaders
    removedCount = this->removeShaders.size();

    if(this->removeShaders.size() > 0)
    {
        for(int i = 0; i < this->removeShaders.size(); i++)
        {
            uint32_t index = this->removeShaders[i];
            this->shaders[index].first = false;
            Extra::UnloadShaderByCopy(this->shaders[index].second);
        }
        this->removeShaders.clear();
    }

    if(this->addShaders.size() > 0)
    {
        uint32_t oldSize = this->shaders.size();
        uint32_t newSize = oldSize + this->addShaders.size() - removedCount;
        uint32_t firstAvailable = 0;

        this->shaders.resize(newSize);
        for(int i = 0; i < this->addShaders.size(); i++)
        {
            Shader shader = Extra::LoadShaderByCopy(this->addShaders[i]);

            while(this->shaders[firstAvailable].first)
            {
                firstAvailable++;
            }
            this->shaders[firstAvailable].first = true;
            this->shaders[firstAvailable].second = shader;
        }
        this->addShaders.clear();
    }

    //texture
    removedCount = this->removeTextures.size();

    if(this->removeTextures.size() > 0)
    {
        for(int i = 0; i < this->removeTextures.size(); i++)
        {
            uint32_t index = this->removeTextures[i];
            this->textures[index].first = false;
            Extra::UnloadTextureByCopy(this->textures[index].second);
        }
        this->removeTextures.clear();
    }

    if(this->addTextures.size() > 0)
    {
        uint32_t oldSize = this->shaders.size();
        uint32_t newSize = oldSize + this->addTextures.size() - removedCount;
        uint32_t firstAvailable = 0;

        this->textures.resize(newSize);
        for(int i = 0; i < this->addTextures.size(); i++)
        {
            Texture texture = Extra::LoadTextureByCopy(this->addTextures[i]);

            while(this->textures[firstAvailable].first)
            {
                firstAvailable++;
            }
            this->textures[firstAvailable].first = true;
            this->textures[firstAvailable].second = texture;
        }
        this->addTextures.clear();
    }

}

void Resources::Close()
{
    ISystem::Close();
    this->Clear();
}


void Resources::AddMesh(const std::string& path)
{
    for(int i = 0; i < this->meshes.size(); i++)
    {
        if(this->meshes[i].first && this->meshes[i].second.name.compare(path))
        {
            return;
        }
    }

    for(int i = 0; i < this->addMeshes.size(); i++)
    {
        if(this->addMeshes[i].compare(path))
        {
            return;
        }
    }

    this->addMeshes.push_back(path);
}

void Resources::RemoveMeshByName(const std::string& name)
{
    for(int i = 0; i < this->meshes.size(); i++)
    {
        std::pair<bool, Mesh>& mesh = this->meshes[i];
        if(mesh.first && mesh.second.name.compare(name))
        {
            this->removeMeshes.push_back(i);
        }
    }
}

Mesh* Resources::GetMeshByName(const std::string& name)
{
    for(auto& mesh: this->meshes)
    {
        if(mesh.first && mesh.second.name.compare(name))
        {
            return &mesh.second;
        }
    }

    return nullptr;
}

void Resources::AddShader(const std::string& path)
{
    for(int i = 0; i < this->shaders.size(); i++)
    {
        if(this->shaders[i].first && this->shaders[i].second.name.compare(path))
        {
            return;
        }
    }

    for(int i = 0; i < this->addShaders.size(); i++)
    {
        if(this->addShaders[i].compare(path))
        {
            return;
        }
    }

    this->addShaders.push_back(path);
}

void Resources::RemoveShaderByName(const std::string& name)
{
    for(int i = 0; i < this->shaders.size(); i++)
    {
        std::pair<bool, Shader>& shader = this->shaders[i];
        if(shader.first && shader.second.name.compare(name))
        {
            this->removeShaders.push_back(i);
        }
    }
}

Shader* Resources::GetShaderByName(const std::string& name)
{
    for(auto& shader: this->shaders)
    {
        if(shader.first && shader.second.name.compare(name))
        {
            return &shader.second;
        }
    }

    return nullptr;
}

void Resources::AddTexture(const std::string& path)
{
    for(int i = 0; i < this->textures.size(); i++)
    {
        if(this->textures[i].first && this->textures[i].second.name.compare(path))
        {
            return;
        }
    }

    for(int i = 0; i < this->addTextures.size(); i++)
    {
        if(this->addTextures[i].compare(path))
        {
            return;
        }
    }

    this->addTextures.push_back(path);
}

void Resources::RemoveTextureByName(const std::string& name)
{
    for(int i = 0; i < this->textures.size(); i++)
    {
        std::pair<bool, Texture>& texture = this->textures[i];
        if(texture.first && texture.second.name.compare(name))
        {
            this->removeTextures.push_back(i);
        }
    }
}

Texture* Resources::GetTextureByName(const std::string& name)
{
    for(auto& texture: this->textures)
    {
        if(texture.first && texture.second.name.compare(name))
        {
            return &texture.second;
        }
    }

    return nullptr;
}

void Resources::Clear()
{
    for(auto& element: this->meshes)
    {
        element.first = false;
        Extra::UnloadMeshByCopy(element.second);
    }
    this->meshes.clear();

    for(auto& element: this->shaders)
    {
        element.first = false;
        Extra::UnloadShaderByCopy(element.second);
    }
    this->shaders.clear();

    for(auto& element: this->textures)
    {
        element.first = false;
        Extra::UnloadTextureByCopy(element.second);
    }
    this->textures.clear();
}

}