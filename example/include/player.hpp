#ifndef PLAYER_HPP
#define PLAYER_HPP

#include"Hero.hpp"

#include"emath.hpp"
#include"camera.hpp"
#include"components.hpp"
#include"anim.hpp"

class Player: public Hero::GameObject
{
private: 
    unsigned int modelLoc;
    Transform root;
    Hero::Texture* texture;
    Transform bones[15];
    Hero::Mesh meshes[15];

    Skeleton* skeleton;
    Animator* animator;

    int health = 500;
    const int maxHealth =  1000;

    const float moveSpeed = 2.0f;
    const float runSpeed = 5.0f;
    float currentSpeed;
    float targetSpeed;

    const float sprintRestorationSpeed = 1.0f;
    const float sprintLostSpeed = 3.0f;
    const float maxSprintTime = 10.0f;
    float sprintTime;
    bool sprintRestoring = false;

public:
    Player(unsigned int _modelLoc);
    ~Player();

    void Start();
    void Update();
    void Draw();
    void Close();

    inline Hero::float3* GetPositionRef(){ return &this->root.position; }
    inline int GetHealth(){ return this->health; }
    inline int GetMaxHealth(){ return this->maxHealth; }
    inline float GetSprint(){ return this->sprintTime; }
    inline float GetMaxSprint(){ return this->maxSprintTime; }
};

#endif