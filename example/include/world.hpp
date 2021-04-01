#ifndef WORLD_HPP
#define WORLD_HPP

#include"Hero.hpp"

#include"camera.hpp"
#include"player.hpp"

class World:public Hero::Level
{
private:
    Hero::Texture* defaultTexture;
    Hero::Mesh* groundMesh;
    Hero::Shader* standardShader;

    Camera* camera;
    //Player* player;
    
public:
    void Start() override;
    void Update() override;
    void Draw() override;
    void Close() override;
};

#endif