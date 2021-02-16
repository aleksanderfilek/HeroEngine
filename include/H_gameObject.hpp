#ifndef H_gameObjectP_HPP
#define H_gameObjectP_HPP

namespace Hero
{

class GameObject
{
private:

public:
    GameObject();
    ~GameObject();
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Close() = 0;
};

class MultiGameObject : public GameObject
{
public:
    MultiGameObject();
    ~MultiGameObject();
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Close() = 0;
};

}

#endif