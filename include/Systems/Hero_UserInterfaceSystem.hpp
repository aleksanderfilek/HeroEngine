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

enum UIType
{
    Canvas = 0,
    Horizontal = 1,
    Vertical = 2,
    Grid = 3,
    Image = 4,
    Label = 5
};

struct UIMain
{
    std::string name;
    UIType type;
    std::string source;
    UIMain* next;
};

struct UIData
{
    uint32_t glID = 0;
    int2 size = int2zero;
    int2 position = int2zero;
    float4 uvRect;
    int4 objectRect;
};

struct UICustom
{
    uint8_t data[16];
};

struct UIElement
{
    UIMain main;
    UIData data;
    UICustom custom;
};

UIElement CreateLabel(const std::string& name);
void SetPositionLabel(UIElement& element, const int2& position);
void SetSizeLabel(UIElement& element, const int2& size);
void SetTextLabel(UIElement& element, const std::string& text);
void SetFontLabel(UIElement& element, Font* font);
void SetColorLabel(UIElement& element, Color& color);


class UserInterface : public ISystem
{
private:
    Mesh* mesh;
    Shader *shader;

    matrix4x4 view;

    std::vector<UIMain> main;
    std::vector<UIData> data;
    std::vector<UICustom> custom;

public:
    UserInterface();
    ~UserInterface();

    void Init();
    void Update();
    void Close();

    static const char* name; 
    const char* GetName(){ return name; }

    std::uint8_t priority(){ return 254; }

    uint32_t Add(const UIElement& element, const char* parent = nullptr);
    void Remove(const std::string& name); 
};

}

#endif