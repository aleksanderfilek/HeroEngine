#include"world.hpp"

#define CheckIndices(x,y) x >= 0 && x < SECTOR_COUNT && y >= 0 && y < SECTOR_COUNT

static void CalculateSectors(const Camera* camera, Sector** sectors);

void World::OnStart()
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

    this->player = new Player(modelLoc);

    this->camera = new Camera(viewLoc, projectionLoc);
    this->camera->SetProjection(1280, 720, 60.0f, 0.1f, 1000.0f);
    this->camera->Start();
    this->camera->SetTarget(this->player->GetPositionRef());

    this->player->SetCamera(this->camera);

    this->sectors = new Sector*[SECTOR_COUNT];
    for(int i = 0; i < SECTOR_COUNT; i++)
    {
        this->sectors[i] = new Sector[SECTOR_COUNT]
        {
            { this->groundMesh, modelLoc, {(float)i, 0.0f, 0.0f} },
            { this->groundMesh, modelLoc, {(float)i, 0.0f, 1.0f} },
            { this->groundMesh, modelLoc, {(float)i, 0.0f, 2.0f} },
            { this->groundMesh, modelLoc, {(float)i, 0.0f, 3.0f} },
            { this->groundMesh, modelLoc, {(float)i, 0.0f, 4.0f} }
        };
    }

    player->Start();
}

void World::OnUpdate()
{

    this->player->Update();
    this->camera->Update();   

    CalculateSectors(this->camera, this->sectors);
}

void World::OnDraw()
{
    Hero::ClearRenderer();

    this->defaultTexture->Bind();
    for(int x = 0; x < SECTOR_COUNT; x++)
    {
        for(int y = 0; y < SECTOR_COUNT; y++)
        {
            this->sectors[x][y].Draw();
        }
    }

    this->player->Draw();
}

void World::OnClose()
{
    this->player->Close();

    delete this->defaultTexture;
    delete this->groundMesh;
    delete this->standardShader;
    delete this->camera;

    for(int i = 0; i < SECTOR_COUNT; i++)
    {
        delete[] this->sectors[i];
    }
    delete[] this->sectors;
}

void CalculateSectors(const Camera* camera, Sector** sectors)
{
    for(int x = 0; x < SECTOR_COUNT; x++)
    {
        for(int y = 0; y < SECTOR_COUNT; y++)
        {
            sectors[x][y].SetVisible(false);
        }
    }

    Hero::int2 indices = camera->GetSectorIndices();

    for(int x = -1; x < 2; x++)
    {
        for(int y = -1; y < 2; y++)
        {
            if(CheckIndices(indices.x - x, indices.y - y)){
                sectors[indices.x - x][indices.y -y].SetVisible(true);
            }
        }
    }
}
