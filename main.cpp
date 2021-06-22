#include"HeroCore.hpp"
#include"HeroSystems.hpp"

class Test:public Hero::ILevel
{
private:
    Hero::Shader* shader;
    Hero::Mesh* mesh;
    Hero::UIElement canvas, label;
    Hero::int2 pos = {0, 0};
    Hero::Input* input;
    Hero::UserInterface* ui;
public:
    void OnInit()
    {
        shader = Hero::LoadShader("standardShader.glslbin");

        float* arr = new float[6] {-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f};
        Hero::meshBufferF buffer = { Hero::BufferType::vec2, arr, 6 };

        float* arr3 = new float[9] {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
        Hero::meshBufferF buffer2 = { Hero::BufferType::vec3, arr3, 9 };

        uint32_t* arr2 = new uint32_t[3] {0, 1 ,2};
        Hero::meshBufferI indices = {arr2, 3};

        mesh = new Hero::Mesh();
        mesh->name = "mesh";
        mesh->buffers.push_back(buffer);
        mesh->buffers.push_back(buffer2);
        mesh->indices = indices;

        Hero::GenerateMesh(mesh);

        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        ui = Hero::Core::GetSystem<Hero::UserInterface>();

        Hero::Font* font = Hero::LoadFont("arial.ttf" , 48);

        label = ui->Element_Create("label1", Hero::UIType::Label);
        Hero::Color color = {255, 255, 0, 255};
        ui->Label_SetColor(label, color);
        ui->Label_SetFont(label, font);
        ui->Label_SetText(label, "Hello, World!");
        ui->Label_SetPosition(label, {100, 100});

        Hero::UIElement label2 = ui->Element_Create("label2", Hero::UIType::Label);
        ui->Label_SetColor(label2, color);
        ui->Label_SetFont(label2, font);
        ui->Label_SetText(label2, "Elo");
        ui->Label_SetPosition(label2, {100, 200});

        Hero::UIElement label3 = ui->Element_Create("label3", Hero::UIType::Label);
        ui->Label_SetColor(label3, color);
        ui->Label_SetFont(label3, font);
        ui->Label_SetText(label3, "Alek");
        ui->Label_SetPosition(label3, {100, 300});

        canvas = ui->Element_Create("canvas1", Hero::UIType::HorizontalBox);
        ui->HorizontalBox_AddChild(canvas, "label1");
        ui->HorizontalBox_AddChild(canvas, "label2");
        ui->HorizontalBox_AddChild(canvas, "label3");
        ui->HorizontalBox_SetPosition(canvas, pos);

        Hero::UnloadFont(font);

        input = Hero::Core::GetSystem<Hero::Input>();
    }

    void OnUpdate()
    {
        Hero::BindShader(shader);
        Hero::DrawMesh(mesh);

        if(input->keyPressed(Hero::Input::KeyCode::SPACE))
        {
            std::cout<<pos.x<<std::endl;
            pos = Hero::AddI2(pos, {100 * Hero::Time::GetDeltaTime(), 100 * Hero::Time::GetDeltaTime()});
            ui->HorizontalBox_SetPosition(canvas, pos);
        }

        if(input->keyPressed(Hero::Input::KeyCode::P))
        {
            std::cout<<"Remove"<<std::endl;
            ui->HorizontalBox_RemoveChild(canvas, label);
        }
    }

    void OnClose()
    {
        Hero::UnloadShader(shader);
        Hero::UnloadMesh(mesh);
    }
};

int main(int argc, char *argv[])
{
    Hero::Core* core = new Hero::Core();

    core->AddSystem<Hero::Window>(new Hero::Window("Title", 1280, 720));
    core->AddSystem<Hero::Event>(new Hero::Event());
    core->AddSystem<Hero::Input>(new Hero::Input());
    core->AddSystem<Hero::Resources>(new Hero::Resources());
    core->AddSystem<Hero::Level>(new Hero::Level(new Test()));
    core->AddSystem<Hero::UserInterface>(new Hero::UserInterface());
    core->Start();

    delete core;

    return 0;
}