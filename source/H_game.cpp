#include"H_game.hpp"

static void CheckLevel();
static void CloseLevel();

struct GameData
{
    Hero::Level* currentLevel;
    Hero::Level* nextLevel;
};

GameData* gameData;

namespace Hero
{
namespace Game
{

void Init(const char *title, int width, int height, int sdlflags)
{
    gameData = new GameData();

    Hero::Window::Engine::Init(title, width, height, sdlflags);

    Hero::Event::Engine::Init();

    Hero::Input::Engine::Init();

    Hero::Time::Engine::Init();    

}

void Close()
{
    //extern void Window_delete();
    Hero::Window::Engine::Delete();

    Hero::Event::Engine::Delete();

    Hero::Input::Engine::Delete();

    Hero::Time::Engine::Delete();
}

void Start(Level* startLevel)
{
    // Set next state, then i will be transfered to current state
    SetLevel(startLevel);
    

    uint32_t timer;
    double elapsed_time = 0.0f;

    // Quit is switch, when equel 1, loop end
    int quit = 0;
    while (quit >= 0)
    {
        Hero::Time::Engine::SetDeltaTime(elapsed_time);

        // Get actual timer
        timer = SDL_GetTicks();
        // Update current state
        CheckLevel();

        // Event loop
        quit = Hero::Event::Engine::Update();

        // Do state update function
        gameData->currentLevel->Update();

        // Do state draw function
        gameData->currentLevel->Draw();

        Hero::Window::Render();

        // Update inputs
        Hero::Input::Engine::Update();

        // Calculate elapsed time
        elapsed_time = (double)(SDL_GetTicks() - timer )/1000.0f;
    }
}

void SetLevel(Level* level)
{
    gameData->nextLevel = level;
}
}
}

void CheckLevel()
{
    // Check if next state exist
    if(gameData->nextLevel){

        // Check if current state exist
        if(gameData->currentLevel){

            gameData->currentLevel->Close();
            // Free current state memory
            delete gameData->currentLevel;
        }

        // Set next state to current state
        gameData->currentLevel = gameData->nextLevel;
        // Forget next state. It is not free, because now current state point to gameData memory area
        gameData->nextLevel = NULL;
        // Run start function of current state
        gameData->currentLevel->Start();
    }
}

void CloseLevel()
{

    // Check if current state exist
    if(gameData->currentLevel){

        gameData->currentLevel->Close();

        // Free current state memory
        delete gameData->currentLevel;
        gameData->currentLevel = NULL;
    }

    // Check if next state exist
    if(gameData->nextLevel){

        // Free current state memory
        delete gameData->nextLevel;
        gameData->nextLevel = NULL;
    }
}