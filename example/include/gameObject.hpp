#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

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

#endif