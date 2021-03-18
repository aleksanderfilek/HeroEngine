#include<iostream>

#include"Hero.hpp"
#include<cmath>

class Scene:public Hero::Level
{
public:
    Hero::Shader shader;
    Hero::Group group;
    //Hero::Texture texture;
    Hero::Font *font;
    unsigned int ColorLoc;
    double timer = 0.0;

    Scene()
    {

    }

    ~Scene()
    {

    }

    void Start()
    {

        shader.Load("example/shader.glslbin");
        Hero::Renderer2D::SetShader(&shader);

        font = new Hero::Font("example/arial.ttf", 28);

        Hero::Color color = {255, 255, 255, 255};

        Hero::Text* text = new Hero::Text(font);
        text->SetColor(color);
        text->SetText("Hello, World!");

        Hero::Text* text2 = new Hero::Text(font);
        text2->SetColor(color);
        text2->SetText("Alek jest sexi!!!");
        text2->SetRelativePosition({200, 200});

        group.Add(text);
        group.Add(text2);

        ColorLoc = shader.GetUniformLocation("color");
        
    }

    void Update()
    {
        if(Hero::Input::keyPressed(Hero::Input::KeyCode::A)) // sprawdzenie czy klawisz A został przytrzymany
        { 
            timer += Hero::Time::GetDeltaTime();
        }

    }

    void Draw()
    {

        glClear(GL_COLOR_BUFFER_BIT);

        float col[] = {
            sinf((float)timer)*0.6f + 0.4f, 
            0.0f, 
            cosf((float)timer)*0.4f + 0.6f, 
            1.0f};
        glUniform4fv(ColorLoc, 1, col);

        group.Draw();
    }

    void Close()
    {
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


















