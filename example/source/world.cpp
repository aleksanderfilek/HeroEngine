#include"world.hpp"

event(kolizja)
{
    std::cout<<"Kolizja"<<std::endl;
}

void World::OnStart()
{   
    this->basicShader = new Hero::Shader();
    this->basicShader->Load("example/resources/shaders/standardShader.glslbin");
    this->basicShader->Bind();
    unsigned int modelLoc = this->basicShader->GetUniformLocation("model");
    unsigned int viewLoc = this->basicShader->GetUniformLocation("view");
    unsigned int projLoc = this->basicShader->GetUniformLocation("proj");
    unsigned int lightDirLoc = this->basicShader->GetUniformLocation("lightDir");
    unsigned int lightColorLoc = this->basicShader->GetUniformLocation("lightColor");

    this->player = new Player(modelLoc);

    this->camera = new Camera(viewLoc, projLoc);
    this->camera->SetTarget(this->player->GetPositionRef());

    this->worldUI = new WorldUI(this->player);

    this->sun = new Sun();
    Hero::Color color = {244,240,230,0};
    this->sun->SetColor(color);
    Hero::float3 dir = {1.0f, -1.0f, 1.0f};
    this->sun->SetDirection(dir);

    this->stone1Mesh = new Hero::Mesh();
    this->stone1Mesh->Load("example/resources/models/enviro/stone1.daebin");

    this->stone1Texture = new Hero::Texture();
    this->stone1Texture->Load("example/resources/textures/stone1.png");

    Hero::matrix_identity(this->stoneMatrix);
    Hero::matrix_translate(this->stoneMatrix, {10.0f, 0.2f, 0.0f});

    this->grassShader = new Hero::Shader();
    this->grassShader->Load("example/resources/shaders/grassShader.glslbin");

    this->groundMesh = new Hero::Mesh();
    this->groundMesh->Load("example/resources/models/plane.daebin");

    this->groundTexture = new Hero::Texture();
    this->groundTexture->Load("example/resources/textures/grass.png");

    Hero::matrix_identity(this->groundMatrix);
    Hero::matrix_scale(this->groundMatrix, {100.0f, 100.0f, 100.0f});
    Hero::matrix_rotateAxisX(this->groundMatrix, Hero::deg2rad(-90.0f));
    Hero::matrix_translate(this->groundMatrix, {-50.0f, 0.0f, 50.0f});

    this->trigger = new Trigger(this->player->GetPositionRef());
    this->trigger->SetPosition({-1.0f, 0.0f, 5.0f});
    this->trigger->SetSize({2.0f, 2.0f, 2.0f});
    this->trigger->AddEvent(kolizja);

    this->player->Start();
    this->camera->Start();
    this->worldUI->Start();
}

void World::OnUpdate()
{

    this->player->Update();
    this->camera->Update();
    this->worldUI->Update();
    this->trigger->Update();
}

void World::OnDraw()
{
    Hero::ClearRenderer();

    glEnable(GL_DEPTH_TEST);
    this->basicShader->Bind();
    this->camera->BindProjectionMatrix(this->basicShader->GetUniformLocation("proj"));
    glCheckError();
    this->camera->Draw();
    this->sun->Bind(this->basicShader->GetUniformLocation("lightDir"),this->basicShader->GetUniformLocation("lightColor"));
    this->player->Draw();

    this->stone1Texture->Bind();
    glUniformMatrix4fv(this->basicShader->GetUniformLocation("model"), 1, GL_FALSE,
            &this->stoneMatrix.v[0].x);
            glCheckError();
    this->stone1Mesh->Draw();

    this->grassShader->Bind();
    this->sun->Bind(this->grassShader->GetUniformLocation("lightDir"),this->grassShader->GetUniformLocation("lightColor"));
    this->camera->BindViewMatrix(this->grassShader->GetUniformLocation("view"));
    glCheckError();
    this->camera->BindProjectionMatrix(this->grassShader->GetUniformLocation("proj"));
    glCheckError();
    this->groundTexture->Bind();
    glUniformMatrix4fv(this->basicShader->GetUniformLocation("model"), 1, GL_FALSE,
            &this->groundMatrix.v[0].x);
    glCheckError();
    glUniform1f(this->grassShader->GetUniformLocation("scale"), 10.0f);
    glCheckError();
    this->groundMesh->Draw();

    glDisable(GL_DEPTH_TEST);

    this->worldUI->Draw();
}

void World::OnClose()
{
    this->player->Close();
    delete this->player;

    this->camera->Close();
    delete this->camera;

    this->worldUI->Close();
    delete this->worldUI;

    delete this->stone1Mesh;
    delete this->stone1Texture;

    delete this->groundMesh;
    delete this->groundTexture;

    delete this->basicShader;
    delete this->grassShader;
}