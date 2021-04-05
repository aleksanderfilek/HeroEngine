#ifndef H_LEVEL_HPP
#define H_LEVEL_HPP

#include"H_gameObject.hpp"

#include<vector>

namespace Hero
{

class Level
{
protected:
    bool visible = true;

    std::vector<GameObject*> gameObjects;

    virtual void OnStart() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnDraw() = 0;
    virtual void OnClose() = 0;
public:
    Level(){};
    virtual ~Level(){};
    void Start();
    void Update();
    void Draw();
    void Close();

    inline void SetVisible(bool _visible){ this->visible = _visible; }
    inline bool GetVisible(){ return this->visible; }

    void AddGameObject(GameObject* gameObject);
};

}

#endif