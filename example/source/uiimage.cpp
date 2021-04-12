#include"uiimage.hpp"

Image::Image(Hero::Texture* _texture):texture(_texture)
{

}

Image::~Image()
{
    delete this->texture;
}

void Image::Draw()
{
    Hero::matrix4x4 model;
    Hero::matrix_identity(model);
    Hero::int2 position = this->GetAbsolutePosition();
    Hero::matrix_translate(model, {(float)position.x, (float)position.y ,0});
    Hero::int2 size = this->GetSize();
    Hero::matrix_scale(model, {(float)size.x, (float)size.y, 0});

    unsigned int modelLoc = Hero::Renderer2D::GetShader()->GetUniformLocation("model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)(&(model.v[0])));
    unsigned int viewLoc = Hero::Renderer2D::GetShader()->GetUniformLocation("view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)(&(Hero::Renderer2D::GetViewMatrix()->v[0])));

    glActiveTexture(GL_TEXTURE0);
    this->texture->Bind();
    DEBUG_CODE(glCheckError();)
    Hero::Renderer2D::GetMesh()->Draw();
}