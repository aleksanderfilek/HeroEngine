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

Group::Group()
{

}

Group::~Group()
{
    this->Clear();
}

void Group::SetAbsolutePosition(const int2& absolutePosition)
{
    this->_absolutPosition = absolutePosition + this->_relativePosition;
    for(UIElement* i : this->elements)
    {
        i->SetAbsolutePosition(this->_absolutPosition);
    }
}

void Group::Update()
{
    for(UIElement* i : this->elements)
    {
        i->Update();
    }
}

void Group::Draw()
{
    for(int i = 0; i < elements.size(); i++)
        elements[i]->Draw();
    /*for(UIElement* i : this->elements)
    {
        i->Draw();
    }*/
}

unsigned int Group::Add(UIElement* element)
{
    element->SetAbsolutePosition(this->GetAbsolutePosition());
    this->elements.push_back(element);
    return this->elements.size()-1;
}

void Group::Remove(unsigned int index)
{
    delete this->elements[index];
    this->elements[index] = nullptr;
    this->elements.erase(this->elements.begin() + index);
}

void Group::Clear()
{
    for(UIElement* i : this->elements)
    {
        delete i;
        i = nullptr;
    }
    this->elements.clear();
}

Text::Text()
{
}

Text::Text(const std::string& text, Color& color, const Font* font)
{
    this->_font = font;
    this->SetText(text);
    this->SetColor(color);
    this->Apply();
}



Text::~Text()
{
    glDeleteTextures(1, &this->_id);
    glCheckError();
    this->_id = 0;
}

void Text::Apply()
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

void Text::Draw()
{
    if(this->_id == 0)
        return;

    Hero::matrix4x4 model;
    Hero::matrix_identity(model);
    Hero::int2 position = this->GetAbsolutePosition();
    Hero::matrix_translate(model, {(float)position.x, (float)position.y ,0});
    Hero::int2 size = this->GetSize();
    Hero::matrix_scale(model, {(float)size.x, (float)size.y, 0});

    unsigned int modelLoc = Renderer2D::GetShader()->GetUniformLocation("model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)(&(model.v[0])));
    unsigned int viewLoc = Renderer2D::GetShader()->GetUniformLocation("view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)(&(Renderer2D::GetViewMatrix()->v[0])));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->_id);
    DEBUG_CODE(glCheckError();)
    Renderer2D::GetMesh()->Draw();
    DEBUG_CODE(glCheckError();)
}

Button::Button()
{
    this->_text = new Text();
    this->_clickEvent = new Event();
}

Button::~Button()
{
    delete this->_text;
    delete this->_clickEvent;
}

void Button::SetAbsolutePosition(const int2& absolutePosition)
{
    this->_absolutPosition = absolutePosition + this->_relativePosition;
    this->_text->SetAbsolutePosition(this->_absolutPosition);
}

void Button::Apply()
{
    this->_text->Apply();
}

void Button::Update()
{
    this->_isHovering = false;
    int4 rect = {this->_absolutPosition.x , this->_absolutPosition.y,
                this->_size.x, this->_size.y};
    int2 mousePos;
    Input::getMousePosition(&mousePos.x, &mousePos.y);
    if(mousePos.x >= this->_absolutPosition.x && 
        mousePos.x <= this->_absolutPosition.x + this->_size.x &&
        mousePos.y >= this->_absolutPosition.y && 
        mousePos.y <= this->_absolutPosition.y + this->_size.y)
    {   
        this->_isHovering = true;
        if(Input::mouseButtonDown(Input::Mouse::Left))
        {
            this->_clickEvent->Invoke(this, nullptr, 0);
        }
    }
}

void Button::Draw()
{
    if(this->_texture == nullptr)
        return;

    Hero::matrix4x4 model;
    Hero::matrix_identity(model);
    Hero::int2 position = this->GetAbsolutePosition();
    Hero::matrix_translate(model, {(float)position.x, (float)position.y ,0});
    Hero::int2 size = this->GetSize();
    Hero::matrix_scale(model, {(float)size.x, (float)size.y, 0});

    unsigned int modelLoc = Renderer2D::GetShader()->GetUniformLocation("model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)(&(model.v[0])));
    unsigned int viewLoc = Renderer2D::GetShader()->GetUniformLocation("view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)(&(Renderer2D::GetViewMatrix()->v[0])));

    glActiveTexture(GL_TEXTURE0);
    this->_texture->Bind();
    DEBUG_CODE(glCheckError();)
    Renderer2D::GetMesh()->Draw();
    DEBUG_CODE(glCheckError();)
    this->_texture->Unbind();

    this->_text->Draw();
}

}