#ifndef HERO_LABEL_UI_HPP
#define HERO_LABEL_UI_HPP

#include<string>

#include"Hero_Config.hpp"

#include"UI/Hero_UIElement.hpp"
#include"UI/Hero_Font.hpp"

namespace Hero
{

class Label: public UIElement
{
private:
    std::string _text;
    Color _color = {255, 255, 255, 255};
    const Font* _font;
    unsigned int _id = 0;
public:
    Label();
    Label(const std::string& text, Color& color, const Font* font);
    ~Label();

    inline void SetFont(const Font* font){ this->_font = font; };
    inline std::string GetText(){ return std::string(this->_text.c_str()); };
    inline void SetText(const std::string& text){ this->_text.assign(text); }
    inline Color GetColor(){ return _color; }
    inline void SetColor(Color& color){ this->_color = color; }

    void Apply();
    void Update(){};
    void Draw();
};

}

#endif