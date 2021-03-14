#include"H_ui.hpp"

namespace Hero
{

Font::Font(const std::string& path, int size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if(!font)
    {
        std::cout<<"Could not load font! SDL_ttf Error: "<<TTF_GetError()<<std::endl;
        return;
    }

    this->_font = font;
}

Font::~Font()
{
    TTF_CloseFont(this->_font);
    this->_font = nullptr;
}

void UIElement::SetRelativePosition(const int2& relativePosition)
{
    int2 diffrence = relativePosition - this->_relativePosition;
    this->_relativePosition = relativePosition;
    this->_absolutPosition += relativePosition;
}

void UIElement::SetAbsolutePosition(const int2& absolutePosition)
{
    this->_absolutPosition = absolutePosition + this->_relativePosition;
}

Text::Text(const Font* font)
{
    this->_font = font;
}


Text::~Text()
{
    glDeleteTextures(1, &this->_id);
}

void Text::SetText(const std::string& text)
{
    if(this->_text.length() == 0)
    {
        glDeleteTextures(1, &this->_id);
    }
        
    this->_text.assign(text);

    SDL_Surface* surface = TTF_RenderText_Blended( this->_font->_font, text.c_str(), this->_color );
    if( !surface)
    {
        std::cout<<"Unable to render text surface! SDL_ttf Error: "<<TTF_GetError()<<std::endl;
        return;
    }

    int mode = GL_RGB;
    if(surface->format->BytesPerPixel == 4)
        mode = GL_RGBA;

    unsigned int texture;
    glGenTextures(1, &texture);
    DEBUG_CODE(glCheckError();)
    glBindTexture(GL_TEXTURE_2D, texture);
    DEBUG_CODE(glCheckError();)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
                        GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    DEBUG_CODE(glCheckError();)
    glBindTexture(GL_TEXTURE_2D, 0);
    DEBUG_CODE(glCheckError();)

    this->_id = texture;
    this->SetSize({surface->w, surface->h});

    SDL_FreeSurface(surface);
}

void Text::Draw()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->_id);
    DEBUG_CODE(glCheckError();)
}

}