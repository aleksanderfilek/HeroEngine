#include"Systems/Hero_UserInterfaceSystem.hpp"

namespace Hero
{

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

        smallestEmpty = 0;
}

void UserInterface::Update()
{
        if(this->main.size() == 0)
                return;
                
        Hero::BindShader(this->shader);

        for(int i = 0; i < this->draw.size(); i++)
        {
                UIDraw& d = this->draw[i];
                if(this->empty[i] || d.id == 0)
                {
                        continue;
                }

                Hero::matrix4x4 model = matrix4x4identity;
                Hero::TranslateM4x4(model, {(float)d.rect.x, (float)d.rect.y ,0});
                Hero::ScaleM4x4(model, {(float)d.rect.z, (float)d.rect.w, 0});
                unsigned int modelLoc = glGetUniformLocation(this->shader->glId, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)(&(model.col[0])));
                unsigned int viewLoc = glGetUniformLocation(this->shader->glId, "view");
                glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)(&(this->view.col[0])));

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, d.id);
                DEBUG_CODE(glCheckError();)
                Hero::DrawMesh(this->mesh);
        }
}

void UserInterface::Close()
{
        ISystem::Close();

        UnloadMesh(this->mesh);
        UnloadShader(this->shader);

        for(int i = 0; i < this->main.size(); i++)
        {
                this->Element_Remove(i);
        }
}

UIElement UserInterface::Element_Create(const std::string& name, UIType type)
{
        UIMain uimain = {
                .name = name,
                .type = type,
        };

        UIDraw uidraw = {
                .id = 0,
                .rect = int4zero
        };

        UICustom uicustom = {};

        if(this->smallestEmpty >= this->main.size())
        {
                this->smallestEmpty++;

                this->empty.push_back(false);
                this->main.push_back(uimain);
                this->draw.push_back(uidraw);
                this->custom.push_back(uicustom);

                return this->main.size()-1;
        }

        this->empty[this->smallestEmpty] = false;
        this->main[this->smallestEmpty] = uimain;
        this->draw[this->smallestEmpty] = uidraw;
        this->custom[this->smallestEmpty] = uicustom;

        uint32_t returnIndex = this->smallestEmpty;
        this->smallestEmpty++;
        while(this->smallestEmpty < this->main.size())
        {                
                if(this->empty[this->smallestEmpty])
                        break;

                this->smallestEmpty++;
        }

        return returnIndex;
}

void UserInterface::Element_Remove(const std::string& name)
{
        uint32_t length = this->main.size();
        for(int i = 0; i < length; i++)
        {
                if(this->main[i].name.compare(name) != 0)
                        continue;
                
                this->Element_Remove(i);
                break;
        }
}
void UserInterface::Element_Remove(UIElement element)
{
        this->empty[element] = true;

        // remove texture if image or label

        if(this->main[element].type == UIType::Image)
        {
                const std::string& name = this->custom[element].third.text;
                for(int i = 0; i < this->textureSet.size(); i++)
                {
                        if(this->textureSet[i].first.name.compare(name) != 0)
                        {
                                continue;
                        }

                        this->textureSet[i].second--;
                        if(this->textureSet[i].second <= 0)
                        {
                                this->textureSet.erase(this->textureSet.begin() + i);
                                break;
                        }
                }
        }
        else if(this->main[element].type == UIType::Label)
        {
                glDeleteTextures(1, &this->draw[element].id);
        }

        // remove childs if group type

        if(UIType::Canvas <= this->main[element].type && 
                this->main[element].type <= UIType::VerticalBox)
        {
                for(int i = 0; i < this->custom[element].second.count; i++)
                {
                        this->Element_Remove(this->custom[element].first.childs[i]);
                }
                delete[] this->custom[element].first.childs;
        }
}

UIElement UserInterface::Element_Find(const std::string& name)
{
        for(int i = 0; i < this->main.size(); i++)
        {
                if(this->main[i].name.compare(name) == 0)
                {
                        return i;
                }
        }
        return 0;
}

void UserInterface::Canvas_AddChild(UIElement self, const std::string& name)
{
        UIElement child = this->Element_Find(name);
        this->Canvas_AddChild(self, child);
}

void UserInterface::Canvas_AddChild(UIElement self, UIElement child)
{
        this->custom[self].second.count++;
        uint32_t newSize = this->custom[self].second.count * sizeof(UIElement);
        this->custom[self].first.childs = (UIElement*)std::realloc(this->custom[self].first.childs, newSize);
        this->custom[self].first.childs[this->custom[self].second.count - 1] = child;
}

