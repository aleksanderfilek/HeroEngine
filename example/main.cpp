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
    Hero::matrix4x4 view;
    Hero::matrix4x4 model;
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

        mesh.Load("example/plane.daebin");

        //texture.Load("example/default.png");

        font = new Hero::Font("example/arial.ttf", 28);

        Hero::Color color = {255, 255, 255, 255};

        text = new Hero::Text(font);
        text->SetColor(color);
        text->SetText("Hello, World!");

        Hero::matrix_orthographic(view, 640, 480, 0, 100);

        Hero::matrix_identity(model);
        Hero::matrix_translate(model, {0, 0 ,0});
        Hero::int2 size = text->GetSize();
        Hero::matrix_scale(model, {(float)size.x, (float)size.y, 0});

        shader.Bind();
        unsigned int modelLoc = shader.GetUniformLocation("model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)(&(model.v[0])));
        unsigned int viewLoc = shader.GetUniformLocation("view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)(&(view.v[0])));
        ColorLoc = shader.GetUniformLocation("color");
        
        text->Draw();
    }

    void Update()
    {
        if(Hero::Input::keyPressed(Hero::Input::KeyCode::A)) // sprawdzenie czy klawisz A został przytrzymany
        { 
            timer += Hero::Time::GetDeltaTime();
            std::cout<<timer<<std::endl;
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


















