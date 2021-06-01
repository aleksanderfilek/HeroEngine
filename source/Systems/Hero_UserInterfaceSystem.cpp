#include"Systems/Hero_UserInterfaceSystem.hpp"

namespace Hero
{

UIElement CreateLabel(const std::string& name)
{
        UIElement element;

        element.main.type = UIType::Label;
        element.main.name = name;
        element.main.next = nullptr;
        element.custom.second.color = {255, 255, 255, 255};
        return element;
}

void SetPositionLabel(UIElement& element, const int2& position)
{
        element.data.position = position;
}

void SetSizeLabel(UIElement& element, const int2& size)
{
        element.data.size = size;
}

void SetTextLabel(UIElement& element, const std::string& text)
{
        element.main.source = text;
}

void SetFontLabel(UIElement& element, Font* font)
{
    element.custom.first.font = font;
}

void SetColorLabel(UIElement& element, Color& color)
{
    element.custom.second.color = color;
}

const char* UserInterface::name = "UserInterface System"; 

UserInterface::UserInterface()
{

}

UserInterface::~UserInterface()
{

}

void UserInterface::Init()
{
        ISystem::Init();

        float* vertices = new float[8]
                {0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
        float* uvs = new float[8]
                {0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
        uint32_t* indices = new uint32_t[6]
                {0, 1, 2, 2, 1, 3};

        meshBufferF verticesBuff = {BufferType::vec2, vertices, 8};
        meshBufferF uvsBuff = {BufferType::vec2, uvs, 8};
        meshBufferI indicesBuff = {indices, 6};

        this->mesh = new Mesh();
        this->mesh->name = "uiSprite";
        mesh->buffers.push_back(verticesBuff);
        mesh->buffers.push_back(uvsBuff);
        mesh->indices = indicesBuff;

        Hero::GenerateMesh(this->mesh);

        this->shader = LoadShader("uiShader.glslbin");

        this->view = Hero::OrthographicMatrix(1280, 700, 0.0f, 100.0f);
}

void UserInterface::Update()
{
        Hero::BindShader(this->shader);
        for(UIData& d: this->data)
        {
                if(d.glID == 0)
                {
                        continue;
                }
                
                Hero::matrix4x4 model = matrix4x4identity;
                Hero::TranslateM4x4(model, {(float)d.position.x, (float)d.position.y ,0});
                Hero::ScaleM4x4(model, {(float)d.objectRect.z, (float)d.objectRect.w, 0});

                unsigned int modelLoc = glGetUniformLocation(this->shader->glId, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)(&(model.col[0])));
                unsigned int viewLoc = glGetUniformLocation(this->shader->glId, "view");
                glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)(&(this->view.col[0])));
                unsigned int uvScaleLoc = glGetUniformLocation(this->shader->glId, "uvScale");
                glUniform2f(uvScaleLoc, d.uvRect.z, d.uvRect.w);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, d.glID);
                DEBUG_CODE(glCheckError();)
                Hero::DrawMesh(this->mesh);
        }
}

void UserInterface::Close()
{
        ISystem::Close();

        UnloadMesh(this->mesh);
        UnloadShader(this->shader);

        for(UIData& d: this->data)
        {
                if(d.glID == 0)
                {
                        continue;
                }
                glDeleteTextures(1, &d.glID);
        }
}

uint32_t UserInterface::Add(const UIElement& element, const char* parent)
{
        UIData data = element.data;
        if(element.main.type == UIType::Label)
        {
                Font* font = element.custom.first.font;
                Color color = element.custom.second.color;
                Texture texture = TextureFromText(element.main.source, color, font);

                data.glID = texture.glId;    
                int x = ClampI(texture.size.x, 0.0f, data.size.x);
                int y = ClampI(texture.size.y, 0.0f, data.size.y);

                data.objectRect = {0, 0, x, y};
                float w = (float)x / (float)texture.size.x;
                float h = (float)y / (float)texture.size.y;
                data.uvRect = {0.0f, 0.0f, w, h};
        }
        else if(element.main.type == UIType::Image)
        {

        }

        this->main.push_back(element.main);
        this->data.push_back(data);
        this->custom.push_back(element.custom);

        return this->main.size() - 1;
}

void UserInterface::Remove(const std::string& name)
{

}

}