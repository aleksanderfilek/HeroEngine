#include"light.hpp"

void Sun::SetDirection(Hero::float3& _direction)
{
    this->direction = { -_direction.x, -_direction.y, -_direction.z };
    Hero::normalize(this->direction);
}

void Sun::Bind(unsigned int _sunDirLoc, unsigned int _sunColorLoc)
{
    //glUniform3fv(this->sunDirLoc, 1, &this->direction.x);    
    //glUniform3fv(this->sunDirLoc, 1, &this->color.x);
    glUniform3f(_sunDirLoc, this->direction.x, this->direction.y, this->direction.z);
    glUniform3f(_sunColorLoc, this->color.x, this->color.y, this->color.z);
}
