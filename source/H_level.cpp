#include"H_level.hpp"

namespace Hero
{

void Level::Start()
{ 
    OnStart();
}

void Level::Update()
{ 
    if(visible){
        OnUpdate(); 
        for(GameObject* g : this->gameObjects)
        {
            g->Update();
        }
    }
}

void Level::Draw()
{ 
    if(visible){
        OnDraw();
        for(GameObject* g : this->gameObjects)
        {
            g->Draw();
        }
    }
}

void Level::Close()
{ 
    OnClose(); 
    for(GameObject* g : this->gameObjects)
    {
        g->Close();
    }
}

void Level::AddGameObject(GameObject* gameObject)
{
    this->gameObjects.push_back(gameObject);
    gameObject->Start();
}


}