#include<iostream>

#include"Hero.hpp"
#include<stdio.h>

class Scene:public Hero::Level
{
public:
    Scene()
    {

    }

    ~Scene()
    {

    }

    void Start()
    {

    }

    void Update()
    {
        if(Hero::Input::keyPressed(Hero::Input::Key::KeyCode_A)) // sprawdzenie czy klawisz A został przytrzymany
        { 
            // wysłanie eventu o zamknięciu okna
            SDL_Event sdlevent;
            sdlevent.type = SDL_QUIT;
            SDL_PushEvent(&sdlevent);
        }
    }

    void Draw()
    {

    }

    void Close()
    {

    } 
};

int main(int argc, char *argv[])
{
    Hero::Game::Init("Test", 640, 480); // inicjalizacja silnika i tworzenie okna

    Scene* startlevel = new Scene(); // stworzenie początkowego levelu

    Hero::Game::Start(startlevel); // uruchomienie silnika

    Hero::Game::Close(); // zamknięcie silnika

    return 0;
}


















