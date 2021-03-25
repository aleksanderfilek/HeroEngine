#include<iostream>

#include"Hero.hpp"
#include<cmath>

class Scene:public Hero::Level
{
public:
    Hero::Shader shader;
    Hero::Group group;
    Hero::Font *font;
    double timer = 0.0;
    Hero::Text* text;

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

        Hero::Color color = {0, 0, 255, 255};

        text = new Hero::Text(font);
        text->SetColor(color);
        text->SetText("Hello, World!");
        text->Apply();

        Hero::Text* text2 = new Hero::Text(font);
        text2->SetColor(color);
        text2->SetText("Testowy napis");
        text2->SetRelativePosition({200, 200});
        text2->Apply();

        group.Add(text);
        group.Add(text2);
        
    }

    void Update()
    {
        if(Hero::Input::keyPressed(Hero::Input::KeyCode::A)) // sprawdzenie czy klawisz A został przytrzymany
        { 
            timer += Hero::Time::GetDeltaTime();

            float col[] = {
                sinf((float)timer)*0.6f + 0.4f, 
                0.0f, 
                cosf((float)timer)*0.4f + 0.6f, 
                1.0f};
            Hero::Color color = {(uint8_t)(col[0] * 255), 
                                (uint8_t)(col[1] * 255), 
                                (uint8_t)(col[2] * 255), 
                                255};
            text->SetColor(color);
            text->Apply();
        }

    }

    void Draw()
    {

        glClear(GL_COLOR_BUFFER_BIT);

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


















