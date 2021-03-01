#include<iostream>

#include"Hero.hpp"
#include<cmath>

class Scene:public Hero::Level
{
public:
    Hero::Mesh mesh;
    Hero::Shader shader;
    Hero::Texture texture;

    Scene()
    {

    }

    ~Scene()
    {

    }

    void Start()
    {
        shader.Load("example/shader.glslbin");

        mesh.Load("example/sphere.daebin");

        texture.Load("example/default.png");

        shader.Bind();

        texture.Bind();

    }

    void Update()
    {
        if(Hero::Input::keyUp(Hero::Input::KeyCode::A)) // sprawdzenie czy klawisz A został przytrzymany
        { 

        }
    }

    void Draw()
    {

        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();

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


















