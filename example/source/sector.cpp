#include"sector.hpp"

void Sector::OnStart()
{
    
}

void Sector::OnUpdate()
{
    
}

void Sector::OnDraw()
{
    glUniformMatrix4fv(this->modelLoc, 1, GL_FALSE, &this->modelMatrix.v[0].x);  
    glCheckError();
    this->mesh->Draw();
}

void Sector::OnClose()
{

}

Sector::Sector(Hero::Mesh*& _mesh, unsigned int _modelLoc, Hero::float3 _position)
    :mesh(_mesh),modelLoc(_modelLoc)
{
    this->visible = false;
    SetPosition(_position);
}

void Sector::SetPosition(Hero::float3& position)
{
    Hero::matrix_identity(this->modelMatrix);
    Hero::matrix_scale(this->modelMatrix, {SECTOR_SCALE, SECTOR_SCALE, 1});
    Hero::matrix_rotateAxisX(this->modelMatrix, Hero::deg2rad(90.0f));
    Hero::matrix_translate(this->modelMatrix, {position.x * SECTOR_SCALE, 0.0f, position.z * SECTOR_SCALE});
}