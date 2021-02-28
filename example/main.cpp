#include<iostream>

#include"Hero.hpp"

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
        Hero::ShaderManager manager;
        manager.LoadShader("shader.glslbin");
    }

    void Update()
    {
        if(Hero::Input::keyUp(Hero::Input::KeyCode::A)) // sprawdzenie czy klawisz A został przytrzymany
        { 

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


















