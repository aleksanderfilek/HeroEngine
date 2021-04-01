#ifndef HERO_UI_HPP
#define HERO_UI_HPP

#include"H_texture.hpp"
#include"H_game.hpp"
#include"H_math.hpp"
#include"H_stdlib.hpp"
#include"H_graphics.hpp"
#include"H_event.hpp"
#include"H_defines.hpp"

#include<iostream>
#include<string>
#include<stdint.h>
#include<cmath>
#include<vector>

namespace Hero
{

class Text;

class Font
{
friend class Text;

private:
    TTF_Font* _font = nullptr;
public:
    Font(const std::string& path, int size);
    ~Font();
};

typedef SDL_Color Color;

class UIElement
{
protected:
    int2 _size = int2zero;
    int2 _relativePosition = int2zero;
    int2 _absolutPosition = int2zero;
public:
    inline int2 GetSize(){ return this->_size; }
    void SetSize(const int2& size){ this->_size = size; }
    inline int2 GetRelativePosition(){ return this->_relativePosition; }
    void SetRelativePosition(const int2& relativePosition);
    inline int2 GetAbsolutePosition(){ return this->_absolutPosition; }
    virtual void SetAbsolutePosition(const int2& absolutePosition);

    virtual void Update() = 0;
    virtual void Draw() = 0;
};

class Group: public UIElement
{
private:
    std::vector<UIElement*> elements;
public:
    Group();
    ~Group();

    inline unsigned int GetCount(){ return elements.size(); }
    void SetAbsolutePosition(const int2& absolutePosition);

    void Update();
    void Draw();

    unsigned int Add(UIElement* element);
    void Remove(unsigned int index);
    void Clear();
};

class Text: public UIElement
{
private:
    std::string _text;
    Color _color = {255, 255, 255, 255};
    const Font* _font;
    unsigned int _id = 0;
public:
    Text();
    Text(const std::string& text, Color& color, const Font* font);
    ~Text();

    inline void SetFont(const Font* font){ this->_font = font; };
    inline std::string GetText(){ return std::string(this->_text.c_str()); };
    inline void SetText(const std::string& text){ this->_text.assign(text); }
    inline Color GetColor(){ return _color; }
    inline void SetColor(Color& color){ this->_color = color; }

    void Apply();
    void Update(){};
    void Draw();
};

class Button: public UIElement
{
private:
    bool _isHovering = false;
    Event* _clickEvent = nullptr;

    Text* _text = nullptr;
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

class Image: public UIElement
{
private:

public:
    void Apply();

    void Update(){};
    void Draw();
};

class HorizontalStack: public UIElement
{
private:

public:
    void Apply();

    void Update(){};
    void Draw();
};

class VerticalStack: public UIElement
{
private:

public:
    void Apply();

    void Update(){};
    void Draw();
};

}

#endif