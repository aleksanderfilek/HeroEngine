#ifndef WORLD_HPP
#define WORLD_HPP

#include"Hero.hpp"

#include"camera.hpp"
#include"player.hpp"
#include"worldUI.hpp"
#include"light.hpp"

class World:public Hero::Level
{
private:
    Hero::Shader* basicShader;
    Hero::Shader* grassShader;

    Camera* camera;
    Player* player;
    WorldUI* worldUI;
    Sun* sun;

    Hero::Mesh* stone1Mesh;
    Hero::Texture* stone1Texture;
    Hero::matrix4x4 stoneMatrix;

    Hero::Mesh* groundMesh;
    Hero::Texture* groundTexture;
    Hero::matrix4x4 groundMatrix;

    void OnStart() override;
    void OnUpdate() override;
    void OnDraw() override;
    void OnClose() override;
};

#endif