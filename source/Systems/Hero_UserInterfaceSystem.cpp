#include"Systems/Hero_UserInterfaceSystem.hpp"

namespace Hero
{

const char* UserInterface::name = "UserInterface System"; 

UserInterface::UserInterface()
{

}

UserInterface::~UserInterface()
{

}

void UserInterface::Init()
{
    ISystem::Init();

    float* vertices = new float[8]
            {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, -1.0f};
    float* uvs = new float[8]
            {0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
    uint32_t* indices = new uint32_t[6]
            {0, 1, 2, 2, 1, 3};

    meshBufferF verticesBuff = {BufferType::vec2, vertices, 8};
    meshBufferF uvsBuff = {BufferType::vec2, uvs, 8};
    meshBufferI indicesBuff = {indices, 6};

    this->mesh = new Mesh();
    this->mesh->name = "uiSprite";
    mesh->buffers.push_back(verticesBuff);
    mesh->buffers.push_back(uvsBuff);
    mesh->indices = indicesBuff;

    this->shader = LoadShader("uiShader.glslbin");

}

void UserInterface::Update()
{

}

void UserInterface::Close()
{
    ISystem::Close();

    UnloadMesh(this->mesh);
    UnloadShader(this->shader);


}

}