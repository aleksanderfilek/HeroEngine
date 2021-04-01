#include"world.hpp"

void World::Start()
{   
    this->defaultTexture = new Hero::Texture();
    this->defaultTexture->Load("example/resources/textures/button.png");

    this->groundMesh = new Hero::Mesh();
    this->groundMesh->Load("example/resources/models/ground.daebin");

    this->standardShader = new Hero::Shader();
    this->standardShader->Load("example/resources/shaders/standardShader.glslbin");

    this->standardShader->Bind();
    unsigned int modelLoc = this->standardShader->GetUniformLocation("model");
    unsigned int viewLoc = this->standardShader->GetUniformLocation("view");
    unsigned int projectionLoc = this->standardShader->GetUniformLocation("proj");

    this->camera = new Camera(viewLoc, projectionLoc);
    this->camera->SetProjection(1280, 720, 60.0f, 0.1f, 1000.0f);
    Hero::float3 postion = {0.0f, 2.0f, 0.0f};
    Hero::float3 target = {0.0f, 0.0f, 1.0f};
    this->camera->SetPosition(postion);
    this->camera->SetLookAtTarget(target);

    this->defaultTexture->Bind();

    Hero::matrix4x4 model;
    Hero::matrix_identity(model);
    Hero::matrix_scale(model, {100.0f, 100.0f, 100.0f});
    Hero::matrix_rotateAxisX(model, Hero::deg2rad(90.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model.v[0].x);  
}

void World::Update()
{
    Hero::float3 deltaPosition = {0.0f, 0.0f, 0.0f};
    if(Hero::Input::keyPressed(Hero::Input::W))
    {
        Hero::float3 f = {0.0f, 0.0f, 1.0f};
        deltaPosition = Hero::add(deltaPosition, f);
    }
    else if(Hero::Input::keyPressed(Hero::Input::S))
    {
        Hero::float3 f = {0.0f, 0.0f, 1.0f};
        deltaPosition = Hero::substract(deltaPosition, f);
    }
    if(Hero::Input::keyPressed(Hero::Input::D))
    {
        Hero::float3 f = {1.0f, 0.0f, 0.0f};
        deltaPosition = Hero::add(deltaPosition, f);
    }
    else if(Hero::Input::keyPressed(Hero::Input::A))
    {
        Hero::float3 f = {1.0f, 0.0f, 0.0f};
        deltaPosition = Hero::substract(deltaPosition, f);
    }

    Hero::float3 newPos = Hero::add(deltaPosition, this->camera->GetPosition());

    this->camera->SetPosition(newPos);

    this->camera->Update();
}

void World::Draw()
{
    Hero::ClearRenderer();

    groundMesh->Draw();
}

void World::Close()
{
    delete this->defaultTexture;
    delete this->groundMesh;
    delete this->standardShader;
}