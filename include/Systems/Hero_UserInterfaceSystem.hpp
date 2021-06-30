#ifndef HERO_USERINTERFACE_SYSTEM_HPP
#define HERO_USERINTERFACE_SYSTEM_HPP

#include<string>
#include<map>
#include<cstdlib>
#include<cstring>

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

typedef uint32_t UIElement;

enum UIType : uint32_t
{
    Canvas,
    HorizontalBox,
    VerticalBox,
    //GridBox, //maybe custom from vertical and horizontal
    Image,
    Label,
    Custom
};

struct UIMain
{
    std::string name;
    UIType type;
    int parent;
};

struct UIDraw
{
    bool visible;
    int id;
    int4 rect;
    matrix3x3 uvMat;
};

typedef void* UICustom;

class UserInterface : public ISystem
{
private:
    Mesh* mesh;
    Shader *shader;

    matrix4x4 view;

    uint32_t smallestEmpty = 0;
    std::vector<bool> empty;
    std::vector<UIMain> main;
    std::vector<UIDraw> draw;
    std::vector<UICustom> custom;

    std::vector<std::pair<Texture, uint32_t>> textureSet;

    void VerticalBox_SizeUpdate(UIElement self);
    void HorizontalBox_SizeUpdate(UIElement self);
    void SizeUpdate(UIElement self);

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
    UIElement Element_Find(const std::string& name);
    void Element_SetVisibility(UIElement self, bool visibility);
    bool Element_IsVisible(UIElement self);

    void Canvas_AddChild(UIElement self, const std::string& name);
    void Canvas_AddChild(UIElement self, UIElement child);
    void Canvas_RemoveChild(UIElement self, const std::string& name);
    void Canvas_RemoveChild(UIElement self, UIElement child);
    void Canvas_SetPosition(UIElement self, const int2& position);
    void Canvas_SetSize(UIElement self, const int2& size);

    void HorizontalBox_AddChild(UIElement self, const std::string& name);
    void HorizontalBox_AddChild(UIElement self, UIElement child);
    void HorizontalBox_RemoveChild(UIElement self, const std::string& name);
    void HorizontalBox_RemoveChild(UIElement self, UIElement child);
    void HorizontalBox_SetPosition(UIElement self, const int2& position);
    void HorizontalBox_SetSize(UIElement self, const int2& size);

    void VerticalBox_AddChild(UIElement self, const std::string& name);
    void VerticalBox_AddChild(UIElement self, UIElement child);
    void VerticalBox_RemoveChild(UIElement self, const std::string& name);
    void VerticalBox_RemoveChild(UIElement self, UIElement child);
    void VerticalBox_SetPosition(UIElement self, const int2& position);
    void VerticalBox_SetSize(UIElement self, const int2& size);

    void Label_SetPosition(UIElement self, const int2& position);
    void Label_SetSize(UIElement self, const int2& size);
    void Label_SetText(UIElement self, const char* _text);
    void Label_SetFont(UIElement self, Font* font);
    void Label_SetColor(UIElement self, Color& color);

    void Image_SetPosition(UIElement self, const int2& position);
    void Image_SetSize(UIElement self, const int2& size);
    void Image_SetTexture(UIElement self, Texture& texture);
    void Image_SetUV(UIElement self, const float4& uv);
};

}

#endif