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
    Hero::Game game("Test", 640, 480);

    Scene* startlevel = new Scene(); // stworzenie początkowego levelu

    game.Start(startlevel); // uruchomienie silnika

    return 0;
}


















