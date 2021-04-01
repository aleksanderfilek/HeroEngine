#include"H_game.hpp"

namespace Hero
{

Game* Game::instance = nullptr;

Game::Game(const char *title, int width, int height, int sdlflags)
{
    instance = this;

    this->windowSystem = new WindowSystem(title, width, height, sdlflags);

    this->eventSystem = new EventSystem();

    this->inputSystem = new InputSystem();

    this->globalTime = new Time();

    this->renderer = new Renderer2D(width, height);

    #if RUNTIME_INJECTION == 1
        this->runtimeInjection = new Event();
    #endif
}

Game::~Game()
{
    this->CloseLevel();

    delete this->windowSystem;

    delete this->eventSystem;

    delete this->inputSystem;

    delete this->globalTime;

    delete this->renderer;

    #if RUNTIME_INJECTION == 1
        delete this->runtimeInjection;
    #endif
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
        this->globalTime->SetDeltaTime(elapsed_time);

        // Get actual timer
        timer = SDL_GetTicks();
        // Update current state
        CheckLevel();

        #if RUNTIME_INJECTION == 1
            this->runtimeInjection->Invoke(nullptr, nullptr, 0);
        #endif

        // Event loop
        quit = this->eventSystem->Update();

        // Do state update function
        this->currentLevel->Update();

        // Do state draw function
        this->currentLevel->Draw();

        this->windowSystem->Render();

        // Update inputs
        this->inputSystem->Update();

        // Calculate elapsed time
        elapsed_time = (double)(SDL_GetTicks() - timer)/1000.0f;

        #if FPS_COUNTER == 1
            double fps = 1000.0/(SDL_GetTicks() - timer);
            std::cout<<"fps: "<<fps<<std::endl;
        #endif
    }
}

WindowSystem* Game::GetWindowSystem()
{
    return instance->windowSystem;
}

EventSystem* Game::GetEventSystem()
{
    return instance->eventSystem;
}

InputSystem* Game::GetInputSystem()
{
    return instance->inputSystem;
}

void Game::SetLevel(Level* level)
{
    instance->nextLevel = level;
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