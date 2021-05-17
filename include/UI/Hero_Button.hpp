#ifndef HERO_BUTTON_UI_HPP
#define HERO_BUTTON_UI_HPP

#include<string>

#include"Core/Hero_Math.hpp"
#include"Core/Hero_Event.hpp"
#include"UI/Hero_UIElement.hpp"
#include"UI/Hero_Label.hpp"
#include"UI/Hero_Font.hpp"
#include"Core/Hero_Texture.hpp"

namespace Hero
{

class Button: public UIElement
{
private:
    bool _isHovering = false;
    EventHandler* _clickEvent = nullptr;

    Label* _text = nullptr;
    Texture* _texture = nullptr;
public:
    Button();
    ~Button();

    inline std::string GetText(){ return this->_text->GetText(); };
    inline void SetText(const std::string& text){ this->_text->SetText(text); }
    inline void SetFont(const Font* font){ this->_text->SetFont(font); };
    inline Color GetTextColor(){ return this->_text->GetColor(); }
    inline void SetTextColor(Color& color){ this->_text->SetColor(color); }
    inline void AddClickEvent(EventFunction function){ this->_clickEvent->Add(function); };
    inline void SetTexture(Texture* texture){ this->_texture = texture; }
    inline Texture* GetTexture(){ return this->_texture; }

    void SetAbsolutePosition(const int2& absolutePosition);

    void Apply();
    void Update();
    void Draw();
};

}

#endif