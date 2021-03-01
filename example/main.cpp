#include<iostream>

#include"Hero.hpp"
#include<cmath>

class Scene:public Hero::Level
{
public:
    Hero::Mesh mesh;
    Hero::ShaderManager manager;
    double time = 0;

    Scene()
    {

    }

    ~Scene()
    {

    }

    void Start()
    {
        unsigned int i = manager.LoadShader("example/shader.glslbin");

        manager.BindShader(i);

        mesh.Load("example/sphere.daebin");
    }

    void Update()
    {
        time += Hero::Time::GetDeltaTime();
        if(Hero::Input::keyUp(Hero::Input::KeyCode::A)) // sprawdzenie czy klawisz A został przytrzymany
        { 

        }
    }

    void Draw()
    {

        glClear(GL_COLOR_BUFFER_BIT);

        mesh.Draw();
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


















