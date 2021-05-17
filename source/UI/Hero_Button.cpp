#include"UI/Hero_Button.hpp"

namespace Hero
{

Button::Button()
{
    this->_text = new Label();
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