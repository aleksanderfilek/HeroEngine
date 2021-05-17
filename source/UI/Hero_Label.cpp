#include"UI/Hero_Label.hpp"

namespace Hero
{

Label::Label()
{
}

Label::Label(const std::string& text, Color& color, const Font* font)
{
    this->_font = font;
    this->SetText(text);
    this->SetColor(color);
    this->Apply();
}



Label::~Label()
{
    glDeleteTextures(1, &this->_id);
    glCheckError();
    this->_id = 0;
}

void Label::Apply()
{
    if(this->_id != 0)
    {
        glDeleteTextures(1, &this->_id);
        this->_id = 0;
        glCheckError();
    }

    if(this->_text.length() == 0)
        return;

    SDL_Surface* surface = TTF_RenderText_Blended( this->_font->_font, this->_text.c_str(), this->_color );
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

void Label::Draw()
{
    if(this->_id == 0)
        return;

    Hero::matrix4x4 model;
    Hero::matrix_identity(model);
    Hero::int2 position = this->GetAbsolutePosition();
    Hero::matrix_translate(model, {(float)position.x, (float)position.y ,0});
    Hero::int2 size = this->GetSize();
    Hero::matrix_scale(model, {(float)size.x, (float)size.y, 0});
/*
    unsigned int modelLoc = Renderer2D::GetShader()->GetUniformLocation("model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)(&(model.v[0])));
    unsigned int viewLoc = Renderer2D::GetShader()->GetUniformLocation("view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)(&(Renderer2D::GetViewMatrix()->v[0])));
*/
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->_id);
    DEBUG_CODE(glCheckError();)
    Renderer2D::GetMesh()->Draw();
    DEBUG_CODE(glCheckError();)
}

}