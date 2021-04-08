#ifndef PLAYER_HPP
#define PLAYER_HPP

#include"Hero.hpp"

#include"camera.hpp"
#include"components.hpp"
#include"anim.hpp"

class Player: public Hero::GameObject
{
private: 
    Hero::float3 position;
    float angle;
    Hero::matrix4x4 modelMatrix;

    Hero::Mesh* mesh;
    Hero::Texture* texture;
    unsigned int modelLoc;

    Camera* camera;

    Transform root;
    Transform child;
    Animator* animator;
public:
    Player(unsigned int _modelLoc);
    ~Player();

    void Start();
    void Update();
    void Draw();
    void Close();

    inline Hero::float3* GetPositionRef(){ return &this->position; }
    inline void SetCamera(Camera* _camera){ this->camera = _camera; }
};

#endif