void UserInterface::Canvas_RemoveChild(UIElement self, const std::string& name)
{
        UIElement child = this->Element_Find(name);
        this->Canvas_RemoveChild(self, child);
}

void UserInterface::Canvas_RemoveChild(UIElement self, UIElement child)
{
        int  i = 0;
        for(i = 0; i < this->custom[self].second.count; i++)
        {
                if(this->custom[self].first.childs[i] == child)
                {
                        break;
                }
        }

        if(i == this->custom[self].second.count)
        {
                return;
        }
        //std::cout<<i<<std::endl;

        this->Element_Remove(this->custom[self].first.childs[i]);

        this->custom[self].second.count--;
        UIElement* newArr = new UIElement[this->custom[self].second.count];

        std::memcpy(newArr, this->custom[self].first.childs, i * sizeof(UIElement));
        std::memcpy(newArr + i, this->custom[self].first.childs + i + 1, 
                                        (this->custom[self].second.count - i)* sizeof(UIElement));

        delete[] this->custom[self].first.childs;
        this->custom[self].first.childs = newArr;

        for(int j = 0; j < this->custom[self].second.count; j++)
        {
                std::cout<<this->custom[self].first.childs[j]<<std::endl;
        }
}

void UserInterface::Canvas_SetPosition(UIElement self, const int2& position)
{
        uint32_t diffX = position.x - this->draw[self].rect.x;
        uint32_t diffY = position.y - this->draw[self].rect.y;

        this->draw[self].rect.x = position.x;
        this->draw[self].rect.y = position.y;

        int length = this->custom[self].second.count;
        for(int i = 0; i < length; i++)
        {
                uint32_t index = this->custom[self].first.childs[i];
                this->draw[index].rect.x += diffX;
                this->draw[index].rect.y += diffY;
        }
}

void UserInterface::Canvas_SetSize(UIElement self, const int2& size)
{
        this->draw[self].rect.z = size.x;
        this->draw[self].rect.w = size.y;
}

void UserInterface::HorizontalBox_AddChild(UIElement self, const std::string& name)
{
        UIElement child = this->Element_Find(name);
        this->HorizontalBox_AddChild(self, child);
}

void UserInterface::HorizontalBox_AddChild(UIElement self, UIElement child)
{
        this->custom[self].second.count++;
        uint32_t newSize = this->custom[self].second.count * sizeof(UIElement);
        this->custom[self].first.childs = (UIElement*)std::realloc(this->custom[self].first.childs, newSize);
        this->custom[self].first.childs[this->custom[self].second.count - 1] = child;

        int posX = this->draw[self].rect.x;
        for(int i = 0; i < this->custom[self].second.count - 1; i++)
        {
                uint32_t index = this->custom[self].first.childs[i];
                posX += this->draw[index].rect.z;
        }
        this->draw[child].rect.x = posX;
        this->draw[child].rect.y = this->draw[self].rect.y;
}

void UserInterface::HorizontalBox_RemoveChild(UIElement self, const std::string& name)
{
        UIElement child = this->Element_Find(name);
        this->HorizontalBox_RemoveChild(self, child);
}

void UserInterface::HorizontalBox_RemoveChild(UIElement self, UIElement child)
{
        int  i = 0;
        for(i = 0; i < this->custom[self].second.count; i++)
        {
                if(this->custom[self].first.childs[i] == child)
                {
                        break;
                }
        }

        if(i == this->custom[self].second.count)
        {
                return;
        }

        this->Element_Remove(this->custom[self].first.childs[i]);

        this->custom[self].second.count--;
        UIElement* newArr = new UIElement[this->custom[self].second.count];

        std::memcpy(newArr, this->custom[self].first.childs, i * sizeof(UIElement));
        std::memcpy(newArr + i, this->custom[self].first.childs + i + 1, 
                                        (this->custom[self].second.count - i)* sizeof(UIElement));

        delete[] this->custom[self].first.childs;
        this->custom[self].first.childs = newArr;

        for(int j = 0, posX = this->draw[self].rect.x; j < this->custom[self].second.count; j++)
        {
                uint32_t index = this->custom[self].first.childs[j];

                this->draw[index].rect.x = posX;
                this->draw[index].rect.y = this->draw[self].rect.y;
                posX += this->draw[index].rect.z;
        }
}

void UserInterface::HorizontalBox_SetPosition(UIElement self, const int2& position)
{
        uint32_t diffX = position.x - this->draw[self].rect.x;
        uint32_t diffY = position.y - this->draw[self].rect.y;

        this->draw[self].rect.x = position.x;
        this->draw[self].rect.y = position.y;

        int length = this->custom[self].second.count;
        for(int i = 0; i < length; i++)
        {
                uint32_t index = this->custom[self].first.childs[i];
                this->draw[index].rect.x += diffX;
                this->draw[index].rect.y += diffY;
        }
}

