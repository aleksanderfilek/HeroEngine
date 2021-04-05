#ifndef WORLD_HPP
#define WORLD_HPP

#include"Hero.hpp"

#include"camera.hpp"
#include"player.hpp"
#include"sector.hpp"

#define SECTOR_COUNT 5

class World:public Hero::Level
{
private:
    Hero::Texture* defaultTexture;
    Hero::Mesh* groundMesh;
    Hero::Shader* standardShader;

    Sector** sectors;

    Camera* camera;
    Player* player;
    
    void OnStart() override;
    void OnUpdate() override;
    void OnDraw() override;
    void OnClose() override;
};

#endif