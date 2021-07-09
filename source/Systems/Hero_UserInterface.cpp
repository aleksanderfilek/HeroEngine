#include"Systems/Hero_UserInterfaceSystem.hpp"
#include"Core/Hero_Mesh.hpp"
#include"Core/Hero_Shader.hpp"
#include"Systems/Hero_InputSystem.hpp"
#include"Core/Hero_Color.hpp"
#include"Core/Hero_Font.hpp"

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
/*
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

        this->smallestEmpty = 0;

        this->input = Core::GetSystem<Input>();*/
}

void UserInterface::Update()
{
        /*
        if(this->main.size() == 0)
                return;

        input->getMousePosition(&mouseX, &mouseY);

        //hover check
        for(int i = 0; i < this->event.size(); i++)
        {
                UIEvent& ev = this->event[i];
                if(ev.set & 7 == 0)
                        continue;

                int4 rect = this->draw[i].rect;
                if(rect.x <= mouseX && mouseX <= (rect.x + rect.z) &&
                        rect.y <= mouseY && mouseY <= (rect.y + rect.w))
                {
                        if(ev.hover == false)
                        {
                                ev.hover = true;
                                std::cout<<"onhover"<<std::endl;
                                if(ev.set & 1)
                                        this->bindedEvents[i][0](this, &i, 1);
                        }
                        else 
                        {
                               // std::cout<<"hover"<<std::endl;
                                if(this->event[i].set & 2)
                                        this->bindedEvents[i][1](this, &i, 1);
                        }
                }
                else
                {
                        if(ev.hover == true)
                        {
                                ev.hover = false;
                                if(this->event[i].set & 4)
                                        this->bindedEvents[i][2](this, &i, 1);
                        }
                }
        }


        //click check
        if(input->mouseButtonDown(Input::Mouse::Left))
        {
                for(int i = 0; i < this->event.size(); i++)
                {
                        UIEvent& ev = this->event[i];

                        if(ev.set & 8 && ev.hover == true)
                        {
                                this->bindedEvents[i][3](this, &i, 1);
                        }
                }
        }
        if(input->mouseButtonPressed(Input::Mouse::Left))
        {
                for(int i = 0; i < this->event.size(); i++)
                {
                        UIEvent& ev = this->event[i];

                        if(ev.set & 16 && ev.hover == true)
                        {
                                this->bindedEvents[i][4](this, &i, 1);
                        }
                }
        }
        if(input->mouseButtonUp(Input::Mouse::Left))
        {
                for(int i = 0; i < this->event.size(); i++)
                {
                        UIEvent& ev = this->event[i];

                        if(ev.set & 32 && ev.hover == true)
                        {
                                this->bindedEvents[i][5](this, &i, 1);
                        }
                }                
        }

        Hero::BindShader(this->shader);

        for(int i = 0; i < this->draw.size(); i++)
        {
                UIDraw& d = this->draw[i];
                if(this->empty[i] || !d.visible || d.id < 0)
                {
                        continue;
                }

                Hero::matrix4x4 model = matrix4x4identity;
                Hero::TranslateM4x4(model, {(float)d.rect.x, (float)d.rect.y , (float)d.zorder/256.0f});
                Hero::ScaleM4x4(model, {(float)d.rect.z, (float)d.rect.w, 0});
                unsigned int modelLoc = glGetUniformLocation(this->shader->glId, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)(&(model.col[0])));
                unsigned int viewLoc = glGetUniformLocation(this->shader->glId, "view");
                glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)(&(this->view.col[0])));
                unsigned int uvmatLoc = glGetUniformLocation(this->shader->glId, "uvmat");
                glUniformMatrix3fv(uvmatLoc, 1, GL_FALSE, (float*)(&(d.uvMat.col[0])));

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, this->textureSet[d.id].first.glId);
                DEBUG_CODE(glCheckError();)
                Hero::DrawMesh(this->mesh);
        }
        */
}

void UserInterface::Close()
{
        /*
        ISystem::Close();

        UnloadMesh(this->mesh);
        UnloadShader(this->shader);

        for(int i = 0; i < this->main.size(); i++)
        {
                if(this->empty[i])
                {
                        continue;
                }

                this->Element_Remove(i);
        }
        */
}

// main data of element
struct UIMain
{
  const char* name;
  UIElementType type;
  UIElement parent;
  void* typeData;
};

