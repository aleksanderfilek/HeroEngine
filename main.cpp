#include"HeroCore.hpp"
#include"HeroSystems.hpp"

class Test:public Hero::ILevel
{
private:
    Hero::Shader* shader;
    Hero::Mesh* mesh;
    Hero::Window* window = nullptr;
public:
    void OnInit()
    {
        window = Hero::Core::GetSystem<Hero::Window>();
        if(!window)
            std::cout<<"brak okna"<<std::endl;

        shader = Hero::LoadShader("standardShader.glslbin");

        Hero::BindShader(shader);

        float* arr = new float[6];
        arr[0] = -0.5f;
        arr[1] = -0.5f;
        arr[2] = 0.0;
        arr[3] = 0.0;
        arr[4] = 0.5;
        arr[5] = -0.5;
        Hero::meshBufferF buffer = { Hero::BufferType::vec2, arr, 6 };

        float* arr3 = new float[9];
        arr3[0] = 1.0f;
        arr3[1] = 0.0f;
        arr3[2] = 0.0;
        arr3[3] = 0.0;
        arr3[4] = 1.0;
        arr3[5] = 0.0;
        arr3[6] = 0.0;
        arr3[7] = 0.0;
        arr3[8] = 1.0;
        Hero::meshBufferF buffer2 = { Hero::BufferType::vec3, arr3, 9 };

        uint32_t* arr2 = new uint32_t[3];
        arr2[0] = 0;
        arr2[1] = 1;
        arr2[2] = 2;
        Hero::meshBufferI indices = {arr2, 3};

        mesh = new Hero::Mesh();
        mesh->name = "mesh";
        mesh->buffers.push_back(buffer);
        mesh->buffers.push_back(buffer2);
        mesh->indices = indices;

        Hero::GenerateMesh(mesh);
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    }

    void OnUpdate()
    {

        glClear(GL_COLOR_BUFFER_BIT);
        Hero::DrawMesh(mesh);
        window->Render();
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
    core->Start();

    delete core;

    return 0;
}