#ifndef HERO_USERINTERFACE_SYSTEM_HPP
#define HERO_USERINTERFACE_SYSTEM_HPP

#include<string>
#include<map>

#include"Hero_Config.hpp"
#include"Core/Hero_Math.hpp"
#include"Core/Hero_System.hpp"
#include"Core/Hero_Mesh.hpp"
#include"Core/Hero_Shader.hpp"
#include"Core/Hero_Color.hpp"
#include"Core/Hero_Font.hpp"
#include"Core/Hero_Texture.hpp"

namespace Hero
{

enum UIType : uint32_t
{
    Canvas,
    Horizontal,
    Vertical,
    //Grid, //maybe custom from vertical and horizontal
    Image,
    Label,
    Custom
};

struct UIMain
{
    std::string name;
    UIType type;
};

struct UIDraw
{
    uint32_t id;
    int4 rect;
};

union First
{
    Font* font; //label
    uint32_t* childs; //canvas, horizontal, vertical
};
union Second
{
    Color color; //label
    uint32_t count; //canvas, horizontal, vertical
};
union Third
{
    char* text; //label, image
};

struct UICustom
{
    First first;
    Second second;
    Third third;
};

typedef uint32_t UIElement;

class UserInterface : public ISystem
{
private:
    Mesh* mesh;
    Shader *shader;

    matrix4x4 view;

    uint32_t smallestEmpty;
    std::vector<bool> empty;
    std::vector<UIMain> main;
    std::vector<UIDraw> draw;
    std::vector<UICustom> custom;

    std::vector<std::pair<Texture, uint32_t>> textureSet;

public:
    UserInterface();
    ~UserInterface();

    void Init();
    void Update();
    void Close();

    static const char* name; 
    const char* GetName(){ return name; }

    std::uint8_t priority(){ return 254; }

    UIElement Element_Create(const std::string& name, UIType type);
    void Element_Remove(const std::string& name);
    void Element_Remove(UIElement element);

    void Canvas_AddChild(UIElement self, const std::string& name);
    void Canvas_AddChild(UIElement self, UIElement element);
    void Canvas_RemoveChild(UIElement self, const std::string& name);
    void Canvas_RemoveChild(UIElement self, UIElement element);
    void Cavnas_SetPosition(UIElement self, const int2& position);
    void Canvas_SetSize(UIElement self, const int2& size);

    void Label_SetPosition(UIElement self, const int2& position);
    void Label_SetSize(UIElement self, const int2& size);
    void Label_SetText(UIElement self, const char* _text);
    void Label_SetFont(UIElement self, Font* font);
    void Label_SetColor(UIElement self, Color& color);
};

}

#endif