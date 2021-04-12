#include"trigger.hpp"

Trigger::Trigger(Hero::float3* _targetPosition)
                    :targetPosition(_targetPosition)
{

}

Trigger::~Trigger()
{
    this->event.Clear();
}

void Trigger::Update()
{
    if(position.x > targetPosition->x || targetPosition->x > (position.x + size.x))
        return;

    if(position.z > targetPosition->z || targetPosition->z > (position.z + size.z))
        return;

    this->event.Invoke(this, nullptr, 0);
}