void UserInterface::HorizontalBox_SetSize(UIElement self, const int2& size)
{
        this->draw[self].rect.z = size.x;
        this->draw[self].rect.w = size.y; 
}

void UserInterface::VerticalBox_AddChild(UIElement self, const std::string& name)
{
        UIElement child = this->Element_Find(name);
        this->VerticalBox_AddChild(self, child);
}

void UserInterface::VerticalBox_AddChild(UIElement self, UIElement child)
{
        this->custom[self].second.count++;
        uint32_t newSize = this->custom[self].second.count * sizeof(UIElement);
        this->custom[self].first.childs = (UIElement*)std::realloc(this->custom[self].first.childs, newSize);
        this->custom[self].first.childs[this->custom[self].second.count - 1] = child;

        this->draw[child].rect.x = this->draw[self].rect.x;
        int posY = this->draw[self].rect.y;
        for(int i = 0; i < this->custom[self].second.count - 1; i++)
        {
                uint32_t index = this->custom[self].first.childs[i];
                posY += this->draw[index].rect.w;
        }
        this->draw[child].rect.y = posY;
}

void UserInterface::VerticalBox_RemoveChild(UIElement self, const std::string& name)
{
        UIElement child = this->Element_Find(name);
        this->VerticalBox_RemoveChild(self, child);
}

void UserInterface::VerticalBox_RemoveChild(UIElement self, UIElement child)
{
        int  i = 0;
        for(i = 0; i < this->custom[self].second.count; i++)
        {
                if(this->custom[self].first.childs[i] == child)
                {
                        break;
                }
        }

        if(i == this->custom[self].second.count)
        {
                return;
        }

        this->Element_Remove(this->custom[self].first.childs[i]);

        this->custom[self].second.count--;
        UIElement* newArr = new UIElement[this->custom[self].second.count];

        std::memcpy(newArr, this->custom[self].first.childs, i * sizeof(UIElement));
        std::memcpy(newArr + i, this->custom[self].first.childs + i + 1, 
                                        (this->custom[self].second.count - i)* sizeof(UIElement));

        delete[] this->custom[self].first.childs;
        this->custom[self].first.childs = newArr;

        for(int j = 0, posY = this->draw[self].rect.y; j < this->custom[self].second.count; j++)
        {
                uint32_t index = this->custom[self].first.childs[j];

                this->draw[index].rect.x = this->draw[self].rect.x;
                this->draw[index].rect.y = posY;
                posY += this->draw[index].rect.w;
        }
}

void UserInterface::VerticalBox_SetPosition(UIElement self, const int2& position)
{
        uint32_t diffX = position.x - this->draw[self].rect.x;
        uint32_t diffY = position.y - this->draw[self].rect.y;

        this->draw[self].rect.x = position.x;
        this->draw[self].rect.y = position.y;

        int length = this->custom[self].second.count;
        for(int i = 0; i < length; i++)
        {
                uint32_t index = this->custom[self].first.childs[i];
                this->draw[index].rect.x += diffX;
                this->draw[index].rect.y += diffY;
        }
}

void UserInterface::VerticalBox_SetSize(UIElement self, const int2& size)
{
        this->draw[self].rect.z = size.x;
        this->draw[self].rect.w = size.y; 
}

void UserInterface::Label_SetPosition(UIElement self, const int2& position)
{
        this->draw[self].rect.x = position.x;
        this->draw[self].rect.y = position.y;
}

void UserInterface::Label_SetSize(UIElement self, const int2& size)
{
        this->draw[self].rect.z = size.x;
        this->draw[self].rect.w = size.y;
}

void UserInterface::Label_SetText(UIElement self, const char* _text)
{
        //free old texture
        if(this->draw[self].id)
        {
                glDeleteTextures(1, &this->draw[self].id);
        }

        if(this->custom[self].third.text)
        {
                delete this->custom[self].third.text;
        }

        //set new text
        uint32_t len = strlen(_text);
        this->custom[self].third.text = new char[len];
        strcpy(this->custom[self].third.text, _text);

        //load new texture
        Texture newText = TextureFromText(_text, this->custom[self].second.color, 
                                                this->custom[self].first.font);

        this->draw[self].id = newText.glId;

        this->draw[self].rect.z = newText.size.x;
        this->draw[self].rect.w = newText.size.y;
}

void UserInterface::Label_SetFont(UIElement self, Font* font)
{
    this->custom[self].first.font = font;
}

void UserInterface::Label_SetColor(UIElement self, Color& color)
{
    this->custom[self].second.color = color;
}

}