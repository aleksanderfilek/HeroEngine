#ifndef HERO_UI_HPP
#define HERO_UI_HPP

#include"H_texture.hpp"
#include"H_game.hpp"
#include"H_math.hpp"
#include"H_stdlib.hpp"
#include"H_graphics.hpp"

#include<SDL\SDL_ttf.h>

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
    void SetAbsolutePosition(const int2& absolutePosition);

    virtual void Update() = 0;
    virtual void Draw() = 0;
};


class Text: public UIElement
{
private:
    std::string _text;
    Color _color = {255, 255, 255, 255};
    const Font* _font;
    unsigned int _id;
public:
    Text(const Font* font);
    ~Text();

    inline std::string GetText(){ return std::string(this->_text.c_str()); };
    void SetText(const std::string& text);
    inline Color GetColor(){ return _color; }
    inline void SetColor(Color& color){ this->_color = color; }

    void Update(){};
    void Draw();
};

class Group: public UIElement
{
private:
    std::vector<UIElement*> elements;
public:
    Group();
    ~Group();

    inline unsigned int GetCount(){ return elements.size(); }

    void Update();
    void Draw();

    unsigned int Add(UIElement* element);
    void Remove(unsigned int index);
    void Clear();
};

}

#endif