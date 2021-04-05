#ifndef HERO_GAMEOBJECT_HPP
#define HERO_GAMEOBJECT_HPP

namespace Hero
{

class GameObject
{
public:
    GameObject(){};
    virtual ~GameObject(){};
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Close() = 0;
};

}

#endif