// element data to render
struct UIDraw
{
  bool isVisible;
  int4 rect;
  uint32_t textureID;
  matrix3x3 textureMat;
};

// element data to handle event states
struct UIEvent
{
  uint8_t set;
  uint32_t state;
};

// custom data structs for elment types
struct CanvasData
{
    UIElement* childs;
    uint32_t count;
};

struct HorizontalBoxData
{
    UIElement* childs;
    uint32_t count;
};

struct VerticalBoxData
{
    UIElement* childs;
    uint32_t count;
};

struct LabelData
{
    Font* font;
    Color color;
    char* text;
};

struct ImageData
{

};

/*
void UserInterface::SizeUpdate(UIElement self)
{
        if(this->main[self].parent < 0)
        {
                return;
        }

        switch(this->main[this->main[self].parent].type)
        {
                case UIElementType::HorizontalBox:
                        this->HorizontalBox_SizeUpdate(this->main[self].parent);
                break;
                case UIElementType::VerticalBox:
                        this->VerticalBox_SizeUpdate(this->main[self].parent);
                break;
        }
}

UIElement UserInterface::Element_Create(const std::string& name, UIElementType type)
{
        UIMain uimain = {
                .name = name,
                .type = type,
                .parent = -1
        };

        UIDraw uidraw = {
                .visible = true,
                .id = -1,
                .rect = int4zero,
                .zorder = 0,
                .uvMat = matrix3x3identity
        };

        UICustom uicustom;
        switch (type)
        {
        case UIElementType::Canvas:
                uicustom = new CanvasData();
                break;
        case UIElementType::HorizontalBox:
                uicustom = new HorizontalBoxData();
                break;
        case UIElementType::VerticalBox:
                uicustom = new VerticalBoxData();
                break;
        case UIElementType::Label:
                uicustom = new LabelData();
                break;
        }

        UIEvent uievent = 
        {
                .set = 0,
                .hover = false
        };

        if(this->smallestEmpty >= this->main.size())
        {
                this->smallestEmpty++;

                this->empty.push_back(false);
                this->main.push_back(uimain);
                this->draw.push_back(uidraw);
                this->custom.push_back(uicustom);
                this->event.push_back(uievent);
                std::vector<EventFunction> events(6);
                this->bindedEvents.push_back(events);

                return this->main.size()-1;
        }

        this->empty[this->smallestEmpty] = false;
        this->main[this->smallestEmpty] = uimain;
        this->draw[this->smallestEmpty] = uidraw;
        this->custom[this->smallestEmpty] = uicustom;
        this->event[this->smallestEmpty] = uievent;
        this->bindedEvents[this->smallestEmpty].clear();

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

        switch (this->main[element].type)
        {
        case UIElementType::Canvas:
                {
                CanvasData* data = (CanvasData*)this->custom[element];
                delete[] data->childs;
               }
               break;
        case UIElementType::HorizontalBox:
                {
                HorizontalBoxData* data = (HorizontalBoxData*)this->custom[element];
                delete[] data->childs;
                }
                break;
        case UIElementType::VerticalBox:
                {
                VerticalBoxData* data = (VerticalBoxData*)this->custom[element];
                delete[] data->childs;
                }
                break;
        case UIElementType::Label:
                {
                LabelData* data = (LabelData*)this->custom[element];
                //glDeleteTextures(1, &this->draw[element].id);
                if(data->text)
                {
                        delete[] data->text;
                }
                this->textureSet[element].second--;
                if(this->textureSet[element].second == 0)
                {
                        this->draw[element].id = -1;
                        Extra::UnloadTextureByCopy(this->textureSet[element].first);
                } 
                }
                break;
        }

        free(this->custom[element]);
        if(this->smallestEmpty > element )
        {
                this->smallestEmpty = element;
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

void UserInterface::Element_SetVisibility(UIElement self, bool visibility)
{
        this->draw[self].visible = visibility;
        this->SizeUpdate(self);
}

bool UserInterface::Element_IsVisible(UIElement self)
{
        return this->draw[self].visible;
}

void UserInterface::Element_BindEvent(UIElement self, UIEventType type, EventFunction function)
{
    this->event[self].set |= 1<<type;
    this->bindedEvents[self][type] = function;
}

void UserInterface::Element_UnbindEvent(UIElement self, UIEventType type)
{
        this->event[self].set &= ~(1<<type);
        this->bindedEvents[self][type] = NULL;
}

void UserInterface::Element_SetZOrder(UIElement self, uint32_t zorder)
{
        this->draw[self].zorder = zorder;

        switch(this->main[self].type)
        {
                case UIElementType::Canvas:
                {
                      CanvasData* data = (CanvasData*)this->custom[self];
                      for(int i = 0; i < data->count; i++)
                      {
                              this->draw[data->childs[i]].zorder = zorder;
                      }  
                }break;
                case UIElementType::HorizontalBox:
                {
                      HorizontalBoxData* data = (HorizontalBoxData*)this->custom[self];
                      for(int i = 0; i < data->count; i++)
                      {
                              this->draw[data->childs[i]].zorder = zorder;
                      }  
                }break;
                case UIElementType::VerticalBox:
                {
                      VerticalBoxData* data = (VerticalBoxData*)this->custom[self];
                      for(int i = 0; i < data->count; i++)
                      {
                              this->draw[data->childs[i]].zorder = zorder;
                      }  
                }break;
        }
}

void UserInterface::Canvas_AddChild(UIElement self, const std::string& name)
{
        UIElement child = this->Element_Find(name);
        this->Canvas_AddChild(self, child);
}

void UserInterface::Canvas_AddChild(UIElement self, UIElement child)
{
        CanvasData* data = (CanvasData*)this->custom[self];
        data->count++;
        uint32_t newSize = data->count * sizeof(UIElement);
        data->childs = (UIElement*)std::realloc(data->childs, newSize);
        data->childs[data->count - 1] = child;
        this->main[child].parent = (int)self;
}

void UserInterface::Canvas_RemoveChild(UIElement self, const std::string& name)
{
        UIElement child = this->Element_Find(name);
        this->Canvas_RemoveChild(self, child);
}

void UserInterface::Canvas_RemoveChild(UIElement self, UIElement child)
{
        CanvasData* data = (CanvasData*)this->custom[self];

        int  i = 0;
        for(i = 0; i < data->count; i++)
        {
                if(data->childs[i] == child)
                {
                        break;
                }
        }

        if(i == data->count)
        {
                return;
        }

        this->Element_Remove(data->childs[i]);

        data->count--;
        UIElement* newArr = new UIElement[data->count];

        std::memcpy(newArr, data->childs, i * sizeof(UIElement));
        std::memcpy(newArr + i, data->childs + i + 1, 
                        (data->count - i)* sizeof(UIElement));

        delete[] data->childs;
        data->childs = newArr;

}

void UserInterface::Canvas_SetPosition(UIElement self, const int2& position)
{
        uint32_t diffX = position.x - this->draw[self].rect.x;
        uint32_t diffY = position.y - this->draw[self].rect.y;

        this->draw[self].rect.x = position.x;
        this->draw[self].rect.y = position.y;

        CanvasData* data = (CanvasData*)this->custom[self];

        int length = data->count;
        for(int i = 0; i < length; i++)
        {
                uint32_t index = data->childs[i];
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
        HorizontalBoxData* data = (HorizontalBoxData*)this->custom[self];
        data->count++;
        uint32_t newSize = data->count * sizeof(UIElement);
        data->childs = (UIElement*)std::realloc(data->childs, newSize);
        data->childs[data->count - 1] = child;

        int posX = this->draw[self].rect.x;
        for(int i = 0; i < data->count - 1; i++)
        {
                uint32_t index = data->childs[i];
                posX += this->draw[index].rect.z;
        }
        this->draw[child].rect.x = posX;
        this->draw[child].rect.y = this->draw[self].rect.y;
        this->main[child].parent = (int)self;
}

void UserInterface::HorizontalBox_RemoveChild(UIElement self, const std::string& name)
{
        UIElement child = this->Element_Find(name);
        this->HorizontalBox_RemoveChild(self, child);
}

void UserInterface::HorizontalBox_RemoveChild(UIElement self, UIElement child)
{
        HorizontalBoxData* data = (HorizontalBoxData*)this->custom[self];
        int  i = 0;
        for(i = 0; i < data->count; i++)
        {
                if(data->childs[i] == child)
                {
                        break;
                }
        }

        if(i == data->count)
        {
                return;
        }

        this->Element_Remove(data->childs[i]);

        data->count--;
        UIElement* newArr = new UIElement[data->count];

        std::memcpy(newArr, data->childs, i * sizeof(UIElement));
        std::memcpy(newArr + i, data->childs + i + 1, 
                                (data->count - i)* sizeof(UIElement));

        delete[] data->childs;
        data->childs = newArr;

        this->HorizontalBox_SizeUpdate(self);
}

void UserInterface::HorizontalBox_SetPosition(UIElement self, const int2& position)
{
        uint32_t diffX = position.x - this->draw[self].rect.x;
        uint32_t diffY = position.y - this->draw[self].rect.y;

        this->draw[self].rect.x = position.x;
        this->draw[self].rect.y = position.y;

        HorizontalBoxData* data = (HorizontalBoxData*)this->custom[self];

        int length = data->count;
        for(int i = 0; i < length; i++)
        {
                uint32_t index = data->childs[i];
                this->draw[index].rect.x += diffX;
                this->draw[index].rect.y += diffY;
        }
}

void UserInterface::HorizontalBox_SetSize(UIElement self, const int2& size)
{
        this->draw[self].rect.z = size.x;
        this->draw[self].rect.w = size.y; 
}

void UserInterface::HorizontalBox_SizeUpdate(UIElement self)
{
        HorizontalBoxData* data = (HorizontalBoxData*)this->custom[self];

        for(int j = 0, posX = this->draw[self].rect.x; j < data->count; j++)
        {
                uint32_t index = data->childs[j];

                if(this->draw[index].visible == false)
                        continue;

                this->draw[index].rect.x = posX;
                this->draw[index].rect.y = this->draw[self].rect.y;
                posX += this->draw[index].rect.z;
        }
}

void UserInterface::VerticalBox_AddChild(UIElement self, const std::string& name)
{
        UIElement child = this->Element_Find(name);
        this->VerticalBox_AddChild(self, child);
}

void UserInterface::VerticalBox_AddChild(UIElement self, UIElement child)
{
        VerticalBoxData* data = (VerticalBoxData*)this->custom[self];
        data->count++;
        uint32_t newSize = data->count * sizeof(UIElement);
        data->childs = (UIElement*)std::realloc(data->childs, newSize);
        data->childs[data->count - 1] = child;
        this->draw[child].zorder = this->draw[self].zorder;
        this->draw[child].rect.x = this->draw[self].rect.x;
        int posY = this->draw[self].rect.y;
        for(int i = 0; i < data->count - 1; i++)
        {
                uint32_t index = data->childs[i];
                posY += this->draw[index].rect.w;
        }
        this->draw[child].rect.y = posY;
        this->main[child].parent = (int)self;
}

void UserInterface::VerticalBox_RemoveChild(UIElement self, const std::string& name)
{
        UIElement child = this->Element_Find(name);
        this->VerticalBox_RemoveChild(self, child);
}

void UserInterface::VerticalBox_RemoveChild(UIElement self, UIElement child)
{
        VerticalBoxData* data = (VerticalBoxData*)this->custom[self];
        
        int  i = 0;
        for(i = 0; i < data->count; i++)
        {
                if(data->childs[i] == child)
                {
                        break;
                }
        }

        if(i == data->count)
        {
                return;
        }

        this->Element_Remove(data->childs[i]);

        data->count--;
        UIElement* newArr = new UIElement[data->count];

        std::memcpy(newArr, data->childs, i * sizeof(UIElement));
        std::memcpy(newArr + i, data->childs + i + 1, 
                        (data->count - i)* sizeof(UIElement));

        delete[] data->childs;
        data->childs = newArr;

        this->VerticalBox_SizeUpdate(self);
}

void UserInterface::VerticalBox_SetPosition(UIElement self, const int2& position)
{
        VerticalBoxData* data = (VerticalBoxData*)this->custom[self];

        uint32_t diffX = position.x - this->draw[self].rect.x;
        uint32_t diffY = position.y - this->draw[self].rect.y;

        this->draw[self].rect.x = position.x;
        this->draw[self].rect.y = position.y;

        int length = data->count;
        for(int i = 0; i < length; i++)
        {
                uint32_t index = data->childs[i];
                this->draw[index].rect.x += diffX;
                this->draw[index].rect.y += diffY;
        }
}

void UserInterface::VerticalBox_SetSize(UIElement self, const int2& size)
{
        this->draw[self].rect.z = size.x;
        this->draw[self].rect.w = size.y; 
}

void UserInterface::VerticalBox_SizeUpdate(UIElement self)
{
        VerticalBoxData* data = (VerticalBoxData*)this->custom[self];

        for(int j = 0, posY = this->draw[self].rect.y; j < data->count; j++)
        {
                uint32_t index = data->childs[j];

                if(this->draw[index].visible == false)
                        continue;

                this->draw[index].rect.x = this->draw[self].rect.x;
                this->draw[index].rect.y = posY;
                posY += this->draw[index].rect.w;
        }
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

        this->SizeUpdate(self);
}

void UserInterface::Label_SetText(UIElement self, const char* _text)
{
        //free old texture
       if(this->draw[self].id >= 0)
        {
                this->textureSet[self].second--;
                if(this->textureSet[self].second == 0)
                {
                        this->draw[self].id = -1;
                        Extra::UnloadTextureByCopy(this->textureSet[self].first);
                } 
        }

        LabelData* data = (LabelData*)this->custom[self];

        if(data->text)
        {
                delete data->text;
        }

        //set new text
        uint32_t len = strlen(_text);
        data->text = new char[len];
        strcpy(data->text, _text);

        for(int i = 0 ; i < this->textureSet.size() && this->draw[self].id >= 0; i++)//ugh
        {
                if(this->textureSet[i].first.name.compare(data->text) != 0)
                {
                        continue;
                }

                this->draw[self].id = i;
                if(this->draw[self].rect.z == 0 && this->draw[self].rect.w == 0)
                {
                        this->draw[self].rect.z = this->textureSet[i].first.size.x;
                        this->draw[self].rect.w = this->textureSet[i].first.size.y;
                }
 
                this->SizeUpdate(self);

                return;
        }

        //load new texture
        Texture newTex = TextureFromText(_text, data->color, data->font);
        newTex.name = std::string(_text);

        std::pair<Texture, uint32_t> element = {newTex, 1};
        this->textureSet.push_back(element);
        this->draw[self].id = this->textureSet.size()-1;

        if(this->draw[self].rect.z == 0 && this->draw[self].rect.w == 0)
        {
                this->draw[self].rect.z = newTex.size.x;
                this->draw[self].rect.w = newTex.size.y;
        }

        this->SizeUpdate(self);
}

void UserInterface::Label_SetFont(UIElement self, Font* font)
{
    ((LabelData*)this->custom[self])->font = font;
}

void UserInterface::Label_SetColor(UIElement self, Color& color)
{
    ((LabelData*)this->custom[self])->color = color;
}

void UserInterface::Image_SetPosition(UIElement self, const int2& position)
{
        this->draw[self].rect.x = position.x;
        this->draw[self].rect.y = position.y;
}

void UserInterface::Image_SetSize(UIElement self, const int2& size)
{
        this->draw[self].rect.z = size.x;
        this->draw[self].rect.w = size.y;

        this->SizeUpdate(self);
}

void UserInterface::Image_SetTexture(UIElement self, Texture& texture)
{
        //free old texture
       if(this->draw[self].id >= 0)
        {
                this->textureSet[self].second--;
                if(this->textureSet[self].second == 0)
                {
                        this->draw[self].id = -1;
                        Extra::UnloadTextureByCopy(this->textureSet[self].first);
                } 
        }

        for(int i = 0 ; i < this->textureSet.size(); i++)//ugh
        {
                if(this->textureSet[i].first.name.compare(texture.name) != 0)
                {
                        continue;
                }

                this->draw[self].id = i;
                if(this->draw[self].rect.z == 0 && this->draw[self].rect.w == 0)
                {
                        this->draw[self].rect.z = this->textureSet[i].first.size.x;
                        this->draw[self].rect.w = this->textureSet[i].first.size.y;
                }

                this->SizeUpdate(self);
                return;
        }

        std::pair<Texture, uint32_t> element = {texture, 1};
        this->textureSet.push_back(element);
        this->draw[self].id = this->textureSet.size()-1;

        if(this->draw[self].rect.z == 0 && this->draw[self].rect.w == 0)
        {
                this->draw[self].rect.z = texture.size.x;
                this->draw[self].rect.w = texture.size.y;
        }

        this->SizeUpdate(self);
}

void UserInterface::Image_SetUV(UIElement self, const float4& uv)
{
       matrix3x3& mat = this->draw[self].uvMat;
       mat.col[0].x = uv.z - uv.x;
       mat.col[1].y = uv.w - uv.y;
       mat.col[2].x = uv.x;
       mat.col[2].y = uv.y; 
}
*/
}