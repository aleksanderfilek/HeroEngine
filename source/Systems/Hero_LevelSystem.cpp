#include"Systems/Hero_LevelSystem.hpp"

namespace Hero
{

const char* Level::name = "Level System";

Level::Level(ILevel* startLevel)
{
    this->nextLevel = startLevel;
}

Level::~Level()
{
    
}

void Level::Init()
{
    ISystem::Init();
}

void Level::Update()
{
    this->CheckLevel();
    this->currentLevel->Update();
}

void Level::Close()
{
    ISystem::Close();

    // Check if current state exist
    if(this->currentLevel){

        this->currentLevel->Close();

        // Free current state memory
        delete this->currentLevel;
        this->currentLevel = NULL;
    }

    // Check if next state exist
    if(this->nextLevel){

        // Free current state memory
        delete this->nextLevel;
        this->nextLevel = NULL;
    }
}

void Level::SetNextLevel(ILevel* nextLevel)
{
    this->nextLevel = nextLevel;
}

void Level::CheckLevel()
{
    // Check if next state exist
    if(this->nextLevel){

        // Check if current state exist
        if(this->currentLevel){

            this->currentLevel->Close();
            // Free current state memory
            delete this->currentLevel;
        }

        // Set next state to current state
        this->currentLevel = this->nextLevel;
        // Forget next state. It is not free, because now current state point to this memory area
        this->nextLevel = NULL;
        // Run start function of current state
        this->currentLevel->Init();
    }
}

}