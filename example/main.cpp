#include<iostream>

#include"Hero.hpp"
#include<cmath>

class Scene:public Hero::Level
{
public:
    Hero::Mesh mesh;
    Hero::Shader shader;
    //Hero::Texture texture;
    Hero::Text *text;
    Hero::Font *font;

    Scene()
    {

    }

    ~Scene()
    {

    }

    void Start()
    {
        shader.Load("example/shader.glslbin");

        mesh.Load("example/plane.daebin");

        //texture.Load("example/default.png");

        font = new Hero::Font("example/arial.ttf", 28);

        Hero::Color color = {0, 0, 255, 255};

        text = new Hero::Text(font);
        text->SetColor(color);
        text->SetText("Hello, World!");

        shader.Bind();

        text->Draw();

        //texture.Bind();

    }

    void Update()
    {
        if(Hero::Input::keyUp(Hero::Input::KeyCode::A)) // sprawdzenie czy klawisz A został przytrzymany
        { 
            std::cout<<"klik"<<std::endl;
        }
    }

    void Draw()
    {

        glClear(GL_COLOR_BUFFER_BIT);

        mesh.Draw();
        DEBUG_CODE(glCheckError();)

    }

    void Close()
    {
        delete text;
        delete font;
    } 
};

int main(int argc, char *argv[])
{

    Hero::Game game("Test", 640, 480);

    Scene* startlevel = new Scene(); // stworzenie początkowego levelu

    game.Start(startlevel); // uruchomienie silnika

    return 0;
}


















