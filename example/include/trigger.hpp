#ifndef TRIGGER_HPP
#define TRIGGER_HPP

#include"Hero.hpp"

class Trigger: public Hero::GameObject
{
private:
    Hero::float3 position;
    Hero::float3 size;

    Hero::Event event;
    
    Hero::float3* targetPosition;
public:
    Trigger(Hero::float3* _targetPosition);
    ~Trigger();

    void Start(){}
    void Update();
    void Draw(){}
    void Close(){}

    inline void AddEvent(Hero::EventFunction function){ this->event.Add(function); }
    inline void SetPosition(Hero::float3 _position){ this->position = _position; };
    inline void SetSize(Hero::float3 _size){ this->size = _size; }
};

#endif