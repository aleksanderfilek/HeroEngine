#include"H_game.hpp"

namespace Hero
{

Game::Game(const char *title, int width, int height, int sdlflags)
{
    this->window = new Window(title, width, height, sdlflags);

    Hero::Event::Engine::Init();

    Hero::Input::Engine::Init();

    Hero::Time::Engine::Init();    
}

Game::~Game()
{
    delete this->window;

    Hero::Event::Engine::Delete();

    Hero::Input::Engine::Delete();

    Hero::Time::Engine::Delete();
}

void Game::Start(Level* startLevel)
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
        this->currentLevel->Update();

        // Do state draw function
        this->currentLevel->Draw();

        this->window->Render();

        // Update inputs
        Hero::Input::Engine::Update();

        // Calculate elapsed time
        elapsed_time = (double)(SDL_GetTicks() - timer )/1000.0f;
    }
}

Window* Game::GetWindow()
{
    return this->window;
}

void Game::SetLevel(Level* level)
{
    this->nextLevel = level;
}

void Game::CheckLevel()
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
        this->currentLevel->Start();
    }
}

void Game::CloseLevel()
{

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

}